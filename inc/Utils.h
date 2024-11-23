#ifndef __UTILS_H__
#define __UTILS_H__
#include <iostream>
#include <memory>
#include <string>
#include <thread>
#include <functional>
#include <map>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast/ssl/ssl_stream.hpp>
#include <boost/asio/ssl.hpp>
#include <openssl/x509.h>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/algorithm/string.hpp>

#include "SslAuth.h"
#include "RestException.h"
#include "RestApiServer.h"
#include "IController.h"
#include "ControllerV1.h"
#include "ControllerV2.h"


namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = net::ip::tcp;

#define CERT_FILE "server.crt"
#define CERT_KEY_FILE "server.key"

class Cfg {
public:
    static const bool checkRouteOnly = true;
    static const bool checkRouteWithMethod = false;
    static const bool verifyClientCert = true;
    //static const std::string certFileName = CERT_FILE;
    //static const std::string certKeyFileName = CERT_KEY_FILE;
};


#endif
