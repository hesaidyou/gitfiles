#include<iostream>
#include<string>
using namespace std;

template<class V,class W>
class GraphMatrix
{
public:
	GraphMatrix(V* vertex, int size, bool IsDirection=false)
		:_vertex(new V[size])
		, _weight(new W*[size])
		, _size(size)
		, _IsDirection(IsDirection)
	{
		for (int i = 0; i < size; i++)
		{
			_vertex[i] = vertex[i];
			_weight[i] = new W[size];
		}

	}
	~GraphMatrix()
	{
		delete[] _vertex;
		for (int i = 0; i < _size; i++)
		{
			delete[] _weight[i];
		}
		delete[] _weight;
	}

	int Getindex(const V& v)
	{
		for (int i = 0; i < _size; i++)
		{
			if (_vertex[i] == v)
				return i;
		}
		//������˵���������󣬲��ڸ����Ķ�����
		throw std::invalid_argument("��������");
	}

	void AddEdge(const V& begin,const V& end,const W& w)   //���ӱ�  ��������ʼ�����������Ȩֵ
	{
		int src = Getindex(begin);
		int des = Getindex(end);
		_weight[src][des] = w;
		if (_IsDirection == false)
		{
			_weight[des][src] = w;
		}
	}


protected:
	V* _vertex;
	W** _weight;
	int _size;

	bool _IsDirection;
};

void TestGraphMatrix()
{
	string city[5] = { "����", "����", "����", "����", "�Ӱ�" };
	GraphMatrix<string, int> gm(city, 5);
	gm.AddEdge("����", "����", 200);
	gm.AddEdge("����", "����", 300);
	gm.AddEdge("����", "�Ӱ�", 300);
	gm.AddEdge("����", "����", 100);
}