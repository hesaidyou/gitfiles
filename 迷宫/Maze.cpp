#include"Maze.h"

int main()
{

	int arr[rows][cols];
	InitMaze((int*)arr);
	PrintMaze((int*)arr);
	//stack<Pos> s;
	//int ret = GetWay((int*)arr, Pos(2, 0), s);
	//if (ret == 1)
	//{
	//	cout << "�г���" << endl;
	//}
	//else
	//	cout << "�޳���" << endl;
	//PrintMaze((int*)arr);
	int tmp[rows][cols];
	GetShortPath((int*)tmp,(int*)arr);

	getchar();
	return 0;
}