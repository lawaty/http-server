#include <iostream>
#include <cstring>
#include <string>

#include "Server/Server.h"

/*
  Server applies multiprocessing approach to communicate to clients simultaneously as processes are more reliable that crasing one process won't affect the others unlike threads
*/

using namespace std;

int
main(int argc, char* argv[])
{
  char* port = argv[1];
  Server server(NULL, port);
  server.start();
  server.stop();
}