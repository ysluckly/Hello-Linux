#pragma once

enum Color
{
	RED,
	BLACK,
};

template<class Value>
struct RBTreeNode
{
	RBTreeNode<Value>* _left;
	RBTreeNode<Value>* _right;
	RBTreeNode<Value>* _parent;

	Value _value;

	Color _color;

	RBTreeNode(const Value& value)
		:_left(nullptr)
		, _right(nullptr)
		, _parent(nullptr)
		, _value(value)
	{}
};

template<class Value>
struct RBTreeIterator
{
	typedef RBTreeNode<Value> Node;
	typedef RBTreeIterator<Value> Self;

	Node* _node;

	RBTreeIterator(Node* node)
		:_node(node)
	{}

	Value& operator*()
	{
		return _node->_value;
	}

	Value* operator->()
	{
		return &_node->_value;
	}

	Self operator++()
	{
		if (_node->_right != nullptr)
		{
			_node = _node->_right;
			while (_node->_left != nullptr)
			{
				_node = _node->_left;
			}
		}
		else
		{
			Node* cur = _node;
			Node* parent = cur->_parent;

			while (parent && cur == parent->_right)
			{
				cur = parent;
				parent = cur->_parent;
			}

			_node = parent;
		}

		return *this;
	}

	bool operator!= (const Self& s)
	{
		return _node != s._node;
	}
};

template<class K, class Value, class KeyOfValue>
class RBTree
{
	typedef RBTreeNode<Value> Node;
public:
	typedef RBTreeIterator<Value> iterator;

	RBTree()
		:_root(nullptr)
	{}

	~RBTree()
	{}

	iterator begin()
	{
		Node* cur = _root;
		while (cur && cur->_left != nullptr)
		{
			cur = cur->_left;
		}

		return iterator(cur);
	}

	iterator end()
	{
		return iterator(nullptr);
	}

	pair<iterator, bool> Insert(const Value& v)
	{
		// 1.按搜索树的规则进行插入
		if (_root == nullptr)
		{
			_root = new Node(v);
			_root->_color = BLACK;
			return make_pair(iterator(_root), true);
		}

		Node* parent = nullptr;
		Node* cur = _root;
		KeyOfValue kov;
		while (cur)
		{
			if (kov(cur->_value) < kov(v))
			{
				parent = cur;
				cur = cur->_right;
			}
			else if (kov(cur->_value) > kov(v))
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				//return false;
				return make_pair(iterator(cur), false);
			}
		}

		cur = new Node(v);
		Node* newnode = cur;
		cur->_color = RED;
		if (kov(parent->_value) < kov(cur->_value))
		{
			parent->_right = cur;
			cur->_parent = parent;
		}
		else
		{
			parent->_left = cur;
			cur->_parent = parent;
		}

		while (parent && parent->_color == RED)
		{
			Node* grandfather = parent->_parent;
			if (parent == grandfather->_left)
			{
				Node* uncle = grandfather->_right;

				// 1.u存在且为红->变色->继续向上
				if (uncle && uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else // u存在且为黑 or 不存在
				{
					// 双旋->单旋
					if (cur == parent->_right)
					{
						RotateL(parent);
						swap(parent, cur);
					}

					parent->_color = BLACK;
					grandfather->_color = RED;
					RotateR(grandfather);
					break;
				}
			}
			else // parent == grandfather->_right
			{
				Node* uncle = grandfather->_left;
				if (uncle && uncle->_color == RED)
				{
					parent->_color = uncle->_color = BLACK;
					grandfather->_color = RED;
					cur = grandfather;
					parent = cur->_parent;
				}
				else
				{
					if (cur == parent->_left)
					{
						RotateR(parent);
						swap(parent, cur);
					}

					grandfather->_color = RED;
					parent->_color = BLACK;
					RotateL(grandfather);
					break;
				}
			}
		}

		_root->_color = BLACK;
		//return true;
		return make_pair(iterator(newnode), true);
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;

		subL->_right = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subL;

		if (parent == _root)
		{
			_root = subL;
		}
		else
		{
			if (parent == ppNode->_left)
				ppNode->_left = subL;
			else
				ppNode->_right = subL;
		}

		subL->_parent = ppNode;
	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		parent->_right = subRL;
		if (subRL)
			subRL->_parent = parent;

		subR->_left = parent;
		Node* ppNode = parent->_parent;
		parent->_parent = subR;

		if (parent == _root)
		{
			_root = subR;
			_root->_parent = nullptr;
		}
		else
		{
			if (parent == ppNode->_left)
				ppNode->_left = subR;
			else
				ppNode->_right = subR;

			subR->_parent = ppNode;
		}
	}

	/*
	void InOrder()
	{
		_InOrder(_root);
		cout << endl;
	}

	void _InOrder(Node* root)
	{
		if (root == nullptr)
			return;
		_InOrder(root->_left);
		cout << root->_key << " ";
		_InOrder(root->_right);
	}

	bool IsValidRBTree()
	{
		Node* pRoot = _root;
		// 空树也是红黑树
		if (nullptr == pRoot)
			return true;

		// 检测根节点是否满足情况
		if (BLACK != pRoot->_color)
		{
			cout << "违反红黑树性质二：根节点必须为黑色" << endl;
			return false;
		}

		// 获取任意一条路径中黑色节点的个数
		size_t blackCount = 0;
		Node* pCur = pRoot;
		while (pCur)
		{
			if (BLACK == pCur->_color)
				blackCount++;
			pCur = pCur->_left;
		}
		// 检测是否
		size_t k = 0;
		return _IsValidRBTree(pRoot, k, blackCount);
	}

	bool _IsValidRBTree(Node* pRoot, size_t k, const size_t blackCount)
	{
		//走到null之后，判断k和black是否相等
		if (nullptr == pRoot)
		{
			if (k != blackCount)
			{
				cout << "违反性质四：每条路径中黑色节点的个数必须相同" << endl;
				return false;
			}
			return true;
		}
		// 统计黑色节点的个数
		if (BLACK == pRoot->_color)
			k++;
		// 检测当前节点与其双亲是否都为红色
		Node* pParent = pRoot->_parent;
		if (pParent && RED == pParent->_color && RED == pRoot->_color)
		{
			cout << "违反性质三：没有连在一起的红色节点" << endl;
			return false;
		}
		return _IsValidRBTree(pRoot->_left, k, blackCount) &&
			_IsValidRBTree(pRoot->_right, k, blackCount);
	}
	*/
private:
	Node* _root;
};

//void TestRBTree()
//{
//	int a[] = { 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };
//	RBTree<int, int> t;
//	for (auto e : a)
//	{
//		t.Insert(e, e);
//		cout << t.IsValidRBTree() << "->" << e << endl;
//	}
//
//	t.InOrder();
//	cout << t.IsValidRBTree() << endl;
//}