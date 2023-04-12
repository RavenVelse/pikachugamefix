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

}

void Difficult(PlayerBoard& player, int size)
{	
	int mode;
	node* phead = new node;
	CreateBoardLinkList(phead, size);
	AssignChar(phead, size);
	DisPlayBoardLinkList(phead, size);
	_getch();
	MainMenu(player, mode, size);
}