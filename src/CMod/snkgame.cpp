#include <stdlib.h>
#include "snkgame.h"
/********************************************************/
/********************************************************/
void SnakeGame::GameInit(const short &plys){
  row = 16; col = 24; players = plys;

  for(int i=0;i<players;++i) dir.push_back(1);

  food[0].left=8;food[0].top=2;food[1].left=8;food[1].top=4;
  food[2].left=10;food[2].top=10;food[3].left=10;food[3].top=12;

  deque<struct Coor> oneSnake;
  struct Coor oneBody;
  for(int i=0;i<players;++i){
    oneSnake.clear();
    for(int k=0;k<4;++k){
      oneBody.left=10*(i%2);oneBody.top=i*2+k;
      oneSnake.push_back(oneBody);
    }
    snakeBody.push_back(oneSnake);
  }
}
/****************************************/
/****************************************/
bool SnakeGame::isInSnakeBody(const struct Coor &coor,const short &snake){
  for(int i=0;i<snakeBody[snake].size();++i){
    if((snakeBody[snake][i].left == coor.left)&&(snakeBody[snake][i].top == coor.top))
      return true;
  }
  return false;
}
bool SnakeGame::isInFood(const struct Coor &coor){
  for(int i=0;i<FOODS;++i){
    if((food[i].left == coor.left)&&(food[i].top == coor.top))
      return true;
  }
  return false;
}
void SnakeGame::newFood(short foo){
  struct Coor temp;
  temp.left = rand()%col;
  temp.top = rand()%row;
  for(int snk=0;snk<players;++snk)
    { if(isInSnakeBody(temp,snk)) return newFood(foo);}
  if( isInFood(temp) ){ return newFood(foo);}
  food[foo].left=temp.left;
  food[foo].top=temp.top;
}
/********************************************************/
/********************************************************/
void SnakeGame::SnakeAction(const short &snake){
  /****************************************/
  /***  Add the new head to snake body  ***/
  struct Coor head = snakeBody[snake][0];
  switch (dir[snake]) {
    case 1: ++head.left;break;
    case 2: --head.left;break;
    case 3: --head.top;break;
    case 4: ++head.top;break;
    default: break;
  }
  if(head.left>col-1)head.left=0;
  if(head.left<0)head.left=col-1;
  if(head.top>row-1)head.top=0;
  if(head.top<0)head.top=row-1;
  snakeBody[snake].push_front(head);
  /****************************************/
  /***             Eat food             ***/
  for(int i=0;i<FOODS;++i){
    if((head.left==food[i].left)&&(head.top==food[i].top)){
      snakeBody[snake].push_back(food[i]); // Then pop it
      newFood(i);break;
    }
  }
  /****************************************/
  /***            Remove tail           ***/
  snakeBody[snake].pop_back();
  /****************************************/
}
void SnakeGame::GameAction(){
  for(int i=0;i<players;++i)
    SnakeAction(i);
}
/********************************************************/
/********************************************************/
void SnakeGame::setGameInfoSS(){
  //  -101 ss block
  //  -102 foo block
  //  -103 arr-snk block
  //  -104 one-snk block

  GameInfoSS.clear();
  GameInfoSS.str("");

  GameInfoSS<<"-101 ";

  GameInfoSS<<"-102 ";
  for(int i=0;i<FOODS;++i)
    GameInfoSS << food[i].left << " " << food[i].top << " ";
  GameInfoSS<<"-102 ";

  GameInfoSS<<"-103 ";
  for(int i=0;i<players;++i){
    GameInfoSS<<"-104 ";
    for(int k=0;k<snakeBody[i].size();++k){
      GameInfoSS << snakeBody[i][k].left << " " << snakeBody[i][k].top << " ";
    }
    GameInfoSS<<"-104 ";
  }
  GameInfoSS<<"-103 ";

  GameInfoSS<<"-101";
}
