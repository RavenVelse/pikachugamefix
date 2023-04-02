#include"Normal.h"

void CreateBoard(board** table, int w, int h)
{
	for (int i = 0; i < w; i++)
	{
		table[i] = new board[h]; // khoi tao table
	}
	int count = 0;
	srand(time(NULL));
	for (int i = 0; i < (w * h) / 2; i++)
	{
		count = 2;
		char c = 65 + rand() % 26;
		while (count != 0) // tim 2 o trong de bo chu cai vao`
		{
			int x = rand() % w;
			int y = rand() % h;
			if (table[x][y].empty)
			{
				table[x][y].c = c;
				table[x][y].empty = false;
				count--;
			}
		}
	}

}

void DisplayBoard(board** table, int size)
{
	string str;
	CreateBoard(table, size, size);
	int x = 2, y = 2;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11);
	for (int i = 0; i < size; i++)
	{
		x = 2;
		for (int j = 0; j < size; j++)
		{
			DrawBox(x, y, table[i][j].c);
			x += 8;
		}
		y += 4;
	}
}

// Move with arrow key and press enter to choose box
void PlayerInput(board** table, int size, int x, int y, int& a1, int& a2, int& b1, int& b2)
{
	bool loop = true;
	int xcurr = x - 1, ycurr = y;
	int xprev = xcurr, yprev = ycurr;
	int index1 = 0, index2 = 0, temp1 = xcurr, temp2 = ycurr;
	int previndex1 = index1, previndex2 = index2;
	bool enter = false;
	int timesenter = 0;
	string nd;

	while (loop)
	{
		board curr = table[index1][index2];
		nd = string(1, table[previndex1][previndex2].c);
		Highlight(xprev, yprev, 8, 4, 16, 11, nd);
		previndex1 = index1;
		previndex2 = index2;
		xprev = xcurr;
		yprev = ycurr;
		nd = string(1, table[index1][index2].c);
		if (enter)
		{
			string nd1 = string(1, table[a1][a2].c);
			Highlight(temp1, temp2, 8, 4, 15, 11, nd1); // Hightlight the chosen box
		}
		Highlight(xcurr, ycurr, 8, 4, 15, 11, nd);
		int ch = _getch();
		if (ch == 224)
		{
			ch = _getch();
			switch (ch)
			{
				//72:up, 80:down, 77:right, 75:left
			case 72:
				if (index1 != 0)
				{
					ycurr -= 4;
					index1--;
				}
				break;
			case 80:
				if (index1 != size - 1)
				{
					ycurr += 4;
					index1++;
				}
				break;
			case 75:
				if (index2 != 0)
				{
					xcurr -= 8;
					index2--;
				}
				break;
			case 77:
				if (index2 != size - 1)
				{
					xcurr += 8;
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
			}
			else if (timesenter == 2)
			{
				b1 = index1;
				b2 = index2;
				if (table[a1][a2].c == table[b1][b2].c) // neu 2 o chon co cung gia tri thi se tra ve dia chi a1 a2 va b1 b2
				{
					loop = false;
				}
				timesenter--;
			}
			enter = true;
		}
		else
		{
			if (char(ch) == '0')
				loop = false;
		}
	}
}