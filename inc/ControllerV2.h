#ifndef __CONTROLLER_V2_H__
#define __CONTROLLER_V2_H__
class ControllerV2 : public IController {
public:
    ControllerV2() noexcept;
    void handleRequest(http::request<http::string_body> request, http::response<http::string_body>& response);

private:
    std::map<std::string, std::function<std::string(http::request<http::string_body>&)>> handlers;
};
#endif