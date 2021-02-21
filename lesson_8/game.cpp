#include "game.hpp"

char getVal(PLAYER **array, const int row, const int col) {
	return POINT_ITEM(array, row, col);
}
void setVal(PLAYER **array, const int row, const int col, PLAYER value) {
	POINT_ITEM(array, row, col) = value;
}

void init(Field &field) {
	field.toWin = 5;
	field.szX = 7;
	field.szY = 7;
	field.map = (PLAYER **) calloc(field.szX, sizeof(PLAYER *));
	for (int y = 0; y < field.szY; y++) {
		*(field.map + y) = (PLAYER *) calloc(field.szX, sizeof(PLAYER));
		for (int x = 0; x < field.szX; x++) {
			setVal(field.map, y, x, EMPTY);
		}
	}
}
void print(Field &field) {
	//#include <windows.h>
	//system("cls");
	std::system("clear");
	std::cout << "-1-2-3-4-5-6-7-\n";
	for (int y = 0; y < field.szY; y++) {
		std::cout << (y + 1);
		for (int x = 0; x < field.szX; x++) {
			std::cout << getVal(field.map, y, x) << "|";
		}
		std::cout << std::endl;
	}
}
bool isEmpty(Field &field, int x, int y) {
	return getVal(field.map, y, x) == EMPTY;
}
bool isValid(Field &field, int x, int y) {
	return CHECK_DOT(x, field.szX) && CHECK_DOT(y, field.szY);
}
void humanTurn(Field &field) {
	int x;
	int y;
	bool isError = false;
	do {
		if (isError)
			std::cout << "your coordinates were entered wrong!, field size is..." << std::endl;
		std::cout << "Введите координаты хода X и Y (от 1 до 3) через пробел >>" << std::endl;
		// <regex>
		std::cin >> x;
		std::cin.ignore(1);
		std::cin >> y;
		// scanf("%d %d", &x, &y);
		// todo check if numbers are entered
		x--; y--;
		isError = true;
	} while (!isValid(field, x, y) || !isEmpty(field, x, y));
	setVal(field.map, y, x, HUMAN);
}
bool isDraw(Field &field) {
	for (int y = 0; y < field.szY; y++)
		for (int x = 0; x < field.szX; x++)
			if (isEmpty(field, x, y))
				return false;
	return true;
}
bool checkLine(Field &field, int y, int x, int vx, int vy, int len, PLAYER c) {
	const int endX = x + (len - 1) * vx;
	const int endY = y + (len - 1) * vy;
	if (!isValid(field, endX, endY))
		return false;
	for (int i = 0; i < len; i++) {
		if (getVal(field.map, (y + i * vy), (x + i * vx)) != c)
			return false;
	}
	return true;
}
bool checkWin(Field &field, PLAYER c) {
	for (int y = 0; y < field.szY; y++) {
		for (int x = 0; x < field.szX; x++) {
			if (getVal(field.map, y, x) == EMPTY)
				continue;
			if (checkLine(field, y, x, 1, 0, field.toWin, c)) return true;
			if (checkLine(field, y, x, 1, 1, field.toWin, c)) return true;
			if (checkLine(field, y, x, 0, 1, field.toWin, c)) return true;
			if (checkLine(field, y, x, 1, -1, field.toWin, c)) return true;
		}
	}
	return false;
}

bool aiWinCheck(Field &field) {
	for (int y = 0; y < field.szY; y++) {
		for (int x = 0; x < field.szX; x++) {
			if (isEmpty(field, x, y)) {
				setVal(field.map, y, x, AI);
				if (checkWin(field, AI))
					return true;
				setVal(field.map, y, x, EMPTY);
			}
		}
	}
	return false;
}

bool humWinCheck(Field &field) {
	for (int y = 0; y < field.szY; y++) {
		for (int x = 0; x < field.szX; x++) {
			if (isEmpty(field, x, y)) {
				setVal(field.map, y, x, HUMAN);
				if (checkWin(field, HUMAN)) {
					setVal(field.map, y, x, AI);
					return true;
				}
				setVal(field.map, y, x, EMPTY);
			}
		}
	}
	return false;
}


void aiTurn(Field &field) {
	if (aiWinCheck(field)) return;
	if (humWinCheck(field)) return;
	int x;
	int y;
	do {
		x = dist(mt);
		y = dist(mt);
	} while (!isEmpty(field, x, y));
	setVal(field.map, y, x, AI);
}

bool gameCheck(Field &field, PLAYER dot, const std::string &winString) {
	print(field);
	if (checkWin(field, dot)) {
		std::cout << winString << std::endl;
		return true;
	}
	if (isDraw(field)) {
		std::cout << "Draw!" << std::endl;
		return true;
	}
	return false;
}
