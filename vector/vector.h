#include<iostream>
#include<vector>
using namespace std;

template<class T>
class MyVector
{
public:
	typedef T* Iterator;
	typedef const T* ConstIterator;

	MyVector(size_t n=3)      //���캯������ʼ����3��T��������
		:_start(new T[n]), _finish(_start), _end_of_storage(_start+n)
	{
	}
	MyVector(const MyVector<T>& v)   //��������
	{
		if (v._finish - v._start > _finish - _start)
		{
			delete[] _start;
			_start = new T[v._finish - v._start];
			_finish = _start;
		}
		for (Iterator tmp = v._start; tmp != v._finish; tmp++)
		{
			*(_finish) = *tmp;
			_finish++;
		}
		_end_of_storage = _finish;
	}
	void PushBack(const T& x)   //β�壬����ע�⣬��ʹ���õ�insert������������β�庯��������
	{
		CheckCapacity();
		Insert(End(), x);
	}
	void PopBack()
	{
		Iterator pos = End();   //ǰ�õ�--��Ϊ���ص�����ʱ������ֵ�����Բ���ֱ�Ӷ�End()��������--
		Erase(--pos);
	}

	void Insert(Iterator pos, const T& x)
	{
		CheckCapacity();
		for (Iterator tmp = End(); tmp != pos;tmp--)
		{
			*tmp = *(tmp - 1);
		}
		*pos = x;
		_finish++;
	}

	void Erase(Iterator pos)
	{
		Iterator end = End();
		for (Iterator tmp = pos; tmp != (--end); tmp++)
		{
			*tmp = *(tmp + 1);
		}
		_finish--;
	}

	size_t Size()
	{
		return _finish - _start;
	}
	/************����������***********/
	Iterator Begin()
	{
		return _start;
	}
	Iterator End()
	{
		return _finish;
	}
	/*Iterator operator++(int)
	{
		Iterator tmp = *this;
		tmp++;
		return tmp;
	}
	Iterator& operator++()
	{
		Iterator tmp = *this;
		tmp++;
		return *this;
	}
	Iterator operator--(int)
	{
		Iterator tmp = *this;
		tmp--;
		return tmp;
	}
	Iterator& operator--()
	{
		Iterator tmp = *this;
		tmp--;
		return *this;
	}
	*/
private:
	void CheckCapacity()
	{
		if (_finish == _end_of_storage)
		{
			Iterator new_start = new T[2 * Size()];   //һ������ԭ��������
			Iterator new_finish = new_start;
			for (Iterator i = Begin(); i != End(); i++,new_finish++)
			{
				*new_finish = *i;
			}
			delete[] _start;
			_start = new_start;
			_finish = new_finish;
			_end_of_storage = _start + 2 * Size();
		}
	}
private:
	Iterator _start;
	Iterator _finish;
	Iterator _end_of_storage;
};


void TestVector()
{
	MyVector<int> v;
	v.PushBack(1);
	v.PushBack(2);
	v.PushBack(3);
	v.PushBack(4);
	MyVector<int>::Iterator it;
	for (it = v.Begin(); it != v.End(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	v.PopBack();
	v.PopBack();
	for (it = v.Begin(); it != v.End(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
	MyVector<int> v1(v);
	for (it = v1.Begin(); it != v1.End(); it++)
	{
		cout << *it << " ";
	}
	cout << endl;
}