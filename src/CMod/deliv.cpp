#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <iostream>
#include "deliv.h"
using std::cin;
using std::cout;
using std::endl;
/*********************************************************/
/*********************************************************/
int Deliv::getSKID(){
  return socketID;
}
int Deliv::getPort(){
  return ntohs(server_sockaddr.sin_port);
}
char* Deliv::getIP(){
  struct in_addr addr;
  memcpy(&addr,&(server_sockaddr.sin_addr.s_addr), 4);
  return inet_ntoa(addr);
}
void Deliv::delivInit(const short &port,const char *ip){
  socketID = socket(AF_INET,SOCK_STREAM,0);
  server_sockaddr.sin_family = AF_INET;
  server_sockaddr.sin_port = htons(port);
  server_sockaddr.sin_addr.s_addr = inet_addr(ip);
}
/*********************************************************/
/*******     Server     *******/
bool Server::delivBind(){
  if( bind(socketID,(struct sockaddr *)&(server_sockaddr),sizeof(server_sockaddr)) == 0 ){
    return true;
  }else{return false;};
}
bool Server::delivListen(){
  if (listen(socketID,LisQ) == 0){
    return true;
  }else{return false;};
}
bool Server::delivAccept(){
  socklen_t length = sizeof(client_sockaddr);
  int foo = accept(socketID, (struct sockaddr*)&client_sockaddr, &length);
  if(foo>=0){
    connSKID = foo;return true;
  }else{return false;};
}
void Server::delivReady(){
  if( delivBind() && delivListen() && delivAccept() );
  else {perror("Server: Failed to Ready >_ ");exit(101);}
}
void Server::delivClose(){
  close(connSKID);
  close(socketID);
}
/*********************************************************/
/*******     Client     *******/
bool Client::delivConnect(){
  if(connect(socketID,(struct sockaddr *)&(server_sockaddr),sizeof(server_sockaddr)) == 0){
    return true;
  }else{return false;};
}
void Client::delivReady(){
  if(!delivConnect()){
    perror("Client: Failed to Connect >_ ");exit(201);
  }
}
void Client::delivClose(){
  close(socketID);
}
/*********************************************************/
/*******     Wking     *******/
short Server::delivWking(const char sendBf[],char recvBf[]){
  send(connSKID,sendBf,MaxBuffSize,0);
  recv(connSKID,recvBf,MaxBuffSize,0);
  cout << "send " << sendBf << endl;
  cout << "recv " << recvBf << endl;
  return 0;
}
short Client::delivWking(const char sendBf[],char recvBf[]){
  send(socketID,sendBf,MaxBuffSize,0);
  recv(socketID,recvBf,MaxBuffSize,0);
  cout << "send " << sendBf << endl;
  cout << "recv " << recvBf << endl;
  return 0;
}
