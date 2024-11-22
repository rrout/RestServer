#ifndef __RESTAPI_SERVER_H__
#define __RESTAPI_SERVER_H__
#include "Utils.h"

class RestApiServer;

struct Route {
    std::string target;
    std::string method;
    std::function<void(std::string target, std::string method, http::request<http::string_body>, http::response<http::string_body>&)> handler;
};

class Controller {
public:
    static void handleRequest(http::request<http::string_body> request, http::response<http::string_body>& response) {
        try {
            // code here
        } catch (const std::exception& e) {
            // handle exception
        } catch (...) {
            // handle unknown exception
        }
        response.body() = "Response from Controller V1..... \n";
        response.prepare_payload();
    }

};

class Session : public std::enable_shared_from_this<Session> {
public:
    Session(net::io_context& ioc, ssl::context& ctx, RestApiServer* server);

    // Run the session
    void run();

    // Read the request
    void readRequest();

    // Handle the request
    void handleRequest();

    // Write the response
    void writeResponse(http::response<http::string_body> &response);

    // Handle a failure
    void fail(beast::error_code ec, char const* what); 
    // Member variables
    net::io_context& ioc_;
    ssl::context& ctx_;
    RestApiServer* server_;
    beast::tcp_stream socket_;
    beast::ssl_stream<beast::tcp_stream> stream_;
    // Create a response
    http::response<http::string_body> response;
    http::request<http::string_body> request_;
    std::unique_ptr<beast::flat_buffer> buffer_;
};


class RestApiServer {
public:
    RestApiServer(net::io_context& ioc, ssl::context& ctx, uint16_t port)
        : ioc_(ioc), ctx_(ctx), port_(port) {}

    // Add a route to the server
    void addRoute(const Route& route);

    // Get the handler for a route
    std::function<void(std::string target, std::string method, http::request<http::string_body>, http::response<http::string_body>&)>
    getHandler(const std::string& target, const std::string& method);

    // Start the server
    void start();

private:
    // Load the server certificate
    void loadServerCertificate(ssl::context& ctx);

    // Accept a new connection
    void accept();

    // Handle a failure
    void fail(beast::error_code ec, char const* what)[;

    // Member variables
    net::io_context& ioc_;
    ssl::context& ctx_;
    std::unique_ptr<tcp::acceptor> acceptor_;
    std::unique_ptr<ssl::context> sslCtx_;
    uint16_t port_;
    std::map<std::string, std::function<void(std::string target, std::string method, http::request<http::string_body>, http::response<http::string_body>&)>> routes_;
};
#endif
