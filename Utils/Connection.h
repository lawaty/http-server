#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#define CONNECTION

#ifndef OUTPUT
#include "Output.h"
#endif

#define MAX_SIZE 10

/**
 * Entity easier the communication processes
*/
class Connection
{
private:
  int sock;
  char buf[MAX_SIZE];

public:
  Connection();
  Connection(int id);
  void handle();
  void echo(string msg);
  char* read();
};

Connection::Connection(){}

Connection::Connection(int id)
{
  sock = id;
}

void Connection::echo(string msg){
  char* p = &msg[0];
  int len = send(sock, p, msg.length() - 1, 0);
  cout << p << msg << len << msg.length() << endl;
  if(len > 0)
    cout << "Sent a msg with length " << len << " : " << msg << endl;
  else
    Output::showError("send");
};

char* Connection::read(){
  int num_bytes = recv(sock, buf, MAX_SIZE - 1, 0);
  if(num_bytes == -1)
    Output::showError("read");

  cout << "Received a msg of size " << num_bytes << ":" << buf << endl;
  return buf;
}