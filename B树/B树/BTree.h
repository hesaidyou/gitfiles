#include<iostream>

using namespace std;

template<class K , int M>
struct BTreeNode
{
	typedef BTreeNode<K, M> Node;
	K _keys[M];   //�����һ��λ����Ϊ�˷�����ѡ�
	Node* _sub[M + 1];
	Node* _parent;
	size_t _size;  //��¼ʵ�ʹؼ��ֵĸ���
	BTreeNode()
		:_parent(NULL)
		, _size(0)
	{
		for (size_t i = 0; i < M; i++)
		{
			_keys[i] = K();
			_sub[i] = 0;
		}
		_sub[M] = 0;
	}
};

template<class K,int M>
class BTree
{
public:
	typedef BTreeNode<K, M> Node;
	BTree()
		:_root(NULL)
	{}
	void InOrder()
	{
		_InOrder(_root);
	}
	~BTree()
	{
		_Destory(_root);
	}
	bool Insert(const K& key)
	{
		if (NULL == _root)
		{
			_root = new Node();
			_root->_keys[0] = key;
			_root->_size++;
			return true;
		}
		pair<Node*, size_t> tmp = _Find(key);
		if (tmp.second != -1)  //�Ѿ����ڹؼ�ֵΪkey�����ܲ���
		{
			return false;
		}
		Node* cur = tmp.first;
		Node* sub = NULL;
		K newkey = key;
		while (1)
		{
			_Insertkey(cur,newkey,sub);  //�Ƚ�key�Ž�Ҫ��Ľڵ�
			//�жϽ��Ĺؼ�����Ŀ�Ƿ���ϱ�׼��
			if (cur->_size < M)  //�ýڵ��ϲ����ؼ�����Ŀ����
				return true;

			//��Ŀ�����涨ֵ��Ҫ���з���
			while (cur->_size >= M)
			{
				size_t mid = cur->_size / 2;
				//1.���ѳ��µĽ��
				Node* NewNode = new Node;
				for (size_t i = mid+1; i < cur->_size; i++)//mid֮���keyֵ���½��
				{
					int j = 0;
					NewNode->_keys[j] = cur->_keys[i];
					NewNode->_size++;
					//cur->_size--;  //ע��˴��Ȳ�ҪŶ�Ķ�cur��size�������Ӱ����һ��ѭ��
					cur->_keys[i] = K();  //�����½���cur��Ӧ��keyӦ�óɳ�ʼֵ
					j++;
				}
				int j = 0;
				for (size_t i = mid+1 ; i < cur->_size+1; i++)
				{
					NewNode->_sub[j] = cur->_sub[i];
					if (NewNode->_sub[j])
						NewNode->_sub[j]->_parent = NewNode;
					j++;
					cur->_sub[i] = NULL;
				}
				if (cur == _root)  //�������µĸ��ڵ�
				{
					Node* tmp = new Node();
					tmp->_keys[0] = cur->_keys[mid];
					cur->_keys[mid] = K();
					cur->_size=mid;
					tmp->_size++;
					tmp->_sub[0] = cur;
					cur->_parent = tmp;
					tmp->_sub[1] = NewNode;
					NewNode->_parent = tmp;
					_root = tmp;
					return true;
				}
				newkey = cur->_keys[mid];
				cur->_keys[mid] = K();
				cur->_size = mid;   
				sub = NewNode;
			}
			
			cur = cur->_parent;
		}
	}

protected:
	void _Destory(Node* root)
	{
		if (NULL == root)
			return;

		size_t i = 0;
		for (; i < root->_size; i++)
		{
			_Destory(root->_sub[i]);
			delete root->_sub[i];
		}
		_Destory(root->_sub[i]);
		delete root->_sub[i];
	}
	void _InOrder(Node* root)
	{
		if (NULL == root)
			return;

		size_t i = 0;
		for (; i < root->_size; i++)
		{
			_InOrder(root->_sub[i]);
			cout << root->_keys[i]<<" ";

		}
		_InOrder(root->_sub[i]);
	}
	pair<Node*,size_t> _Find(const K& key)
	{
		Node* cur = _root;
		Node* parent = NULL;
		while (cur)
		{
			size_t i = 0;
			while (i< cur->_size)  //�ҵ�ǰ����key
			{
				
				if (cur->_keys[i] < key)
					i++;
				else if (cur->_keys[i]>key)
					//cur = cur->_sub[i];
					break;
				else   //�ҵ��˺ʹ���key��ȵĹؼ���
					return pair<Node* ,size_t>(cur,i);
			}
			parent = cur;
			cur = cur->_sub[i];
		}
		return pair<Node* , size_t>(parent, -1);  //û�ҵ�
	}
	void _Insertkey(Node* cur,const K& key,Node*sub)
	{
		int i = cur->_size-1;
		while (i >=0)
		{
			if (cur->_keys[i] > key)
			{
				//�ƶ��ؼ��ֵ�λ��
				cur->_keys[i + 1] = cur->_keys[i];

				//�ƶ�������λ��
				cur->_sub[i + 2] = cur->_sub[i + 1];
				i--;
			}
			else
				break;
		}
		//i��¼��Ҫ����λ�õ�ǰһ��
		cur->_keys[i + 1] = key;
		cur->_sub[i + 2] = sub;
		if (sub)
			sub->_parent = cur;
		cur->_size++;
	}
private:
	Node* _root;
};

void TestBTree()
{
	BTree<int, 3> bt;
	int a[] = { 53, 75, 139, 49, 145, 36, 101 };
	for (int i = 0; i < sizeof(a) / sizeof(a[0]); i++)
	{
		bt.Insert(a[i]);
	}
	bt.InOrder();
}