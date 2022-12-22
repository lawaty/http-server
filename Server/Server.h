#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include "../Utils/AddrInfo.h"

#define INET AF_INET
#define MAX_QUEUE 5

using namespace std;

class Server
{
private:
  AddrInfo *si;           // struct holding server info
  int sock;               // socket file descriptor
  void showError(string); // error formatting method
  bool running;
  vector<int> conns;

public:
  Server(char *ip, char *port); // initializing the server
  void start();                 // bind to port and listen
  void stop();                  // close listening socket
};

void Server::showError(string err, bool fatal = true) {
  if(fatal)
    throw("Error: " + err);
  
  cout << "Warn: " + err;

}

Server::Server(char *ip, char *port) // initializing the server
{
  struct addrinfo hints;
  struct addrinfo* temp;

  memset(&hints, 0, sizeof hints);

  hints.ai_family = INET;
  hints.ai_socktype = SOCK_STREAM;
  if (ip == NULL)
    hints.ai_flags = AI_PASSIVE;

  if (getaddrinfo(ip, port, &hints, &temp))
    showError("getaddr");

  si = new AddrInfo(temp);

  cout << "Initialized server successfully" << endl;
}

void Server::start() {
  sock = socket(si->getFamily(), si->getType(), si->getProtocol());
  if (sock == -1)
    showError("socket");

  if (bind(sock, si->getAddr(), si->getLength()) == -1)
    showError("bind");

  if (listen(sock, MAX_QUEUE) == -1)
    showError("listen");

  cout << "Currently Listening on port " << si->getPort() << endl;

  struct sockaddr_storage their_addr; // connector address

  running = true;
  while(running) {
    int conn = accept(sock, (struct sockaddr *) &their_addr, sizeof their_addr);
    if(conn == -1){
      showError("Initializing communication with client failed", false);
      continue;
    }

    int id = fork();
    if(!id){
      conns.push_back(conn);
    }
  }

}

void Server::stop() {
  close(sock);
  cout << "Server closed";
  running = false;
}
