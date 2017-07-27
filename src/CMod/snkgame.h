#ifndef SNKGAME_H
#define SNKGAME_H

#include <iostream>
#include <deque>
#include <string>
#include <cmath>
#include <sstream>
#include <vector>

using std::vector;
using std::deque;
using std::stringstream;

static const short FOODS = 4;
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
  short players;
  struct Coor food[FOODS];
  vector< deque<struct Coor> > snakeBody;
  bool isInFood(const struct Coor &coor);
  bool isInSnakeBody(const struct Coor &coor,const short &snake);
  void newFood(short foo);
public:
  stringstream GameInfoSS;
  vector<short> dir;
  void GameInit(const short &plys);
  void SnakeAction(const short &snake);
  void GameAction();
  void setGameInfoSS();
};
/****************************************/
/****************************************/
#endif
