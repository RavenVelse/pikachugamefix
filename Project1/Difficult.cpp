#include "Difficult.h"

node* CreateBoardLinkList(node* phead, int size)
{
	node* pcurr = phead;
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			phead->x = i;
			phead->y = j;
			phead->c = ' ';
			phead->next = new node;
			phead = phead->next;
		}
	}
	return pcurr;
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
void AssignChar(node* phead, int size)
{
	srand(time(NULL));
	for (int i = 0; i < (size * size) / 2; i++)
	{
		node* temp = phead;
		int count = 2;
		char c = 65 + rand() % 26;
		while (count != 0)
		{
			int x = rand() % size;
			int y = rand() % size;
			temp = phead;
			for (int i = 0; i < size * size; i++)
			{
				if (temp->x == x && temp->y == y && temp->c == ' ')
				{
					temp->c = c;
					count--;
					break;
				}
				temp = temp->next;
			}
		}
	}
}

void DisPlayBoardLinkList(node* phead, int size)
{
	int x = 0, y = 0;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	for (int i = 0; i < size; i++)
	{
		x = 2;
		for (int j = 0; j < size; j++)
		{
			DrawBox(x, y, phead->c);
			phead = phead->next;
			x += 9;
		}
		y += 5;
	}
}

void PlayerInputLinkList(node* phead, PlayerBoard& player, int size, int x, int y, int& a1, int& a2, int& b1, int& b2)
{
	bool loop = true;
	int xcurr = x - 1, ycurr = y;
	int xprev = xcurr, yprev = ycurr, temp1 = xcurr, temp2 = ycurr;
	int index1 = 0, index2 = 0;
	int previndex1 = index1, previndex2 = index2;
	bool enter = false;
	int timesenter = 0;
	string nd;
	node* pcurr = phead;
	node* preve = pcurr;
	while (loop)
	{

		nd = string(1, pcurr->c);
		Highlight(xprev, yprev, 8, 4, 16, 11, nd); // to den o khac sau khi da move
		previndex1 = index1;
		previndex2 = index2;
		xprev = xcurr;
		yprev = ycurr;
		nd = string(1, pcurr->c);
	}
}

void Difficult(PlayerBoard& player, int size)
{
	node* phead = new node;
	CreateBoardLinkList(phead, size);
	AssignChar(phead, size);
	DisPlayBoardLinkList(phead, size);
	int x = 0, y = 0;

}