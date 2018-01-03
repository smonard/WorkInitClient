#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Credential.cpp"

#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <sstream>

using namespace std;

class Client{
private:
  BIO * bio;
  SSL * ssl;
  SSL_CTX * ctx;
  string host;
  string hostPort;

  string BuildRequest(string user, string pass){
    string requestBody = user + "|" + pass ;
    string http = "POST /start-evething HTTP/1.1\r\n";
    string httpHost = "Host: " + this->host + "\r\n";
    string httpContentType = "Content-Type: text/plain\r\n";
    string httpContentLeght = string("Content-Length: ") + to_string(requestBody.size()) + "\r\n";
    string httpConnectionClose = "Connection: Close\r\n";
    string httpAccept = "Accept: */*\r\n";
    string httpEndLine = "\r\n";

    stringstream requestStream;
    requestStream << http << httpHost << httpContentType << httpContentLeght << httpConnectionClose << httpAccept << httpEndLine << requestBody;

    return requestStream.str();
  }

  SSL_CTX * SetUpSslContext(){
    ctx = SSL_CTX_new(SSLv23_client_method());

    if(! SSL_CTX_set_default_verify_paths(ctx))
    {
      std::cout << "ERROR while loading certs" << '\n';
      printf("Error: %s\n", ERR_reason_error_string(ERR_get_error()));
      throw 221;
    }
    return ctx;
  }

  BIO * OpenBio(){
    bio = BIO_new_ssl_connect(ctx);


    BIO_get_ssl(bio, & ssl);
    SSL_set_mode(ssl, SSL_MODE_RELEASE_BUFFERS);

    string uri = string(this->host + ":" + this->hostPort);
    BIO_set_conn_hostname(bio, uri.c_str());

    if(BIO_do_connect(bio) <= 0)
    {
        fprintf(stderr, "Error attempting to connect\n");
        throw 220;
    }
    return bio;
  }

  void ValidateCert(){
    if(SSL_get_verify_result(ssl) != X509_V_OK)
    {
        fprintf(stderr, "Certificate verification error :( \nCode: %i\n", SSL_get_verify_result(ssl));
    }
  }

public:

  Client(string n_host, string n_port) : host(n_host) {
    this->hostPort = n_port;
    SSL_load_error_strings();
    ERR_load_BIO_strings();
    OpenSSL_add_all_algorithms();

    SSL_library_init();
    SSL_load_error_strings();
  }

  int MakeRequest(Credential* credential){
    ctx = SetUpSslContext();
    bio = OpenBio();
    ValidateCert();

    int bytesNumber;
    char response[8];

    string request = BuildRequest((*credential).GetUser(), (*credential).GetKey());
    BIO_write(bio, request.c_str(), request.size());

    std::cout << endl;
    for(;;)
    {
        bytesNumber = BIO_read(bio, response, 7);
        if(bytesNumber <= 0) break;
        response[bytesNumber] = '\0';
        printf(response);
    }
    int statusCode = 0;
    std::cout << "program status: " << statusCode <<"\r\n";
    return statusCode;
  }

  ~Client(){
    BIO_free_all(bio);
    SSL_CTX_free(ctx);
  }
};