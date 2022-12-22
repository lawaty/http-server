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
#define MAX_QUEUE 5

using namespace std;

/**
 * 
*/
void handleConnection(int id)
{
  Connection conn(id);
  conn.handle();
}


class Server
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
  bool running;

public:
  /**
   * Method prepares the required data structures for operating the server
   * @param char[] ip
   * @param char[] port
  */
  Server(char *ip, char *port);
  /**
   * Method initializes listeners and manager connection requests
  */
  void start();
  /**
   * Method stops listeners
  */
  void stop();
};

Server::Server(char *ip, char *port) // initializing the server
{
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

  Output::showSuccess("Initialized server successfully");
}

void Server::start()
{
  // Starting listener
  sock = socket(si->getFamily(), si->getType(), si->getProtocol());
  if (sock == -1)
    Output::showError("socket");

  if (bind(sock, si->getAddr(), si->getLength()) == -1)
    Output::showError("bind");

  if (listen(sock, MAX_QUEUE) == -1)
    Output::showError("listen");

  // Accepting Connections
  struct sockaddr_storage their_addr; // connector address
  running = true;
  cout << "Currently Listening on port " << si->getPort() << endl;
  while (running)
  {
    int conn_id = accept(sock, (struct sockaddr *)&their_addr, sizeof their_addr);

    // Connection rejected
    if (conn_id == -1)
    {
      Output::showError("Initializing communication with client failed", false);
      continue;
    }

    // Connection accepted
    Output::showSuccess("Connection Accepted");
    int id = fork();

    if (!id) // Child process
      handleConnection(id);
    
    else
      close(id); // Parent doesn't need the connection descriptor at all
  }
}

void Server::stop()
{
  close(sock);
  cout << "Server closed";
  running = false;
}
