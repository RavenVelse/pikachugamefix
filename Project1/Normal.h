#pragma once
#include "Console.h"
#include"Struct.h"
#include "Normal.h"
#include"Utility.h"
#include"checkpointer.h"
void CreateBoard(board** table, int w, int h);
void DisplayBoard(board** table, int size);
void PlayerInput(board** table, int size, int x, int y, int& a1, int& a2, int& b1, int& b2,PlayerBoard& player);
void Normal(PlayerBoard p, int size);
void  Timer(promise<int> && promisetotaltime);