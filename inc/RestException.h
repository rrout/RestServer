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


class NotImplementedException : public std::exception {
public:
    NotImplementedException(const std::string& message) : message_(message) {}

    const char* what() const throw() {
        return message_.c_str();
    }
    const char* status() const throw() {
        return statusStr.c_str();
    }

private:
    std::string statusStr = "501 Not Implemented";
    std::string message_; //501
};

#endif