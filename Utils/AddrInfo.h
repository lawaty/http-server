#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

/**
 * DTO for clarity
 */
class AddrInfo
{
public:
  struct addrinfo* ai;
  struct sockaddr_in *sin;

  AddrInfo(struct addrinfo* ai)
  {
    this->ai = ai;
    this->sin = (struct sockaddr_in *) ai;
  }

  struct sockaddr* getAddr() {
    return this->ai->ai_addr;
  }

  int getFamily()
  {
    return ai->ai_family;
  }

  int getType()
  {
    return ai->ai_socktype;
  }

  int getProtocol()
  {
    return ai->ai_protocol;
  }

  int getLength()
  {
    return ai->ai_addrlen;
  }

  int getPort()
  {
    return htons(sin->sin_port);
  }
};