#ifndef __ICONTROLLER_H__
#define __ICONTROLLER_H__

class IController {
public:
    virtual void handleRequest(http::request<http::string_body> request, http::response<http::string_body>& response) = 0;
};

#endif