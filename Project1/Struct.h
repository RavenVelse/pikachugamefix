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
	double score = 0;
	char pass[20];
	bool achive1 =0;
	bool achive2 = 0;
	bool achive3 = 0;
};

struct  node
{
	char c = ' ';
	int x;
	int y;
	bool empty = false;
	node* next;
};