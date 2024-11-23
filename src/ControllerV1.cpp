#include "Utils.h"

void ControllerV1::handleRequest(http::request<http::string_body> request, http::response<http::string_body>& response) {
    std::string response_message;
    std::string target = request.target().to_string();
    if (request.method() == http::verb::get && boost::algorithm::starts_with(target, "/apiv1/GetVnet")) {
        response_message = GetVnet(request);
    } else if (target == "PutVnet") {
        response_message =  PutVnet(request);
    } else if (target == "GetMapping") {
        response_message =  PutMapping(request);
    } else if (target == "PutMappingt") {
        response_message =  GetVnet(request);
    } else if (target == "GetConfig") {
        response_message = GetConfig(request);
    } else if (target == "PutConfig") {
        response_message = PutConfig(request);
    } else {
        response_message += "Endpoints are:\n";
        response_message += "POST : /apiv1/PutVnet \n";
        response_message += "POST : /apiv1/GetVnet \n";
        response_message += "POST : /apiv1/PutMapping \n";
        response_message += "GET  : /apiv1/GetMapping \n";
        response_message += "GET  : /apiv1/GetConfig \n";
        response_message += "GET  : /apiv1/PutConfig \n";
        throw NotImplementedException(response_message);
    }
    response.body() = response_message;
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

std::string ControllerV1::PutMapping(http::request<http::string_body> &request) {
    return "Something............... \n";
}

std::string ControllerV1::GetConfig(http::request<http::string_body> &request) {
    return "Something............... \n";
}

std::string ControllerV1::PutConfig(http::request<http::string_body> &request) {
    return "Something............... \n";
}
