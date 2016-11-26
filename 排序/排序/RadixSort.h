#pragma once
#include<iostream>

using namespace std;

int GetMaxDigit(int*a, int size)    //�õ��������������λ��
{
	int digit = 1;
	int num = 10;
	for (int i = 0; i < size; i++)
	{
		if (a[i]>=num)
		{
			num *= 10;
			++digit;
		}
	}
	return digit;
}

void LSDSort(int*a,int size)    //�ɵ�λ���λ����
{
	int *tmp = new int[size];
	memset(tmp, 0, sizeof(int)*size);
	int digit = GetMaxDigit(a, size);
	int count[10] = { 0 };   //ͳ��λ���ֵĴ���
	int start[10] = { 0 };  //����λ��λ��
	int base = 1;
	while (digit--)
	{
		for (int i = 0; i < size; i++)
		{
			int index = (a[i]/base )% 10;
			count[index]++;
		}
		for (int i = 1; i < size; i++)
		{
			start[i] = start[i - 1] + count[i - 1];
		}

		for (int i = 0; i < size; i++)
		{
			int index = a[i]/base % 10;
			tmp[start[index]++] = a[i];
		}

		for (int i = 0; i < size; i++)
			a[i] = tmp[i];

		base *= 10;
	}
	delete[] tmp;
}

void TestLSDSort()
{
	int a[] = { 9, 5, 4, 2, 3, 6, 8, 7, 1, 5 };
	LSDSort(a, sizeof(a) / sizeof(a[0]));
	PrintArr(a, sizeof(a) / sizeof(a[0]));
}