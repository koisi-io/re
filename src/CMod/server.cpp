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
  snakeGame.GameInit(4);

  char recvBuf[4]="";
  while(true){

    // char debug[]="-101 -102 7 5 7 6 7 7 7 8 -102 -103 0 1 0 2 0 3 0 4 -103 -103 3 1 3 2 3 3 -103 -101";
    // server.delivWking(debug,recvBuf);
    // cout << "send " << debug << endl;
    // cout << "recv " << recvBuf << endl;
    // snakeGame.dir[0] = atoi(recvBuf);
    // snakeGame.GameAction();
    snakeGame.setGameInfoSS();
    server.delivWking(snakeGame.GameInfoSS.str().c_str(),recvBuf);
    cout << "send " << snakeGame.GameInfoSS.str().c_str() << endl;
    cout << "recv " << recvBuf << endl;
    snakeGame.dir[0] = atoi(recvBuf);
    snakeGame.GameAction();
  };

  server.delivClose();

}
