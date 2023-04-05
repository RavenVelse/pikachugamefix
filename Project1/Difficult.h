#pragma once
#include "Console.h"
#include "Struct.h"
#include "Utility.h"

node* CreateBoardLinkList(node* phead, int size);
node* seeknode(node* phead, int x, int y, int size);
void AssignChar(node* phead, int size);
void DisPlayBoardLinkList(node* phead, int size);
void Difficult(PlayerBoard& player, int size);