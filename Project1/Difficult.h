#pragma once
#include "Console.h"
#include "Struct.h"
#include "Utility.h"
#include "checklinklisted.h"
node* CreateBoardLinkList(node* phead, int size);

void AssignChar(node* phead, int size);
void DisPlayBoardLinkList(node* phead, int size);
void Difficult(PlayerBoard& player, int size);