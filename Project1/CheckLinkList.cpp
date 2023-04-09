#include "checklinklisted.h"

bool Icheck_linklist(node* phead,int x1,int y1,int x2,int y2,int size)
{
	node* p1 = seeknode(phead, x1, y1, size);
	node* p2 = seeknode(phead, x2, y2, size);
	int max = 0, min = 0;
	if (x1 == x2)
	{
		if (y2 - y1 == 1 || y2 - y1 == -1)
		{
			return true;
		}
		if (y1 < y2)
		{
			min = y1;
			max = y2;
		}
		else
		{
			min = y2;
			max = y1;
		}
		for (int i = min + 1; i < max; i++)
		{
			node* pcur = seeknode(phead, x1, i, size);
			if (pcur->empty == false)
			{
				return false;
			}
		}
		return true;
	}
	else if (y1 == y2)
	{
		if (x2 - x1 == 1 || x2 - x1 == -1) 
		{
			return true;
		}
		if (x1 < x2)
		{
			min = x1;
			max = x2;
		}
		else
		{
			min = x2;
			max = x1;
		}
		for (int i = min + 1; i < max; i++)
		{
			node* pcur = seeknode(phead, i, y1, size);
			if (pcur->empty == false)
			{
				return false;
			}
		}
		return true;
	}
	return false;
}

bool Lcheck_linklist(node* phead, int x1, int y1, int x2, int y2, int size)
{
	node* p1 = seeknode(phead, x1, y2, size);
	node* p2 = seeknode(phead, x2, y1, size);
	bool check1, check2;
	if (p1->empty == false && p2->empty == false)
	{
		return false;
	}
	if (p1->empty == true)
	{
		check1 = Icheck_linklist(phead, x1, y1, x1, y2,size);
		check2 = Icheck_linklist(phead, x2, y2, x1, y2,size);
		if (check1 == true && check2 == true)
		{
			return true;
		}
	}
	if (p2->empty == true)
	{
		check1 = Icheck_linklist(phead, x1, y1, x2, y1, size);
		check2 = Icheck_linklist(phead, x2, y2, x2, y1, size);
		if (check1 == true && check2 == true)
		{
			return true;
		}
	}
	return false;
}

node* seeknode(node* phead, int x, int y, int size)
{
	while (phead != NULL)
	{
		if (phead->x == x && phead->y == y)
		{
			return phead;
		}
		phead = phead->next;
	}
}


bool AllCheckLinkList(node* phead,int x1,int y1,int x2,int y2,int size)
{
	node* temp = seeknode(phead, x1, y1, size);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	if (Icheck_linklist(phead,x1,y1,x2,y2,size))
	{
		GoTo(85, 5);
		cout << temp->c;
		GoTo(89, 6);
		cout << "I check";
	}
}