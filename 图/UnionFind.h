#pragma once
#include<iostream>

using namespace std;
class UnionFind
{
public:
	UnionFind(size_t n)    //����n+1��С������,�±�Ϊ0�Ĳ�ʹ��
		:_a(new int[n + 1])
		, _size(n + 1)
	{
		memset(_a, -1, sizeof(int)*(n + 1));
	}

	void Merge(int x, int y)   //������ϵ
	{
		int root1 = GetRoot(x);
		int root2 = GetRoot(y);

		if (root1 != root2)   //�����������һ��������Ͳ��ý�����ϵ��
		{
			_a[root1] += _a[root2];
			_a[root2] = root1;   //���Ӵ�Ÿ��׵��±�
		}
	}

	int CountUnion()   //ͳ���м�������
	{
		int count = 0;
		for (size_t i = 0; i < _size; i++)
		{
			if (_a[i] < 0)
				count++;
		}
		return count - 1;   //��ȥ�±�Ϊ0��λ��
	}

	int GetRoot(int index)
	{
		int root = index;
		while (_a[root] >= 0)
		{
			root = _a[root];
		}
		return root;
	}
protected:
	int* _a;
	size_t _size;
};

int friends(int n, int m, int r[][2])
{
	UnionFind uf(n);
	uf.Merge(r[0][0], r[0][1]);
	uf.Merge(r[1][0], r[1][1]);
	uf.Merge(r[2][0], r[2][1]);
	return uf.CountUnion();
}

void TestUnionFind()
{
	const int n = 5;
	const int m = 3;
	int r[m][2] = { { 1, 2 }, { 2, 3 }, { 4, 5 } };
	cout << friends(n, m, r);
}