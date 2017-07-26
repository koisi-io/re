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

  Server server;
  server.delivInit(8887,"127.0.0.1");
  server.delivReady();

  SnakeGame snakeGame;
  snakeGame.GameInit();
  
  char recvBuf[4]="";
  while(true){
    snakeGame.setGameInfoSS();
    server.delivWking(snakeGame.GameInfoSS.str().c_str(),recvBuf);
    cout << "send " << snakeGame.GameInfoSS.str().c_str() << endl;
    cout << "recv " << recvBuf << endl;
    snakeGame.dir = atoi(recvBuf);
    snakeGame.GameAction();
  };

  server.delivClose();

}
