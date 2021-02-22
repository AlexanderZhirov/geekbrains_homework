#ifndef AI_HPP_
#define AI_HPP_

#include <iostream>
#include <random>
#include <algorithm>
#include "map.hpp"

#define CHECK_DOT(X, Y) ((X) >= 0 && (X) < (Y))

void aiTurn(map *);
bool aiWinCheck(map *);
bool humWinCheck(map *);
void setVal(cell *, PLAYER, bool = false);
bool checkWin(map *, PLAYER);
bool checkLine(map *, int, int, int, int, int, PLAYER);
bool isValid(map *, int, int);
bool isDraw(map *m);

#endif
