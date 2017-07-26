#ifndef SNKGAME_H
#define SNKGAME_H

#include <iostream>
#include <deque>
#include <string>
#include <cmath>
#include <sstream>

using std::deque;
using std::stringstream;
/****************************************/
/****************************************/
struct Coor{
  short left;
  short top;
};
class SnakeGame{
private:
  short row;
  short col;
  struct Coor food;
  deque<struct Coor> snakeBody;
  bool isInSnakeBody(struct Coor &coor);
  void newFood();
public:
  stringstream GameInfoSS;
  short dir;
  void GameInit();
  void GameAction();
  void setGameInfoSS();
};
/****************************************/
/****************************************/
#endif
