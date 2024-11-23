#include "Utils.h"

bool SslAuth::verify_callback1(bool preverified, ssl::verify_context& ctx) {
  std::cerr << __FUNCTION__ << ":" << __LINE__ << std::endl;
    // Check if the peer's certificate is valid
    if (!preverified) {
        return true;
    }
  std::cerr << __FUNCTION__ << "--:" << __LINE__ << std::endl;
    char subject_name[256];
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    X509_NAME_oneline(X509_get_subject_name(cert), subject_name, sizeof(subject_name));

    unsigned char md[EVP_MAX_MD_SIZE];
    unsigned int n;
    if (!X509_digest(cert, EVP_sha1(), md, &n)) {
    std::cerr << __FUNCTION__ << "--********:" << __LINE__ << std::endl;
        return false;
    }

    std::ostringstream clientThumbprint;
    for (unsigned int i = 0; i < n; i++) {
        clientThumbprint << std::hex << std::uppercase << (md[i] >> 4);
        clientThumbprint << std::hex << std::uppercase << (md[i] & 0x0F);
        if (i + 1 < n) clientThumbprint << ":";
    }
    return true;
}
// Function to get the thumbprint (SHA1) of the certificate
std::string SslAuth::get_certificate_thumbprint(X509* cert) {
    unsigned char md[EVP_MAX_MD_SIZE];
    unsigned int n;

    if (!X509_digest(cert, EVP_sha1(), md, &n)) {
        throw std::runtime_error("Failed to compute certificate thumbprint");
    }

    std::ostringstream thumbprint;
    for (unsigned int i = 0; i < n; i++) {
        thumbprint << std::hex << std::uppercase << (md[i] >> 4);
        thumbprint << std::hex << std::uppercase << (md[i] & 0x0F);
        if (i + 1 < n) thumbprint << ":";
    }

    return thumbprint.str();
}

bool SslAuth::verify_callback(bool preverified, ssl::verify_context& ctx) {
    // Get the current certificate being verified
    X509* cert = X509_STORE_CTX_get_current_cert(ctx.native_handle());
    if (!cert) {
        std::cerr << "No certificate present in verify context" << std::endl;
        return false;
    }

    // Get the subject name of the certificate
    char subject_name[256];
    X509_NAME* subject = X509_get_subject_name(cert);
    if (!subject) {
        std::cerr << "No subject name found in certificate" << std::endl;
        return false;
    }

    X509_NAME_oneline(subject, subject_name, sizeof(subject_name));
    std::cout << "Certificate subject name: " << subject_name << std::endl;

    // Get and print the thumbprint of the certificate
    try {
        std::string thumbprint = get_certificate_thumbprint(cert);
        std::cout << "Certificate thumbprint: " << thumbprint << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error computing thumbprint: " << e.what() << std::endl;
        return false;
    }

    // Check if the subject name is present
    if (strlen(subject_name) == 0) {
        std::cerr << "Subject name is empty" << std::endl;
        return false;
    }
    
    // Log the reason why preverified is false
    if (!preverified) {
        int error = X509_STORE_CTX_get_error(ctx.native_handle());
        std::cerr << "Preverification failed: " << X509_verify_cert_error_string(error) << std::endl;
    }

    // Additional checks can be implemented here if needed

    // Override preverified to true if all checks pass (optional)
    // return preverified;  // Proceed based on the initial verification status
    return true;  // Override preverified to true if all checks pass
}

void SslAuth::loadServerCertificate(ssl::context& ctx) {
        std::cerr << __FUNCTION__ << ":" << __LINE__ << std::endl;
        // Load the certificate from the file
        ctx.set_options(ssl::context::default_workarounds | ssl::context::no_sslv2 | ssl::context::single_dh_use);
        ctx.use_certificate_chain_file(CERT_FILE);
        ctx.use_private_key_file(CERT_KEY_FILE, ssl::context::pem);
        if (Cfg::verifyClientCert == true) {
            ctx.set_verify_mode(ssl::verify_peer | ssl::verify_fail_if_no_peer_cert);
            ctx.set_verify_callback(verify_callback);
        }
        std::cerr << __FUNCTION__ << ":" << __LINE__ << std::endl;
    }