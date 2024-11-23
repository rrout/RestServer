#include "Utils.h"

void ControllerV2::handleRequest(http::request<http::string_body> request, http::response<http::string_body>& response) {
    std::string response_message;
    std::string target = request.target().to_string();
    bool handlerFound = false;
    for (auto handler:handlers) {
        if (boost::algorithm::contains(target, handler.first)) {
            response_message = handler.second(request);
            handlerFound = true;
        }
    }
    if (handlerFound == false) {
        response_message += "Endpoints are:\n";
        response_message += "POST : /apiv2/PutVnet \n";
        response_message += "POST : /apiv2/GetVnet \n";
        response_message += "POST : /apiv2/PutMapping \n";
        response_message += "GET  : /apiv2/GetMapping \n";
        response_message += "GET  : /apiv2/GetConfig \n";
        response_message += "GET  : /apiv2/PutConfig \n";
        throw NotImplementedException(response_message);
    }
    response.body() = response_message;
    response.prepare_payload();
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