#ifndef __RESTAPI_SERVER_H__
#define __RESTAPI_SERVER_H__
#include "Utils.h"
#include "IController.h"
#include "ControllerV1.h"
#include "ControllerV2.h"

class RestApiServer;

struct Route {
    std::string target;
    std::string method;
    std::function<void(std::string target, std::string method, http::request<http::string_body>, http::response<http::string_body>&)> handler;
};

class Controller {
public:
    static void handleRequest(std::string target, std::string method, http::request<http::string_body> request, http::response<http::string_body>& response) {
        std::string response_message;
        http::status status;
        std::string apiV1 = "/apiv1/";
        std::string apiV2 = "/apiv2/";
        bool is_apiv1 = target.find("/apiv1/") == 0;
        bool is_apiv2 = target.find("/apiv2/") == 0;
        std::cout << __FUNCTION__ << ":" << __LINE__ << " :  [" << method << "] " <<  target << std::endl;
        
        if (!is_apiv1 && !is_apiv2) {
            response_message = "505 HTTP Version Not Supported : Controller V1 support Routes [ /apiv1/ OR /apiv2/ ]  ..... \n";
            status = http::status::bad_request;   
        }
        try {
            if (is_apiv1) {
                std::unique_ptr<IController> controller = std::make_unique<ControllerV1>();
                controller->handleRequest(request, response);
            } else if (is_apiv2) {
                std::unique_ptr<IController> controller = std::make_unique<ControllerV2>();
                controller->handleRequest(request, response);
            }
        } catch (const NotImplementedException& e) {
            std::cerr << "Exception caught: " << e.what() << std::endl;
            response_message += e.what();
            response_message += e.status();
        } catch (const std::exception& e) {
            std::cerr << "Exception caught: " << e.what() << std::endl;
            response_message += e.what();
            response_message += "500 Internal Server Error \n";
        } catch (...) {
            // handle unknown exception
            std::cerr << "Unknown exception caught" << std::endl;
            response_message = "500 Internal Server Error";
            status = http::status::bad_request;
        }
        response.body() += response_message + "\n";
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
    RestApiServer(net::io_context& ioc, ssl::context& ctx, uint16_t port);

    // Add a route to the server
    void addRoute(const Route& route);

    // Get the handler for a route
    std::function<void(std::string target, std::string method, http::request<http::string_body>, http::response<http::string_body>&)>
    getHandler(const std::string& target, const std::string& method);

    // Start the server
    void start();

private:
    // Accept a new connection
    void accept();

    // Handle a failure
    void fail(beast::error_code ec, char const* what);

    // Member variables
    net::io_context& ioc_;
    ssl::context& ctx_;
    std::unique_ptr<tcp::acceptor> acceptor_;
    std::unique_ptr<ssl::context> sslCtx_;
    uint16_t port_;
    std::map<std::string, std::function<void(std::string target, std::string method, http::request<http::string_body>, http::response<http::string_body>&)>> routes_;
};
#endif
