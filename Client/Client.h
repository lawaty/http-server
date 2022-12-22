#include <string>
#include <vector>

#include <cstring>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#ifndef OUTPUT
#include "../Utils/Output.h"
#endif

#ifndef ADDRINFO
#include "../Utils/AddrInfo.h"
#endif

#ifndef CONNECTION
#include "../Utils/Connection.h"
#endif

class Client
{
private:
  /**
   * DTO holds server info and provides easy interface to extract data from it
   */
  AddrInfo *address; // struct holding server info
  /**
   * Socket file descriptor
   */
  int sock;
  Connection* conn;

public:
  /**
   * Method prepares the required data structures for operating the server
   * @param char* ip
   * @param char* port
   */
  Client(char* ip, char* port);

  string sendRequest();
};

Client::Client(char* ip, char* port)
{
  address = new AddrInfo(ip, port);

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
    Output::showError("socket");

  if (connect(sock, address->format(), address->getLength()) == -1)
    Output::showError("connect");

  Output::showSuccess("Connected successfully");


  char buf[20];
  conn = new Connection(sock);
  int numbytes;
  if ((numbytes = recv(sock, buf, 19, 0)) == -1) {
    perror("recv");
    exit(1);
  }

  buf[numbytes] = '\0';
  printf("client: received '%s'\n",buf);
}

string Client::sendRequest(){
  
}
