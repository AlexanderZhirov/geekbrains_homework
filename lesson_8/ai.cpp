#include "ai.hpp"

std::random_device rd;
std::mt19937 mt(rd());

void aiTurn(map *m)
{
	std::uniform_int_distribution<int> dist(0, m->size - 1);

	if (aiWinCheck(m)) return;
	if (humWinCheck(m)) return;
	int x;
	int y;
	do {
		y = dist(mt);
		x = dist(mt);
	} while (m->cells[x][y]->p != EMPTY);
	setVal(m->cells[x][y], AI, true);
}

bool aiWinCheck(map *m)
{
	for (int y = 0; y < m->size; y++)
	{
		for (int x = 0; x < m->size; x++)
		{
			cell *c = m->cells[y][x];

			if (c->p == EMPTY)
			{
				setVal(c, AI, true);
				if (checkWin(m, AI))
					return true;
				setVal(c, EMPTY);
			}
		}
	}
	return false;
}

bool humWinCheck(map *m)
{
	for (int y = 0; y < m->size; y++)
	{
		for (int x = 0; x < m->size; x++)
		{
			cell *c = m->cells[y][x];

			if (c->p == EMPTY)
			{
				setVal(c, HUMAN, true);
				if (checkWin(m, HUMAN))
				{
					setVal(c, AI, true);
					return true;
				}
				setVal(c, EMPTY);
			}
		}
	}

	return false;
}

void setVal(cell *c, PLAYER p, bool draw)
{
	c->p = p;
	c->is_draw = draw;
}

bool checkWin(map *m, PLAYER p)
{
	for (int y = 0; y < m->size; y++)
	{
		for (int x = 0; x < m->size; x++)
		{
			if (m->cells[y][x]->p == EMPTY) continue;
			if (checkLine(m, y, x, 0, 1, m->toWin, p)) return true;
			if (checkLine(m, y, x, 1, 1, m->toWin, p)) return true;
			if (checkLine(m, y, x, 1, 0, m->toWin, p)) return true;
			if (checkLine(m, y, x, -1, 1, m->toWin, p)) return true;
		}
	}

	return false;
}

bool checkLine(map *m, int y, int x, int vy, int vx, int len, PLAYER p)
{
	const int endX = x + (len - 1) * vx;
	const int endY = y + (len - 1) * vy;

	if (!isValid(m, endX, endY))
		return false;

	for (int i = 0; i < len; i++)
	{
		if (m->cells[y + i * vy][x + i * vx]->p != p)
			return false;
	}

	return true;
}

bool isValid(map *m, int y, int x)
{
	return CHECK_DOT(y, m->size) && CHECK_DOT(x, m->size);
}

bool isDraw(map *m)
{
	for (int y = 0; y < m->size; y++)
		for (int x = 0; x < m->size; x++)
			if (m->cells[y][x]->p == EMPTY)
				return false;
	return true;
}

