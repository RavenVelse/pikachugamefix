#pragma once
#include "Struct.h"
#include "Console.h"

node* seeknode(node* phead, int x, int y, int size);
bool Icheck_linklist(node* phead, int x1, int y1, int x2, int y2, int size);
bool Lcheck_linklist(node* phead, int x1, int y1, int x2, int y2, int size);
bool Zcheck_linklist(node* phead, int x1, int y1, int x2, int y2, int size);
bool Ucheck_linklist(node* phead, int x1, int y1, int x2, int y2, int size);
bool AllCheckLinkList(node* phead, int x1, int y1, int x2, int y2, int size);
bool CheckLinkListNoCout(node* phead, int x1, int y1, int x2, int y2, int size);
bool ValidPairLeftLinkList(node * phead, int size, int c);
