#include <string>
#include <vector>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

#include "../Utils/Output.h"

#include "Client.h"

using namespace std;

int
main(int argc, char* argv[])
{

  if(argc < 3)
    Output::showError("IP and Port Are Required");

  char* ip = argv[1];
  char* port = argv[2];

  Client client(ip, port);
  client.sendRequest();
}