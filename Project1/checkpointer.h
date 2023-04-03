#pragma once
#include "Struct.h"
#include "Console.h"

bool ICheck(board** table, int x1, int y1, int x2, int y2);
bool UCheck(board** table, int x1, int y1, int x2, int y2, int size);
bool CheckPointer(board** table, int x1, int y1, int x2, int y2, int size);
bool ValidPairLeft(board** table, int size, int c);