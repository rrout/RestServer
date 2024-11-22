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


#include "SslAuth.h"
#include "RestException.h"
#include "RestServer.h"
#include "IController.h"
#include "ControllerV1.h"
#include "ControllerV2.h"


namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = net::ip::tcp;

#endif