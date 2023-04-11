#include "Difficult.h"
int minute2 = 8;
int second2 = 0;
bool result2 = true;
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
void LeftSliding(node* phead, int x, int y, int size)
{
	bool check = true;
	while (check == true)
	{
		for (int i = y; i < (size - 1); i++)
		{
			node* p1 = seeknode(phead, x, i, size);
			node* p2 = seeknode(phead, x, i + 1, size);
			if (p1->empty == true && p2->empty == false)
			{
				p1->c = p2->c;
				p1->empty = false;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),11);
				DrawBox(i*9+2,x*5, p1->c);
				DeleteLinkList(((i + 1) * 9)+1, x * 5, phead, x, i + 1);
			}
		}
		check = false;
		for (int i = y; i < (size - 1); i++)
		{
			node* ptemp1 = seeknode(phead, x, i, size);
			node* ptemp2 = seeknode(phead, x, i + 1, size);
			if (ptemp1->empty == true && ptemp2->empty == false)
			{
				check = true;
				break;
			}
		}
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
	node* ptemp = pcurr;
	while (loop == true && result2 == true)
	{
		pcurr = seeknode(phead, index1, index2, size);
		preve = seeknode(phead, previndex1, previndex2, size);
		nd = string(1, preve->c);
		Highlight(xprev, yprev, 8, 4, 16, 11, nd); // to den o khac sau khi da move
		previndex1 = index1;
		previndex2 = index2;
		xprev = xcurr;
		yprev = ycurr;
		nd = string(1, pcurr->c);
		ptemp = seeknode(phead, a1, a2, size);
		if (enter)
		{
			string nd1 = string(1, ptemp->c);
			Highlight(temp1, temp2, 8, 4, 15, 11, nd1); // to mau` o enter
		}
		else if (!enter)
		{
			string nd1 = string(1, ptemp->c);
			Highlight(temp1, temp2, 8, 4, 16, 11, nd1); // to den o chon sai
		}
		Highlight(xcurr, ycurr, 8, 4, 15, 11, nd); // to trang o dang di chuyen
		int ch = _getch();
		PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
		if (ch == 224)
		{
			ch = _getch();
			switch (ch)
			{
			//72 up, 80 down, 77 right, 75 left
			case 72:
				if (index1 != 0)
				{
					ycurr -= 5;
					index1--;
				}
				break;
			case 80:
				if (index1 != size - 1)
				{
					ycurr += 5;
					index1++;
				}
				break;
			case 75:
				if (index2 != 0)
				{
					xcurr -= 9;
					index2--;
				}
				break;
			case 77:
				if (index2 != size - 1)
				{
					xcurr += 9;
					index2++;
				}
				break;
			default: break;
			}
		}
		if (ch == 13)
		{
			timesenter++;
			if (timesenter == 1)
			{
				a1 = index1;
				a2 = index2;
				temp1 = xcurr, temp2 = ycurr;
				enter = true;
			}
			else if (timesenter == 2)
			{
				b1 = index1;
				b2 = index2;
				if (a1 != b1 || a2 != b2)
				{
					node* p1 = seeknode(phead, a1, a2, size);
					node* p2 = seeknode(phead, b1, b2, size);
					if (p1->c == p2->c && AllCheckLinkList(phead, a1, a2, b1, b2, size)) // neu 2 o chon co cung gia tri thi se tra ve dia chi a1 a2 va b1 b2
					{
						DeleteLinkList(temp1, temp2, phead, a1, a2);
						DeleteLinkList(xcurr, ycurr, phead, b1, b2);
						LeftSliding(phead, a1, a2, size);
						LeftSliding(phead, b1, b2, size);
						player.score += 100;
						DrawStatusBoard(player);
						loop = ValidPairLeftLinkList(phead, size, ch);
						GoTo(70, 25);
						if (!loop)
						{
							GoTo(71, 8);
							cout << "- No valid pairs left press any keys to";
							GoTo(71, 9);
							cout << " continue";
							result2 = false;
							_getch();
						}
					}
				}
				timesenter = 0;
				enter = false;
			}

		}
		else if (char(ch) == 'h')
		{
			player.score -= 200;
			DrawStatusBoard(player);
			ValidPairLeftLinkList(phead, size, ch);
		}
		else
		{
			if (char(ch) == '0')
				loop = false;
		}
	}
}

void DelteLinkListBoard(node* phead,int size)
{
	node* preve = NULL;
	int l = size * size;
	while (phead->next != NULL)
	{
		node* pcur = phead;
		for (int i = 0; i < l; i++)
		{
			preve = pcur;
			pcur = pcur->next;
		}
		delete pcur;
		preve->next = NULL;
		l--;
	}
	delete phead;
}

void  Timer2(promise<int>&& promisetotaltime)
{
	while (result2)
	{

		if (minute2 == 0 && second2 == 0)
		{
			result2 = false;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			GoTo(84, 4);
			cout << "Time over press any key";
		}
		else if (second2 == 0)
		{
			minute2--;
			second2 = 60;
		}
		else
		{
			Sleep(1000);
			second2--;
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
			GoTo(84, 4);
			cout << "            ";
			GoTo(84, 4);
			cout << minute2 << " : " << second2;
		}
	}
	int countime = minute2 * 60 + second2;
	promisetotaltime.set_value(countime);
}

void Difficult(PlayerBoard& player, int size)
{
	node* phead = new node;
	int x1 = 0, y1 = 0, x2 = 0, y2 = 0;
	CreateBoardLinkList(phead, size);
	AssignChar(phead, size);
	DisPlayBoardLinkList(phead, size);
	promise<int> totaltime;
	future<int> final_totaltime = totaltime.get_future();
	thread clock2(Timer2, move(totaltime));
	DrawStatusBoard(player);
	PlayerInputLinkList(phead, player, size, 2, 0, x1, y1, x2, y2);
	result2 = false;
	int timescore = final_totaltime.get();
	player.score += timescore;
	clock2.join();
	DelteLinkListBoard(phead,size);
	_getch();
	system("cls");
	cout << player.score;
}