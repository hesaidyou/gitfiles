#pragma once
#include<iostream>

using namespace std;

void AdjustDown(int* a, int root,int size)
{
	int parent = root;
	int child = 2 * parent + 1;  //�����±��Ǵ�0��ʼ�ģ��ʴ˴���child�����ӵ��±�
	while (child < size)
	{
		if ((child + 1)<size && a[child + 1]>a[child])
			++child;
		if (a[child]>a[parent])
			swap(a[child], a[parent]);
		parent = child;
		child = 2 * parent + 1;
	}
}

void HeapSort(int*a, int size)
{
	for (int i = (size-2)/2; i >=0; i--)   //����
	{
		AdjustDown(a, i, size);
	}
	for (int j = 0; j < size; j++)
	{
		swap(a[0], a[size - 1 - j]);
		AdjustDown(a, 0, size - j - 1);
	}
}

void TestHeapSort()
{
	int a[] = { 9, 5, 4, 2, 3, 6, 8, 7, 1, 5 };
	HeapSort(a,  sizeof(a) / sizeof(a[0]));
	PrintArr(a, sizeof(a) / sizeof(a[0]));
}