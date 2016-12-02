#pragma once
#include<iostream>

using namespace std;
void _AjustDown(int* a, size_t size, int root)
{
	size_t parient = root;
	size_t child = 2 * parient + 1;

	while (child<size)
	{

		if ((child + 1<size) && (a[child + 1]> a[child]))  //�˴�һ��Ҫ�ȿ��ǵ��Һ��Ӳ����ڵ����
		{
			++child;
		}
		if (a[parient] < a[child])
		{
			swap(a[parient], a[child]);
		}
		parient = child;
		child = 2 * parient + 1;
	}
}


	void HeapSort(int* a, size_t size)    
	{
		for (int i = (size - 2) / 2; i >= 0; i--)   //����һ�����
		{
			_AjustDown(a, size, i);
		}
		for (size_t i = 0; i < size; i++)
		{
			swap(a[0], a[size - 1-i]);    //�����������ڶѵ����һ�����
			_AjustDown(a, size - 1 - i, 0);   //�����������һ�����ֵ�ʣ�µĶѡ�
		}
		//return a;
	}

	

void TestHeapSort()
{
	int a[10] = { 10, 16, 18, 12, 11, 13, 15, 17, 14, 19 };
	HeapSort(a, 10);
}