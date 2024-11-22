#include "Utils.h"

void ControllerV2::handleRequest(http::request<http::string_body> request, http::response<http::string_body>& response) {
    std::string target = request.target().to_string();

    auto handler = handlers.find(target);
    if (handler != handlers.end()) {
        std::string result = handler->second(request);
        response.body() = result;
        response.prepare_payload();
    } else {
        throw RestException("Something went wrong");
    }
}

// In your constructor or initialization function
ControllerV2::ControllerV2() noexcept {
    handlers["/GetVnet"] = [](http::request<http::string_body>& request) {
        // Implement GetVnet logic here
        return "GetVnet result";
    };

    handlers["/PutVnet"] = [](http::request<http::string_body>& request) {
        // Implement PutVnet logic here
        return "PutVnet result";
    };

    handlers["/GetMapping"] = [](http::request<http::string_body>& request) {
        // Implement GetMapping logic here
        return "GetMapping result";
    };

    handlers["/PutMapping"] = [](http::request<http::string_body>& request) {
        // Implement PutMapping logic here
        return "PutMapping result";
    };

    handlers["/GetConfig"] = [](http::request<http::string_body>& request) {
        // Implement GetConfig logic here
        return "GetConfig result";
    };

    handlers["/PutConfig"] = [](http::request<http::string_body>& request) {
        // Implement PutConfig logic here
        return "PutConfig result";
    };
}