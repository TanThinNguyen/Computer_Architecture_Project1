#include "pch.h"
#include "BitManipulation.h"

QInt& BitManipulation::copy(const QInt& x)
{
	QInt* res = new QInt();
	for (int i = 0; i < 4; i++)
	{
		res->data[i] = x.data[i];
	}
	return *res;
}

/*
Input: Biến x kiểu QInt (128 bit)
Output: Chuỗi biểu diễn nhị phân tương ứng của x
*/
string BitManipulation::QIntToBinStr(const QInt& x)
{
	string bin;
	// Lặp qua 128 bit, lấy từng bit ra và thêm vào chuỗi kết quả
	for (int i = 0; i < 128; i++)
	{
		int bit = (x.data[i / 32] >> (31 - i % 32)) & 1;
		bin = bin + char(bit + '0');
	}
	return bin;
}

/*
Input: Chuỗi biểu diễn nhị phân x
Output: Biến x kiểu QInt (128 bit) tương ứng với biểu diễn nhị phân đó
*/
QInt& BitManipulation::BinStrToQInt(string s)
{
	QInt* res = new QInt();
	// Lặp qua từng kí tự, nếu là '1' thì gán vào bit tương ứng của QInt
	for (int i = 0; i < 128; i++)
	{
		int bit = s[i] - '0';
		if (bit == 1)
			res->data[i / 32] = res->data[i / 32] | (bit << (31 - i % 32));
	}
	return *res;
}

QInt& BitManipulation::logicalLeftShift(const QInt& x, int y)
{
	string bin = BitManipulation::QIntToBinStr(x);

	// Dời (128 - y) bit cuối sang trái y đơn vị
	int i = 0;
	for (; i < bin.length() - y; i++)
	{
		bin[i] = bin[i + y];
	}
	// Gán giá trị 0 các bit còn lại ở cuối
	while (i < bin.length())
	{
		bin[i] = '0';
		i++;
	}

	QInt res = BitManipulation::BinStrToQInt(bin);
	return res;
}

QInt& BitManipulation::logicalRightShift(const QInt& x, int y)
{
	string bin = BitManipulation::QIntToBinStr(x);

	// Dời (128 - y) bit đầu sang phải y đơn vị
	int i = bin.length() - 1;
	for (; i >= y; i--)
	{
		bin[i] = bin[i - y];
	}
	// Gán giá trị 0 các bit còn lại ở đầu
	while (i >= 0)
	{
		bin[i] = '0';
		i--;
	}

	QInt res = BitManipulation::BinStrToQInt(bin);
	return res;
}

QInt& BitManipulation::arithmeticRightShift(const QInt& x, int y)
{
	string bin = BitManipulation::QIntToBinStr(x);

	// Dời (128 - y) bit đầu sang phải y đơn vị
	int i = bin.length() - 1;
	for (; i >= y; i--)
	{
		bin[i] = bin[i - y];
	}
	// Gán giá trị các bit còn lại ở đầu
	while (i >= 0)
	{
		bin[i] = bin[y];
		i--;
	}

	QInt res = BitManipulation::BinStrToQInt(bin);
	return res;
}


QInt& BitManipulation::leftRotate(const QInt& x)
{
	int mostLeftBit = (x.data[0] >> 31) & 1;
	QInt res = BitManipulation::logicalLeftShift(x, 1);

	// Đưa bit ngoài cùng bên trái (của x ban đầu) vào vị trí ngoài cùng bên phải
	if (mostLeftBit == 1)
		res.data[3] = x.data[3] | 1;
	else
		res.data[3] = x.data[3] & (~1);
	
	return res;
}

QInt& BitManipulation::rightRotate(const QInt& x)
{
	int mostRightBit = x.data[3] & 1;
	QInt res = BitManipulation::logicalLeftShift(x, 1);

	if (mostRightBit == 1)
		res.data[0] = x.data[0] | (1 << 31);
	else
		res.data[0] = x.data[0] & (~(1 << 31));
	return res;
}

//
//QInt& BitManipulation::logicalLeftShift(const QInt& x, int y)
//{
//	/*QInt* res = new QInt();
//	for (int i = 0; i < 4; i++)
//	{
//		res->data[i] = x.data[i];
//	}*/
//
//	QInt res = BitManipulation::copy(x);
//
//	// leftBit, rightBit tương ứng là bit trái nhất, bit phải nhất của một phần tử trong mảng data
//	int leftBit = 0, rightBit = 0;
//	// Duyệt từ phần tử data[3] tới data[0]
//	for (int i = 3; i >= 0; i--)
//	{
//		// Tại mỗi phần tử của mảng data:
//		//	+ Lấy ra leftBit của phần tử
//		//	+ LeftShift phần tử 1 bước (data[i] << 1)
//		//	+ Đưa rightBit vào phần tử
//		//	+ Gán leftBit có được ở trêc gán cho rightBit dùng cho phần tử tiếp theo
//		leftBit = (x.data[i] >> 31) & 1;
//		res.data[i] = x.data[i] << 1;
//
//		if (rightBit == 1)
//			res.data[i] = res.data[i] | 1;
//		else  // rightBit == 0
//			res.data[i] = res.data[i] & (~1);
//
//		rightBit = leftBit;
//	}
//
//	return res;
//}
//
//QInt& BitManipulation::logicalRightShift(const QInt& x, int y)
//{
//	// leftBit, rightBit tương ứng là bit trái nhất, bit phải nhất của một phần tử trong mảng data
//	int leftBit = 0, rightBit = 0;
//	// Duyệt từ phần tử data[0] tới data[3]
//	for (int i = 0; i < 4; i++)
//	{
//		// Tại mỗi phần tử của mảng data:
//		//	+ Lấy ra rightBit của phần tử
//		//	+ RightShift phần tử 1 bước (data[i] >> 1)
//		//	+ Đưa leftBit vào phần tử
//		//	+ Gán rightBit có được ở trêc gán cho leftBit dùng cho phần tử tiếp theo
//		rightBit = x.data[i] & 1;
//		x.data[i] = x.data[i] >> 1;
//
//		if (leftBit == 1)
//			x.data[i] = x.data[i] | (1 << 31);
//		else  // leftBit == 0
//			x.data[i] = x.data[i] & (~(1 << 31));
//
//		leftBit = rightBit;
//	}
//	return QInt();
//}
//
//QInt& BitManipulation::arithmeticRightShift(const QInt& x, int y)
//{
//	// leftBit, rightBit tương ứng là bit trái nhất, bit phải nhất của một phần tử trong mảng data
//	int leftBit = 0, rightBit = 0;
//	leftBit = (x.data[0] >> 31) & 1;
//
//	// Duyệt từ phần tử data[0] tới data[3]
//	for (int i = 0; i < 4; i++)
//	{
//		// Tại mỗi phần tử của mảng data:
//		//	+ Lấy ra rightBit của phần tử
//		//	+ RightShift phần tử 1 bước (data[i] >> 1)
//		//	+ Đưa leftBit vào phần tử
//		//	+ Gán rightBit có được ở trêc gán cho leftBit dùng cho phần tử tiếp theo
//		rightBit = x.data[i] & 1;
//		x.data[i] = x.data[i] >> 1;
//
//		if (leftBit == 1)
//			x.data[i] = x.data[i] | (1 << 31);
//		else  // leftBit == 0
//			x.data[i] = x.data[i] & (~(1 << 31));
//
//		leftBit = rightBit;
//	}
//	return QInt();
//}


