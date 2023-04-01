#include "checkpointer.h"

bool NextToCheck(board** table, int x1, int y1, int x2, int y2)
{
	if (x1 == x2)
	{
		if ((y1 - y2) == 1 || (y1 - y2) == -1)
		{
			return true;
		}
	}
	else if (y1 == y2)
	{
		if ((x1 - x2) == -1 || (x1 - x2) == 1)
		{
			return true;
		}
	}
	return false;
}

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

bool UCheck(board** table, int x1, int y1, int x2, int y2, int size)
{
	if (x1 == x2 && x1 == 0 || y1 == y2 && y1 == 0)
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
		if (i <= min || i >= max) 
		{
			check1 = (ICheck(table, x1, i, x2, i) );
			if (check1)
			{
				check2 = ICheck(table, x1, y1, x1, i);
				check3 = ICheck(table, x2, y2, x2, i);
				if (check2 && check3 && table[x1][i].empty == true && table[x2][i].empty == true || check2 && y2 == 0 || check3 && y1 == 0 || check2 && y2 == size-1  || check3 && y1 == size - 1 && table[x2][y1].empty)
					return true;
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
		if (i <= min || i >= max)
		{
			check1 = (ICheck(table, i, y1, i, y2));
			if (check1)
			{
				check2 = ICheck(table, x1, y1, i, y1);
				check3 = ICheck(table, x2, y2, i, y2);
				if (check2 && check3 && table[i][y1].empty && table[i][y2].empty)// || check2 && x2 == 0 || check3 && x1 == 0 || check2 && x2 == size-1 || check3 && x1 == size-1)
					return true;
			}
		}
	}
	return false;
}

bool CheckPointer(board** table, int x1, int y1, int x2, int y2, int size)
{
	//if (NextToCheck(table,x1,y1,x2,y2) == true)
	//{
	//	GoTo(70, 0);
	//	cout << "Next match" << endl;
	//	GoTo(70, 1);
	//	cout << x1 << " " << y1 << "& " << x2 << " " << y2;
	//	return true;
	//}
	if (ICheck(table, x1, y1, x2, y2)) {
		GoTo(70, 0);
		cout << " I match";
		return true;
	}

	if (UCheck(table, x1, y1, x2, y2, size)) {
		GoTo(70, 0);
		cout << "U match";
		return true;
	}

}