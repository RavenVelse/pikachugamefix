#include "checkpointer.h"

bool ICheck(board** table, int x1, int y1, int x2, int y2)
{
	int min = 0, max = 0;
	if (x1 == x2)
	{
		if ((y1 - y2) == 1 || (y1 - y2) == -1)
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
			if (!table[x1][i].empty)
				return false;
		}
		return true;
	}

	else if (y1 == y2)
	{
		if ((x1 - x2) == -1 || (x1 - x2) == 1)
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
			if (!table[i][y1].empty)
				return false;
		}
		return true;
	}
	return false;
}
//Reference : phvanmin/pikachu 
bool UCheck(board** table, int x1, int y1, int x2, int y2, int size)
{
	if (x1 == x2 && x1 == 0 || y1 == y2 && y1 == 0 || x1 == x2 && x1 == size -1 || y1 == y2 && y1 == size - 1)
		return true;
	bool check1 = false, check2 = false, check3 = false;
	int min = 0, max = 0;
	//Check U ngang
	if ( y1 < y2)
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
		if (i == 0 || i == size -1)
		{
			check2 = ICheck(table, x1, y1, x1, i);
			check3 = ICheck(table, x2, y2, x2, i);
			if (check2 && check3 && table[x1][i].empty == true && table[x2][i].empty == true || check2 && y2 == i && table[x1][i].empty == true || check3 && y1 == i && table[x2][i].empty == true)
			{
				return true;
			}
		}
		else if (i <= min || i >= max) 
		{
			check1 = (ICheck(table, x1, i, x2, i) );
			if (check1)
			{
				check2 = ICheck(table, x1, y1, x1, i);
				check3 = ICheck(table, x2, y2, x2, i);
				if (check2 && check3 && table[x1][i].empty == true && table[x2][i].empty == true) 
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
		if (i == 0 || i == size -1)
		{
			check2 = ICheck(table, x1, y1, i, y1);
			check3 = ICheck(table, x2, y2, i, y2);
			if (check2 && check3 && table[i][y1].empty == true && table[i][y2].empty ==true || check2 && table[i][y1].empty && x2 == i || check3 && table[i][y2].empty && x1 == i)
			{
				return true;
			}
		}
		else if (i <= min || i >= max)
		{
			check1 = (ICheck(table, i, y1, i, y2));
			if (check1)
			{
				check2 = ICheck(table, x1, y1, i, y1);
				check3 = ICheck(table, x2, y2, i, y2);
				if (check2 && check3 && table[i][y1].empty == true && table[i][y2].empty == true)
				{
					return true;
				}
			}
		}
	}
	return false;
}
bool LCheck(board** table, int x1, int y1, int x2, int y2) {
	bool check1 = false;
	bool check2 = false;
	if (table[x1][y2].empty == false && table[x2][y1].empty == false) {
		return false;
	}
	if (table[x1][y2].empty == true) {
		check1 = ICheck(table, x1, y1, x1, y2);
		check2 = ICheck(table, x1, y2, x2, y2);
		if (check1 == true && check2 == true) {
			return true;
		}
	}
	if (table[x2][y1].empty == true) {
		check1 = ICheck(table, x1, y1, x2, y1);
		check2 = ICheck(table, x2, y1, x2, y2);
		if (check1 == true && check2 == true) {
			return true;
		}
	}
	return false;
}
bool ZCheck(board**table, int x1, int y1, int x2, int y2) 
{
	int min = 0, max = 0;
	bool check1 = false;
	bool check2 = false;
	bool check3 = false;
	if (x1 == x2 || y1 == y2 )
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
		check1 = ICheck(table, i, y1, i, y2);
		if (check1 == true && table[i][y1].empty == true && table[i][y2].empty == true) {
			check2 = ICheck(table, x1, y1, i, y1);
			check3 = ICheck(table, x2, y2, i, y2);
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
	for (int i = min + 1; i < max; i++) {
		check1 = ICheck(table, x1, i, x2, i);
		if (check1 == true && table[x1][i].empty == true && table[x2][i].empty == true) {
			check2 = ICheck(table, x1, y1, x1, i);
			check3 = ICheck(table, x2, y2, x2, i);
			if (check2 && check3) {
				return true;
			}
		}
	}
	return false;
}
bool CheckPointer(board** table, int x1, int y1, int x2, int y2, int size)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	if (ICheck(table, x1, y1, x2, y2)) 
	{
		GoTo(85, 5);
		cout << table[x1][y1].c;
		GoTo(89, 6);
		cout << " I match";
		return true;
	}
	if (LCheck(table, x1, y1, x2, y2)) 
	{
		GoTo(85, 5);
		cout << table[x1][y1].c;
		GoTo(89, 6);
		cout << "L match";
		return true;
	}
	if (ZCheck(table, x1, y1, x2, y2)) 
	{
		GoTo(85, 5);
		cout << table[x1][y1].c;
		GoTo(89, 6);
		cout << "Z match";
		return true;
	}
	if (UCheck(table, x1, y1, x2, y2, size)) 
	{
		GoTo(85, 5);
		cout << table[x1][y1].c;
		GoTo(89, 6);
		cout << "U match";
		return true;
	}
	return false;
}

bool CheckPointerNoCout(board** table, int x1, int y1, int x2, int y2, int size)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
	if (ICheck(table, x1, y1, x2, y2))
	{
		return true;
	}
	if (LCheck(table, x1, y1, x2, y2))
	{
		return true;
	}
	if (ZCheck(table, x1, y1, x2, y2))
	{
		return true;
	}
	if (UCheck(table, x1, y1, x2, y2, size))
	{
		return true;
	}
	return false;
}

bool ValidPairLeft(board** table, int size,int c)
{
	int l = 0, k = 0;
	while (l < size)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if ( l != i || k != j )
				{
					if (CheckPointerNoCout(table, l, k, i, j, size) == true && table[l][k].empty == false && table[i][j].c == table[l][k].c)
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
		if (k < size -1)
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