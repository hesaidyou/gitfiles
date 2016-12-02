#include<iostream>
#include<vector>
#include<cassert>
using namespace std;

template<class T>
struct Grearer
{
	bool operator()(const T& left, const T& right)
	{
		return left > right;
	}
};

template<class T>
struct Less
{
	bool operator()(const T& left, const T& right)
	{
		return left < right;
	}
};
template<class T,class Compare=Grearer<T>>    //ģ���ģ�������Ĭ��ֵΪ����
class Heap
{
public:
	Heap()
	{}
	Heap(T* a, size_t size)    //����
	{
		for (size_t i = 0; i < size; i++)  //�������ݿ�������Ա_a
		{
			_a.push_back(a[i]);
		}
		for (int i = (size - 2) / 2; i >= 0; i--)   //�����һ����Ҷ�ӽڵ����µ���
		{
			_AjustDown(i);
		}
	}

	void Push(const T& x)
	{
		_a.push_back(x);     //�Ȳ嵽�ѵ����һ��λ��
		_AjustUp(_a.size() - 1);   //�ٶ����һ���������Ͻ��е���
	}

	void Pop()
	{
		assert(!_a.empty());    //�Կնѽ��ж���
		swap(_a[0], _a[_a.size() - 1]);    //�����ѵĵ�һ�����ݺ����һ��
		_a.pop_back();                    //�൱��ɾ���˵�һ������
		_AjustDown(0);                     //�Ըշ�����λ�õ����ݽ������µ���
	}

	size_t Size()           //�ѽڵ����
	{
		return _a.size();
	}

	const T& Top()     //�ѵ��׸�����
	{
		return _a[0];
	}

	bool Empty()    //���Ƿ�Ϊ��
	{
		return _a.empty();
	}
protected:
	void _AjustUp(int root)     //���ϵ���
	{
		size_t child = root;
		size_t parient = (child - 1) / 2;
		
		while (child > 0)
		{
			Compare com;
			//if (_a[child] > _a[parient])
			if (com(_a[child], _a[parient]))
			{
				swap(_a[child], _a[parient]);
			}
			else
			{
				break;
			}
			child = parient;
			parient = (child - 1) / 2;
		}

	}
	void _AjustDown(int root)   //���µ���
	{
		size_t parient = root;
		size_t child = 2 * parient + 1;
		
		while (child<_a.size())
		{
			Compare com;
			if ((child+1<_a.size())&&com(_a[child + 1] , _a[child]))  //�˴�һ��Ҫ�ȿ��ǵ��Һ��Ӳ����ڵ����
			{
				++child;
			}
			//if (_a[parient] < _a[child])
			if (com(_a[child], _a[parient]))
			{
				swap(_a[parient], _a[child]);
			}
			parient = child;
			child = 2 * parient + 1;
		}
	}
private:
	vector<T>_a;
};

template<class T,class Compare=Grearer<T>>
class PriorityQueue    //���ȼ�����
{
public:
	void Push(const T&x)
	{
		_h.Push(x);
	}
	void Pop()
	{
		_h.Pop();
	}
	size_t Size()
	{
		return _h.Size();
	}
	const T& Top()
	{
		return _h.Top();
	}
	bool Empty()
	{
		return _h.Empty();
	}
private:
	Heap<T,Compare> _h;
};

void test()
{
	int a[10] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 };
	Heap<int,Less<int>> hp(a, 10);
	hp.Push(30);
	hp.Pop();
}
void TestPriority()
{
	PriorityQueue<int> pq;
	pq.Push(3);
	pq.Push(2);
	pq.Push(1);
	pq.Push(9);
	cout << pq.Top() << endl;
	cout << pq.Size() << endl;
	pq.Pop();
}