// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower = s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower = bf.GetLength();
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if (Elem < 0)
		throw Elem;
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	int flag = 0;
	if (MaxPower == s.MaxPower)
	{
		if (BitField == s.BitField)
			flag = 1;
	}
	return flag;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	int flag = 1;
	if (MaxPower == s.MaxPower)
	{
		if (BitField == s.BitField)
			flag = 0;
	}
	return flag;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int MaxLen = MaxPower;
	if (s.MaxPower > MaxLen)
		MaxLen = s.MaxPower;
	TSet Tmp(MaxLen);
	Tmp.BitField = BitField | s.BitField;
	return Tmp;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet Tmp = *this;
	Tmp.InsElem(Elem);
	return Tmp;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet Tmp = *this;
	Tmp.DelElem(Elem);
	return Tmp;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	int MaxLen = MaxPower;
	if (s.MaxPower > MaxLen)
		MaxLen = s.MaxPower;
	TSet Tmp(MaxLen);
	Tmp.BitField = BitField & s.BitField;
	return Tmp;
}

TSet TSet::operator~(void) // дополнение
{
	TSet Tmp(MaxPower);
	Tmp.BitField = ~BitField;
	return Tmp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	return ostr;
}