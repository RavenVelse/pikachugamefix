#include "checklinklisted.h"

bool Icheck_linklist(node* phead, int x1, int y1, int x2, int y2, int size)
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
		check1 = Icheck_linklist(phead, x1, y1, x1, y2, size);
		check2 = Icheck_linklist(phead, x2, y2, x1, y2, size);
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

bool Zcheck_linklist(node* phead, int x1, int y1, int x2, int y2, int size)
{
	int min = 0, max = 0;
	bool check1 = false;
	bool check2 = false;
	bool check3 = false;
	node* p1;
	node* p2;
	if (x1 == x2 || y1 == y2)
	{
		return false;
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
	for (int i = min + 1; i < max; i++) {
		check1 = Icheck_linklist(phead, i, y1, i, y2, size);
		p1 = seeknode(phead, i, y1, size);
		p2 = seeknode(phead, i, y2, size);
		if (check1 == true && p1->empty == true && p2->empty == true) {
			check2 = Icheck_linklist(phead, x1, y1, i, y1, size);
			check3 = Icheck_linklist(phead, x2, y2, i, y2, size);
			if (check2 && check3) {
				return true;
			}
		}
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
		check1 = Icheck_linklist(phead, x1, i, x2, i, size);
		p1 = seeknode(phead, x1, i, size);
		p2 = seeknode(phead, x2, i, size);
		if (check1 == true && p1->empty == true && p2->empty == true) {
			check2 = Icheck_linklist(phead, x1, y1, x1, i, size);
			check3 = Icheck_linklist(phead, x2, y2, x2, i, size);
			if (check2 && check3) {
				return true;
			}
		}
	}
	return false;
}

bool Ucheck_linklist(node* phead, int x1, int y1, int x2, int y2, int size)
{
	if (x1 == x2 && x1 == 0 || y1 == y2 && y1 == 0 || x1 == x2 && x1 == size - 1 || y1 == y2 && y1 == size - 1)
		return true;
	bool check1 = false, check2 = false, check3 = false;
	int min = 0, max = 0;
	node* p1;
	node* p2;
	//Check U ngang
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
	for (int i = 0; i < size; i++)
	{
		if (i == 0 || i == size - 1)
		{
			check2 = Icheck_linklist(phead, x1, y1, x1, i, size);
			check3 = Icheck_linklist(phead, x2, y2, x2, i, size);
			p1 = seeknode(phead, x1, i, size);
			p2 = seeknode(phead, x2, i, size);
			if (check2 && check3 && p1->empty == true && p2->empty == true || check2 && y2 == i && p1->empty == true || check3 && y1 == i && p2->empty == true)
			{
				return true;
			}
		}
		else if (i <= min || i >= max)
		{
			check1 = (Icheck_linklist(phead, x1, i, x2, i, size));
			if (check1)
			{
				check2 = Icheck_linklist(phead, x1, y1, x1, i, size);
				check3 = Icheck_linklist(phead, x2, y2, x2, i, size);
				p1 = seeknode(phead, x1, i, size);
				p2 = seeknode(phead, x2, i, size);
				if (check2 && check3 && p1->empty == true && p2->empty == true)
				{
					return true;
				}
			}
		}
	}
	// Chech U doc
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
	for (int i = 0; i < size; i++)
	{
		if (i == 0 || i == size - 1)
		{
			check2 = Icheck_linklist(phead, x1, y1, i, y1, size);
			check3 = Icheck_linklist(phead, x2, y2, i, y2, size);
			p1 = seeknode(phead, i, y1, size);
			p2 = seeknode(phead, i, y2, size);
			if (check2 && check3 && p1->empty == true && p2->empty == true || check2 && p1->empty && x2 == i || check3 && p2->empty && x1 == i)
			{
				return true;
			}
		}
		else if (i <= min || i >= max)
		{
			check1 = (Icheck_linklist(phead, i, y1, i, y2, size));
			if (check1)
			{
				check2 = Icheck_linklist(phead, x1, y1, i, y1, size);
				check3 = Icheck_linklist(phead, x2, y2, i, y2, size);
				p1 = seeknode(phead, i, y1, size);
				p2 = seeknode(phead, i, y2, size);
				if (check2 && check3 && p1->empty == true && p2->empty == true)
				{
					return true;
				}
			}
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


bool AllCheckLinkList(node* phead, int x1, int y1, int x2, int y2, int size)
{
	node* temp = seeknode(phead, x1, y1, size);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	if (Icheck_linklist(phead, x1, y1, x2, y2, size))
	{
		GoTo(85, 5);
		cout << temp->c;
		GoTo(89, 6);
		cout << "I check";
		return true;
	}
	if (Lcheck_linklist(phead, x1, y1, x2, y2, size))
	{
		GoTo(85, 5);
		cout << temp->c;
		GoTo(89, 6);
		cout << "L check";
		return true;
	}
	if (Zcheck_linklist(phead, x1, y1, x2, y2, size))
	{
		GoTo(85, 5);
		cout << temp->c;
		GoTo(89, 6);
		cout << "Z check";
		return true;
	}
	if (Ucheck_linklist(phead, x1, y1, x2, y2, size))
	{
		GoTo(85, 5);
		cout << temp->c;
		GoTo(89, 6);
		cout << "U check";
		return true;
	}
	return false;
}

bool CheckLinkListNoCout(node* phead, int x1, int y1, int x2, int y2, int size)
{
	if (Icheck_linklist(phead, x1, y1, x2, y2, size))
	{
		return true;
	}
	if (Lcheck_linklist(phead, x1, y1, x2, y2, size))
	{
		return true;
	}
	if (Zcheck_linklist(phead, x1, y1, x2, y2, size))
	{
		return true;
	}
	if (Ucheck_linklist(phead, x1, y1, x2, y2, size))
	{
		return true;
	}
	return false;
}

bool ValidPairLeftLinkList(node* phead, int size, int c)
{
	int l = 0, k = 0;
	while (l < size)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (l != i || k != j)
				{
					node* p1 = seeknode(phead, l, k, size);
					node* p2 = seeknode(phead, i, j, size);
					if (CheckLinkListNoCout(phead, l, k, i, j, size) == true && p1->empty == false && p1->c == p2->c)
					{
						if (char(c) == 'h')
						{
							GoTo(79, 7);
							cout << "cell(" << l << ", " << k << ") and cell(" << i << ", " << j << ")";
						}
						return true;
					}
				}
			}
		}
		if (k < size - 1)
		{
			k++;
		}
		else
		{
			l++;
			k = 0;
		}
	}
	return false;
}