#ifndef GAME_HPP_
#define GAME_HPP_

#include <iostream>
#include <random>
#include <algorithm>

#define CHECK_DOT(X,Z) (((X) >= 0) && ((X) < (Z)))
#define POINT_ITEM(a,r,c) (*((*((a) + (r))) + (c)))

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> dist(0, 6);

enum PLAYER {HUMAN, AI, EMPTY};

typedef struct {
	int szX;
	int szY;
	PLAYER **map;
	int toWin;
} Field;

void init(Field &);


char getVal(PLAYER **, const int, const int);
void setVal(PLAYER **, const int, const int, PLAYER);
void print(Field &);
bool isEmpty(Field &, int, int);
bool isValid(Field &, int, int);
void humanTurn(Field &);
bool isDraw(Field &);
bool checkLine(Field &, int, int, int, int, int, PLAYER);
bool checkWin(Field &, PLAYER);
bool aiWinCheck(Field &);
bool humWinCheck(Field &);
void aiTurn(Field &);
bool gameCheck(Field &, PLAYER, const std::string &);

#endif
