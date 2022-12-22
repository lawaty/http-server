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
  Connection *conn;

public:
  /**
   * Method prepares the required data structures for operating the server
   * @param char* ip
   * @param char* port
   */
  Client(char *ip, char *port);

  void sendRequest(string msg);
};

Client::Client(char *ip, char *port)
{
  address = new AddrInfo(ip, port);

  sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock == -1)
    Output::showError("socket");

  if (connect(sock, address->format(), address->getLength()) < 0)
    Output::showError("connect");

  Output::showSuccess("Connected successfully");

  conn = new Connection(sock);
}

void Client::sendRequest(string msg)
{
  conn->echo(msg);
  cout << conn->recv();
}