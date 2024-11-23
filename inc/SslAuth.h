#ifndef __SSL_AUTH_H__
#define __SSL_AUTH_H__
#include "Utils.h"
namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
namespace ssl = net::ssl;
using tcp = net::ip::tcp;
class SslAuth {
public:
    static bool verify_callback1(bool preverified, ssl::verify_context& ctx);
    // Function to get the thumbprint (SHA1) of the certificate
    static std::string get_certificate_thumbprint(X509* cert);
    static bool verify_callback(bool preverified, ssl::verify_context& ctx);
    static void loadServerCertificate(ssl::context& ctx);


};
#endif