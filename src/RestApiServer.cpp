#include "Utils.h"

RestApiServer::RestApiServer(net::io_context& ioc, ssl::context& ctx, uint16_t port)
    : ioc_(ioc), ctx_(ctx), port_(port) {}

// Add a route to the server
void RestApiServer::addRoute(const Route& route) {
    routes_[route.target + " " + route.method] = route.handler;
}

// Get the handler for a route
std::function<void(std::string target, std::string method, http::request<http::string_body>, http::response<http::string_body>&)>
RestApiServer::getHandler(const std::string& target, const std::string& method) {
    std::string target_string = target;
    std::cout << __FUNCTION__ << ":" << __LINE__ << " :  [" << method << "] " <<  target << std::endl;
    if (target.empty() || method.empty())
        return {};
    size_t first_slash = target.find('/');
    size_t second_slash = target.find('/', first_slash + 1); 
    if (first_slash != std::string::npos && second_slash != std::string::npos) { 
        target_string = target.substr(0, second_slash); 
    }

    if (Cfg::checkRouteOnly) {
        for (auto route:routes_) {
            std::cout << "Checking " << route.first << " in " << target_string << std::endl;        
            if (route.first.find(target_string) == 0) {
                std::cout << "Found match for : target = " << route.first << std::endl;
                return route.second;
            } 
        }
        std::cout << "No route match found for : target = " << target_string << std::endl;
    } else {
        //std::map<std::string, std::function<void(std::string target, std::string method, http::request<http::string_body>, http::response<http::string_body>&)>>::iterator it;
        auto it = routes_.find(target + " " + method);
        if (it != routes_.end()) {
            return it->second;
        }
    }
    
    return {};
}

// Start the server
void RestApiServer::start() {
    // Create a TCP acceptor
    acceptor_ = std::make_unique<tcp::acceptor>(ioc_, tcp::endpoint{net::ip::make_address("0.0.0.0"), port_});

    // Create a SSL context
    sslCtx_ = std::make_unique<ssl::context>(std::move(ctx_));

    // Load the server certificate
    SslAuth::loadServerCertificate(*sslCtx_);

    // Start accepting connections
    accept();
}

// Accept a new connection
void RestApiServer::accept() {
    // Create a new session
    auto session = std::make_shared<Session>(ioc_, *sslCtx_, this);

    // Accept a new connection
    acceptor_->async_accept(session->stream_.next_layer().socket(),
        [session, this](beast::error_code ec) {
            if (ec) {
                return fail(ec, "accept");
            }

            // Handle the new connection
            session->run();
            accept();
        });
}

// Handle a failure
void RestApiServer::fail(beast::error_code ec, char const* what) {
    std::cerr << what << ": " << ec.message() << "\n";
}

Session :: Session(net::io_context& ioc, ssl::context& ctx, RestApiServer* server)
    : ioc_(ioc), ctx_(ctx), socket_(ioc), stream_(std::move(socket_), ctx), server_(server) {}
    // Run the session
void Session :: run() {
    // Perform the SSL handshake
    stream_.async_handshake(ssl::stream_base::server,
        [self = shared_from_this()](beast::error_code ec) {
            if (ec) {
                return self->fail(ec, "handshake");
            }

            // Read the request
            self->readRequest();
        });
}

// Read the request
void Session :: readRequest() {
    // Create a buffer to store the request
    buffer_ = std::make_unique<beast::flat_buffer>();

    // Read the request
    http::async_read(stream_, *buffer_, request_,
        [self = shared_from_this()](beast::error_code ec, std::size_t bytes_transferred) {
            if (ec) {
                return self->fail(ec, "read");
            }

            // Handle the request
            self->handleRequest();
        });
}

// Handle the request
void Session :: handleRequest() {
    if (!server_) {
      // Handle null server pointer
      return fail(beast::error_code(net::error::invalid_argument), "null server pointer");
    }
    // Get the target and method from the request
    std::string target = request_.target().to_string();
    std::string method = request_.method_string().to_string();

    // Get the handler for the route
    auto handler = server_->getHandler(target, method);

    if (handler) {
        // Call the handler to handle the request
        handler(target, method, request_, response);

        // Write the response
        writeResponse(response);
    } else {
        // Return a 404 error if no handler is found
        //http::response<http::string_body> response{http::status::not_found, request_.version()};
        response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
        response.set(http::field::content_type, "text/plain");
        response.body() = "Not Found";
        response.prepare_payload();

        // Write the response
        writeResponse(response);
    }
}

// Write the response
void Session :: writeResponse(http::response<http::string_body> &response) {
    // Write the response
    http::async_write(stream_, response,
        [self = shared_from_this()](beast::error_code ec, std::size_t bytes_transferred) {
            if (ec) {
                return self->fail(ec, "write");
            }

            // Close the stream
            self->stream_.async_shutdown(
                [self](beast::error_code ec) {
                    if (ec) {
                        return self->fail(ec, "shutdown");
                    }
                });
        });
}

// Handle a failure
void Session :: fail(beast::error_code ec, char const* what) {
    std::cerr << what << ": " << ec.message() << "\n";
}

// Define the main function
int ServerStart() {
    // Create a new IO context
    net::io_context ioc;

    // Create a new SSL context
    ssl::context ctx{ssl::context::sslv23};

    // Create a new REST API server
    RestApiServer server(ioc, ctx, 4434);

    // Add routes to the server
    server.addRoute(Route{"/", "GET", [](std::string target, std::string method, http::request<http::string_body> request, http::response<http::string_body>& response) {
        response.body() = "Hello, World!............\n";
        response.prepare_payload();
    }});
    server.addRoute(Route{"/apiv1", "GET", Controller::handleRequest});
    server.addRoute(Route{"/apiv2", "", Controller::handleRequest});
    // Start the server
    server.start();

    // Run the IO context
    ioc.run();

    return 0;
}