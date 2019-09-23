// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <string>

TBitField::TBitField(int len)
{
	if (len <= 0) throw "Length is not correct";
	BitLen = len;
	MemLen = (BitLen - 1) / (8 * sizeof(TELEM)) + 1;
	pMem = new unsigned int[MemLen];
	for (int i = 0; i < MemLen; i++)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	 if ((n>BitLen) ||(n < 0))
	{
		throw "Not correct";
	}
	return (n / (sizeof(TELEM) * 8));
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n>BitLen) || (n < 0))
	{
		throw "Not correct";
	}
	return 1 << (n & (sizeof(TELEM) * 8 - 1));
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	int i = GetMemIndex(n);
	if ((n>BitLen) || (n < 0))
	{
		throw "Not correct";
	}
	pMem[i] = pMem[i] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n>BitLen) || (n < 0))
	{
		throw "Not correct";
	}
	int i = GetMemIndex(n);
	pMem[i] = pMem[i] & ~GetMemMask(n);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n>BitLen) || (n < 0))
	{
		throw "Not correct";
	}
	int i = GetMemIndex(n);
	return (pMem[i] & GetMemMask(n));
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (&bf != this)
	{
		if (BitLen == bf.BitLen)
			for (int i = 0; i < MemLen; i++)
				pMem[i] = bf.pMem[i];
		else
		{
			BitLen = bf.BitLen;
			MemLen = bf.MemLen;
			pMem = new TELEM[MemLen];
			for (int i = 0; i < MemLen; i++)
				pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	int flag = 1;
	if (BitLen != bf.BitLen)
		flag = 0;
	else for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
		{
			flag = 0;
			break;
		}
	return flag;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	int flag = 0;
	if (BitLen != bf.BitLen)
		flag = 1;
	else for (int i = 0; i < MemLen; i++)
		if (pMem[i] != bf.pMem[i])
		{
			flag = 1;
			break;
		}
	return flag;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int TmpLen = BitLen;
	if (TmpLen < bf.BitLen)
		TmpLen = bf.BitLen;
	TBitField Tmp(TmpLen);
	for (int i = 0; i < MemLen; i++)
		Tmp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		Tmp.pMem[i] |= bf.pMem[i];
	return Tmp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int TmpLen = BitLen;
	if (TmpLen < bf.BitLen)
		TmpLen = bf.BitLen;
	TBitField Tmp(TmpLen);
	for (int i = 0; i < MemLen; i++)
		Tmp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++)
		Tmp.pMem[i] &= bf.pMem[i];
	return Tmp;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField Tmp(BitLen);
	for (int i = 0; i < BitLen; i++)
	{
		if (GetBit(i) == 0)		
			Tmp.SetBit(i);
		else Tmp.ClrBit(i);
	}
	return Tmp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	string Tmp;
	istr >> Tmp;
	bf = TBitField(Tmp.size());
	for (int i = 0; i < bf.BitLen; i++) 
	{
		if (Tmp[i] == 1) 
			bf.SetBit(i);
		else  if (Tmp[i] != 0)
			throw "Not a bitfield";
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i = 0; i < bf.BitLen; ++i) 
		cout << bf.GetBit(i);
	return ostr;
}