#pragma once
#include"Console.h"
#include"Normal.h"
#include"Utility.h"

struct board
{
	int x, y;
	bool empty = true;
	char c;
	int w, h;
}; struct PlayerBoard
{
	string num;
	string name;
	string date;
	string score;
};
