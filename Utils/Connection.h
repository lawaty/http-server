#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include 

#define MAX_SIZE 200

/**
 * Entity easier the communication processes
*/
class Connection
{
private:
  int sock;
  char buf[MAX_SIZE]

public:
  Connection(int id);
  void handle();
  void echo();
  void read();
};

Connection::Connection(int id)
{
  sock = id;
}

void Connection::handle()
{
  echo(sock, "a7la mesa", 13, 0);
}

void Connection::echo(char msg[]){
  char* p = &msg[0];
  send(sock, p, sizeof(msg) / sizeof(msg[0]), 0);
}:

char* Connection::read(){
  int num_bytes = recv(sock, buf, MAX_SIZE - 1);
  if(num_bytes == -1)
    Output::showError("recv")
}