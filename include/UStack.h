#ifndef __TSTACK_H__
#define __TSTACK_H__
#include <string>
#include <vector>
#include<iostream>
template <class ValType>
class TStack
{
protected:
	ValType * pVector;
	int Size;
	int Count;
public:
	TStack(int _Size = 13);
	TStack(const TStack<ValType> &v);
	void Push(const ValType &v);
	ValType Pop();
	TStack<ValType>& operator=(const TStack<ValType>& _st);
	void Clear(int i = 0;)
	{
		Count = i;
	}
	bool IsEmpty()
	{
		return (Count == 0);
	}
	bool IsFool()
	{
		return (Count == Size);
	}
	ValType Top()
	{
		if (IsEmpty())
		{
			throw "Cant top empty stack";
		}
		return pVector[Count];
	}
	~TStack()
	{
		delete[] pVector;
	}
};
template<typename ValType>
TStack<ValType>& TStack<ValType>::operator=(const TStack& _v)
{
	if (this != &_v)
	{
		Count = _v.Count;
		if (Size != _v.Size)
		{
			delete[] pVector;
			Size = _v.Size;
			pVector = new ValType[Size];
		}
		for (int i = 0; i < Size; i++)
			pVector[i] = _v.pVector[i];
	}
	return *this;
}
template<typename ValType>
TStack<ValType>::TStack(int _Size = 13)
{
	if (_Size < 0)
	{
		throw "Incorrect size";
	}
	Size = _Size;
	pVector = new ValType[Size];
	Count = 0;
}
template<typename ValType>
TStack<ValType>::TStack(const TStack<ValType> &v)
{
	Size = v.Size;
	Count = v.Count;
	pVector = new ValType[v.Size];
	for (int i = 0; i < Size; i++)
	{
		pVector[i] = v.pVector[i];
	}
}
template<typename ValType>
ValType TStack<ValType>::Pop()
{
	if (IsEmpty())
	{
		throw "Cant pop empty stack";
	}
	Count--;
	return pVector[Count + 1];
}
template<typename ValType>
void TStack<ValType>::Push(const ValType &v)
{
	if (IsFool())
	{
		ValType* _pVector;
		_pVector = new ValType(4 / 3 * Size);
		for (int i = 0; i < Size; i++)
			_pVector[i] = pVector[i];
		pVector = _pVector;
	}
	pVector[Count + 1] = v;
	Count++;
}



template <class ValType>
class TMinStack
{
private:
	TStack<ValType> JustStack;
	TStack<ValType> MinStack;
public:
	TMinStack(int _Size = 13)
	{
		TStack<ValType> A(_Size);
		JustStack = A;
		MinStack = A;
	}
	bool IsEmpty()
	{
		return (JustStack.IsEmpty());
	}
	bool IsFool()
	{
		return (JustStack.IsFool());
	}
	void Push(const ValType &v)
	{
		JustStack.Push(v);
		if ((MinStack.IsEmpty()) || (v <= MinStack.Top()))
			MinStack.Push(v);
	}
	ValType Pop()
	{
		if (JustStack.Top() == MinStack.Top())
			MinStack.Pop();
		return JustStack.Pop();
	}
	ValType FindMin()
	{
		return MinStack.Top();
	}
};
#endif