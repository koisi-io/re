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

  short plys = 4;
  SnakeGame snakeGame;
  snakeGame.GameInit(plys);

  for(int i=0;i<plys;++i)
    server.delivAccept();
  /*****   Init   *****/

  char recvBuf[4]="";
  while(true){

    snakeGame.setGameInfoSS();
    for(int i=0;i<plys;++i){
      server.delivWking(snakeGame.GameInfoSS.str().c_str(),recvBuf,i);
      snakeGame.dir[i] = atoi(recvBuf);
      cout << "recv " << recvBuf <<"xx"<< endl;
    }
    cout << "send " << snakeGame.GameInfoSS.str().c_str() << endl;
    snakeGame.GameAction();

  };

  server.delivClose();

}
