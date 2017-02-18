#pragma once
#include<iostream>

using namespace std;
template<class K>
struct SelectBinaryTreeNode
{
	typedef SelectBinaryTreeNode<K> Node;
	K _key;
	Node* _left;
	Node* _right;
	SelectBinaryTreeNode(const K& key)
		:_key(key)
		, _left(NULL)
		, _right(NULL)
	{}
};

template<class K>
class SelectBinaryTree
{
public:
	typedef SelectBinaryTreeNode<K> Node;
	SelectBinaryTree()
	{}
	~SelectBinaryTree()   //�������ݹ�ʵ��
	{
		_Destory(_root);
	}

	void TodoubleLink()  //����������ת����˫������
	{
		Node* prev = NULL;
		_TodoubleLink(_root, prev);
		Node* head = _root;
		while (head->_left)
		{	
			head = head->_left;
		}
		_root = head;
		while (head)
		{
			cout << head->_key << " ";
			head = head->_right;
		}
		cout << endl;
	}

	bool Insert(const K& key)    //�ǵݹ����
	{
		if (NULL == _root)
		{
			_root = new Node(key);
			return true;
		}
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			if (cur->_key < key)
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (cur->_key>key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
				return false;
		}
		if (parent->_key < key)
		{
			parent->_right = new Node(key);
		}
		else
			parent->_left = new Node(key);
		return true;
	}

	bool InsertR(const K& key)    //�ݹ����
	{
		return _InsertR(_root, key);
	}

	
protected:

	Node* _TodoubleLink(Node* root, Node*& prev)
	{
		if (root == NULL)
			return NULL;
		Node* cur = root;
		_TodoubleLink(cur->_left, prev);
		cur->_left = prev;
		if (prev)
			prev->_right = cur;
		prev = cur;
		_TodoubleLink(cur->_right, prev);
		return root;
	}


	bool _InsertR(Node*& root, const K& key)
	{
		if (NULL == root)
		{
			root = new Node(key);
			return true;
		}
		if (root->_key < key)
			return _InsertR(root->_right, key);
		else if (root->_key>key)
			return _InsertR(root->_left, key);
		else
			return false;
	}



	void _Destory(Node* root)
	{
		Node* cur = root;
		while (cur)
		{
			Node* del = cur;
			cur = cur->_right;
			delete del;
		}
	}



private:
	Node* _root;
};



void TestTodoubleLink()
{
		int a[] = { 5, 3, 4, 1, 2, 6, 0 };
		SelectBinaryTree<int> sbt;
		for (size_t i = 0; i < sizeof(a) / sizeof(a[0]); i++)
		{
			sbt.InsertR(a[i]);
		}
		sbt.TodoubleLink();
}