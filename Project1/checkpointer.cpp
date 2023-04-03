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
//Reference : phvanmin/pikachu (Ucheck only)
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
		return 0;
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
		if (check1 == true && check2 == false) {
			return true;
		}
	}
	return false;
}
bool ZCheck(board**table, int x1, int y1, int x2, int y2) {
	bool check1 = false;
	bool check2 = false;
	bool check3 = false;
	if (x1 < x2) { // Set the upper box is the left
		x1 = x1;
		x2 = x2;
	}
	else if(x2 < x1){
		swap(x1, x2);
	}
	for (int i = x1 + 1; i < x2; i++) { 
		check1 = ICheck(table, i, y1, i, y1);
		if (check1) {
			check2 = ICheck(table, i, y1, i, y2);
			check3 = ICheck(table, i, y2, x2, y2);
			if (check2 && check3) {
				return true;
			}
		}
	}
	if (y1 < y2) { // Set the upper box is the top 
		y1 = y1;
		y2 = y2;
	}
	else if( y2 < y1){
		swap(y1, y2);
	}
	for (int i = y1 + 1; i < y2; i++) {
		check1 = ICheck(table, x1, i, x1, i);
		if (check1) {
			check2 = ICheck(table, x1, i, x2, i);
			check3 = ICheck(table, x1, i, x2, y2);
			if (check2 && check3) {
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
	if (LCheck(table, x1, y1, x2, y2)) {
		GoTo(70, 0);
		cout << "L match";
		return true;
	}
	if (ZCheck(table, x1, y1, x2, y2)) {
		GoTo(70, 0);
		cout << "Z match";
		return true;
	}
	if (UCheck(table, x1, y1, x2, y2, size)) {
		GoTo(70, 0);
		cout << "U match";
		return true;
	}
}