#pragma once
#include <string>

using namespace std;

struct board
{
	int x, y;
	bool empty = true;
	char c;
	int w, h;
}; 
struct PlayerBoard
{
	string num;
	string name;
	string date;
	string score;
};
