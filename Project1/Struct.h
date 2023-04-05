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
	string name;
	char date[11];
	double score = 0;
};

struct  node
{
	char c = ' ';
	int x;
	int y;
	bool empty = false;
	node* next;
};