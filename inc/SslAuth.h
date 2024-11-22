#ifndef __SSL_AUTH_H__
#define __SSL_AUTH_H__
#include "Utils.h"

class SslAuth {
public:
    bool verify_callback1(bool preverified, ssl::verify_context& ctx);
    // Function to get the thumbprint (SHA1) of the certificate
    std::string get_certificate_thumbprint(X509* cert);
    bool verify_callback(bool preverified, ssl::verify_context& ctx);
    void loadServerCertificate(ssl::context& ctx);


};
#endif