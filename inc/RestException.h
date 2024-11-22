#ifndef __REST_EXCEPTION_H__
#define __REST_EXCEPTION_H__
#include "Utils.h"

class RestException : public std::exception {
public:
    RestException(const std::string& message) : message_(message) {}

    const char* what() const throw() {
        return message_.c_str();
    }

private:
    std::string message_;
};

#endif