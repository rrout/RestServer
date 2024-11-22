#include "Utils.h"

void ControllerV1::handleRequest(http::request<http::string_body> request, http::response<http::string_body>& response) {
    std::string target = request.target().to_string();
    if (target == "GetVnet") {
        GetVnet(request);
    } else if (target == "PutVnet") {
        PutVnet(request);
    } else if (target == "GetMapping") {
        PutMappingt(request);
    } else if (target == "PutMappingt") {
        GetVnet(request);
    } else if (target == "GetConfig") {
        GetConfig(request);
    } else if (target == "PutConfig") {
        PutConfig(request);
    } else {
      throw RestException("Something went wrong");
    }
}
std::string ControllerV1::GetVnet(http::request<http::string_body> &request) {
    return "Something............... \n";
}

std::string ControllerV1::PutVnet(http::request<http::string_body> &request) {
    return "Something............... \n";
}

std::string ControllerV1::GetMapping(http::request<http::string_body> &request) {
    return "Something............... \n";
}

std::string ControllerV1::PutMappingt(http::request<http::string_body> &request) {
    return "Something............... \n";
}

std::string ControllerV1::GetConfig(http::request<http::string_body> &request) {
    return "Something............... \n";
}

std::string ControllerV1::PutConfig(http::request<http::string_body> &request) {
    return "Something............... \n";
}
