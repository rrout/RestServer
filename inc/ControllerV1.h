#ifndef __CONTROLLER_V1_H__
#define __CONTROLLER_V1_H__
class ControllerV1 : public IController {
public:
    void handleRequest(http::request<http::string_body> request, http::response<http::string_body>& response);
    std::string GetVnet(http::request<http::string_body> &request);
    std::string PutVnet(http::request<http::string_body> &request);
    std::string GetMappingt(http::request<http::string_body> &request);
    std::string PutMapping(http::request<http::string_body> &request);
    std::string GetConfig(http::request<http::string_body> &request);
    std::string PutConfig(http::request<http::string_body> &request);
};
#endif