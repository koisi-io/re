#include <stdlib.h>
#include "snkgame.h"
/********************************************************/
/********************************************************/
void SnakeGame::GameInit(){
  row = 16; col = 24; dir = 1;
  struct Coor coor = {0,0};
  for(int i=0;i<5;++i){
    coor.left=i;coor.top=0;
    snakeBody.push_back(coor);
  }
  food.left=7;food.top=2;
}
/****************************************/
/****************************************/
bool SnakeGame::isInSnakeBody(struct Coor &coor){
  for(int i=0;i<snakeBody.size();++i){
    if((snakeBody[i].left == coor.left)&&(snakeBody[i].top == coor.top))
      return true;
  }
  return false;
}
void SnakeGame::newFood(){
  do{
    food.left = rand()%col;
    food.top = rand()%row;
  }while(isInSnakeBody(food));
}
/********************************************************/
/********************************************************/
void SnakeGame::GameAction(){
  /****************************************/
  /***  Add the new head to snake body  ***/
  struct Coor head = snakeBody[0];
  switch (dir) {
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
  snakeBody.push_front(head);
  /****************************************/
  /***             Eat food             ***/
  if((head.left==food.left)&&(head.top==food.top)){
    snakeBody.push_back(food);
    newFood();
  }
  /****************************************/
  /***            Remove tail           ***/
  snakeBody.pop_back();
  /****************************************/
}
/********************************************************/
/********************************************************/
void SnakeGame::setGameInfoSS(){
  GameInfoSS.clear();
  GameInfoSS.str("");
  GameInfoSS<<"-101 ";
  GameInfoSS << food.left << " " << food.top << " ";
  for(int i=0;i<snakeBody.size();++i){
    GameInfoSS << snakeBody[i].left << " " << snakeBody[i].top << " ";
  }
  GameInfoSS<<"-101";
}
