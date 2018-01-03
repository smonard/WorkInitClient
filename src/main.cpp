#include <iostream>
#include <string>
#include "Client/Client.cpp"
#include "Client/Credential.cpp"
#include <termios.h>

struct Endpoint {
  string host;
  string port;
};

struct Endpoint GetEndpoint();
Credential * GetCredentials();

int main(){
  struct Endpoint endpoint = GetEndpoint();
  try 
  {
    Credential * credential = GetCredentials();
    Client client(endpoint.host, endpoint.port);

    int statusCode = client.MakeRequest(credential);
    
    delete credential;
    return statusCode;
  }
  catch (int e)
  {
    perror("Program failed");
    return e;
  }
  
}

struct Endpoint GetEndpoint(){
  struct Endpoint endpoint;
  std::string host, port;
  if(const char* hostEnv = std::getenv("HOST_TL")) {
    host = hostEnv;
    std::cout << "Using " << host << " as Server address." << endl;
  }
  else {
    std::cout << "Host IP: ";
    std::cin >> host;
  }
  if(const char* portEnv = std::getenv("PORT_TL")) {
    port = portEnv;
    std::cout << "Using " << port << " as Server port." << endl;
  }
  else {
    std::cout << "Port: ";
    std::cin >> port;
  }
 
  endpoint.host = host;
  endpoint.port = port;
  return endpoint;
}

Credential * GetCredentials(){
  struct termios oflags, nflags;
  tcgetattr(fileno(stdin), &oflags);
  nflags = oflags;
  nflags.c_lflag &= ~ECHO;
  nflags.c_lflag |= ECHONL;
  tcsetattr(fileno(stdin), TCSANOW, &nflags);

  std::string user, pass;
  std::cout << "Username: ";
  std::cin >> user;
  std::cout << "Password: ";
  std::cin >> pass;
  Credential * credential = new Credential(user, pass);
  std::cout << "----" << '\n';

  tcsetattr(fileno(stdin), TCSANOW, &oflags);
  return credential;
}