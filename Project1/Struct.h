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
	unsigned short num;
	char name[40];
	char date[11];
	double score;
};
