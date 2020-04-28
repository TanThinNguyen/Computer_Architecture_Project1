#include "pch.h"
#include "QInt.h"
#include "BitManipulation.h"

int main()
{
	string s = "-891243829999";
	//string s = "-1782487659998";

	QInt x;
	x.ScanQInt(s);
	cout << x.PrintQInt() << endl;

	x = x << 128;
	cout << x.PrintQInt() << endl;
	
	system("pause");
}