/*********************************************************/
#ifndef DELIV_H
#define DELIV_H
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sstream>
#include <unistd.h>
#include <vector>
using std::stringstream;
using std::vector;
// Server Listen Queue
static const short LisQ = 16;
// MaxBuffSize
static const short MaxBuffSize = 1024;
/*********************************************************/
class Deliv{
protected:
  int socketID;
  struct sockaddr_in server_sockaddr;
public:
  int getSKID();
  int getPort();
  char* getIP();
  void delivInit(const short &port,const char *ip);
  virtual void delivReady() = 0;
  virtual void delivClose() = 0;
  virtual short delivWking(const char sendBf[],char recvBf[],const int &cli) = 0;
};

class Server: public Deliv{
private:
  vector<int> connSKID;
  struct sockaddr_in client_sockaddr;
  bool delivBind();
  bool delivListen();
public:
  bool delivAccept();
  void delivReady();
  void delivClose();
  short delivWking(const char sendBf[],char recvBf[],const int &cli);
};

class Client: public Deliv{
private:
  bool delivConnect();
public:
  void delivReady();
  void delivClose();
  short delivWking(const char sendBf[],char recvBf[],const int &cli);
};
/*********************************************************/
#endif
