#include <iostream>
#include <cstring>
#include <string>

#include "Server.h"

/*
  Server applies multiprocessing approach to communicate to clients simultaneously as processes are more reliable that now if one process crashes, it won't affect the others unlike threads
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