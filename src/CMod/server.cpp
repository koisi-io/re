#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
#include "deliv.h"
#include "snkgame.h"

using std::deque;
using std::cin;
using std::cout;
using std::endl;

int main(){
  /*****   Init   *****/
  Server server;
  server.delivInit(8887,"127.0.0.1");
  server.delivReady();

  short plys = 6;
  SnakeGame snakeGame;
  snakeGame.GameInit(plys);

  for(int i=0;i<plys;++i)
    server.delivAccept();
  /*****   Init   *****/
  char recvBuf[4]="";
  stringstream ss;
  while(true){
    snakeGame.setGameInfoSS();
    for(int i=0;i<plys;++i){
      ss.str("");ss.clear();
      ss << snakeGame.GameInfoSS.str() << " "  << i;
      server.delivWking(ss.str().c_str(),recvBuf,i);
      snakeGame.dir[i] = atoi(recvBuf);
    }
    snakeGame.GameAction();
  };

  server.delivClose();

}
