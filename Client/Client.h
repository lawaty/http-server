#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include "../Utils/Output.h"
#include "../Utils/AddrInfo.h"
#include "../Utils/Connection.h"

#define INET AF_INET

class Client
{
private:
  /**
   * DTO holds server info and provides easy interface to extract data from it
  */
  AddrInfo *si; // struct holding server info
  /**
   * Socket file descriptor
  */
  int sock;
  Connection conn;
  
public:

  /**
   * Method prepares the required data structures for operating the server
   * @param char[] ip
   * @param char[] port
  */
  Client(char *ip, char *port);
  /**
   * Method initializes listeners and manager connection requests
  */
 };

Client::Client(ip, port) {
  struct addrinfo hints;
  struct addrinfo *temp;

   memset(&hints, 0, sizeof hints);

  hints.ai_family = INET;
  hints.ai_socktype = SOCK_STREAM;
  if (ip == NULL)
    hints.ai_flags = AI_PASSIVE;

  if (getaddrinfo(ip, port, &hints, &temp))
    Output::showError("getaddr");

  si = new AddrInfo(temp);

  sock = socket(si->getFamily(), si->getType(), si->getProtocol());
  if (sock == -1)
    Output::showError("socket");    

  if(connect(sock, si->getAddr(), si->getLength()) == -1)
    Output::showError("connect");

  Output::showSuccess("Connected successfully");

  conn(sock);
}

