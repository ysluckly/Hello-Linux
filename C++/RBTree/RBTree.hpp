#pragma once 

#include <iostream>

using std::swap;

enum color
{
	RED,
	BLACK
};

template<class K, class V>
struct  RBTreeNode
{
	struct RBTreeNode<K, V>* _left;
	struct RBTreeNode<K, V>* _right;
	struct RBTreeNode<K, V>* _parent;
	enum color _color;

	K _key;
	V _val;
	RBTreeNode(int key, int val) :_left(nullptr), _right(nullptr), _parent(nullptr), _color(RED), _key(key), _val(val)
	{
	}
};

template<class K, class V>
class RBTree
{
public:
	typedef struct RBTreeNode<K, V> Node;
	RBTree() :_root(nullptr)
	{}

	~RBTree()
	{}

	void LeftRotate(Node* parent)
	{
		Node* subtree_right = parent->_right;
		Node* subtree_right_left = subtree_right->_left;

		parent->_right = subtree_right_left;
		if (subtree_right_left)
		{
			subtree_right_left->_parent = parent;
		}

		subtree_right->_left = parent;
		Node* pparent = parent->_parent;
		parent->_parent = subtree_right;

		subtree_right->_parent = pparent;
		if (parent == _root)
		{
			_root = subtree_right;
		}
		else
		{
			if (pparent->_left == parent)
			{
				pparent->_left = subtree_right;
			}
			else
			{
				pparent->_right = subtree_right;
			}
		}
	}

	void RightRotate(Node* parent)
	{
		Node* subtree_left = parent->_left;
		Node* subtree_left_right = subtree_left->_right;

		parent->_left = subtree_left_right;
		if (subtree_left_right)
		{
			subtree_left_right->_parent = parent;
		}

		subtree_left->_right = parent;
		Node* pparent = parent->_parent;
		parent->_parent = subtree_left;

		subtree_left->_parent = pparent;
		if (parent == _root)
		{
			_root = subtree_left;
		}
		else
		{
			if (subtree_left == pparent->_left)
			{
				pparent->_left = subtree_left;
			}
			else
			{
				pparent->_right = subtree_left;
			}
		}
	}

	bool Insert(K key, V value)
	{
		//按照搜索树的规则进行插入   
		if (_root == nullptr)
		{
			Node* tmp = new Node(key, value);
			_root = tmp;
			return true;
		}

		Node* parent = nullptr;
		Node* cur = _root;
		Node* insert_node = new Node(key, value);
		while (cur)
		{
			if (cur->_key == key)
			{
				return true;
			}
			else if (cur->_key > key)
			{
				parent = cur;
				cur = cur->_left;
			}
			else
			{
				parent = cur;
				cur = cur->_right;
			}
		}

		if (parent->_key > key)
		{
			parent->_left = insert_node;
			insert_node->_parent = parent;
		}
		else
		{
			parent->_right = insert_node;
			insert_node->_parent = parent;
		}

		//已经将结点插入到二叉搜索树了，然后进行判断调整

		//当父亲结点存在，并且为红色的时候进行调整
		while (parent && parent->_color == RED)
		{
			Node* grandfather = parent->_parent;

			if (grandfather)
			{
				if (parent == grandfather->_left)//父亲结点是爷爷结点的左子树
				{
					Node* uncle = grandfather->_right;
					if (uncle && uncle->_color == RED)
					{
						//将父亲结点和叔叔结点变为黑色，爷爷结点变为红色，继续向上调整
						parent->_color = BLACK;
						uncle->_color = BLACK;
						grandfather->_color = RED;
						insert_node = grandfather;
						parent = insert_node->_parent;
					}
					else
					{
						//有着两种情况，但是两种情况都要进行右旋
						//可以将右旋进行合并，首先判断是否需要左旋   
						if (parent->_right == insert_node)
						{
							//左旋
							//注意：就是左旋之后，insert_node和parent结点为位置发生改变，所以需要将两个节点的指针进行交换
							LeftRotate(parent);
							std::swap(insert_node, parent);
						}
						//进行右旋，以爷爷结点为支点进行右旋            
						parent->_color = BLACK;
						grandfather->_color = RED;
						RightRotate(grandfather);

						break;
					}
				}
				else //parent == grandfather->_right 
				{
					Node* uncle = grandfather->_left;
					if (uncle && uncle->_color == RED)
					{
						parent->_color = uncle->_color = BLACK;
						grandfather->_color = RED;
						insert_node = grandfather;
						parent = insert_node->_parent;
					}
					else
					{
						//进行左旋和右旋，都要进行右旋
						//左旋
						if (insert_node == parent->_left)
						{
							RightRotate(parent);
							swap(parent, insert_node);
						}

						parent->_color = BLACK;
						grandfather->_color = RED;
						LeftRotate(grandfather);
						break;
					}
				}
			}
			else
			{
				break;
			}
		}

		//如果grandfather是根节点的话，需要将其设置为黑色
		_root->_color = BLACK;
	}

	void InOrderSubFunction(Node* root)
	{
		if (root == nullptr)
		{
			return;
		}

		InOrderSubFunction(root->_left);
		std::cout << root->_key << " ";
		InOrderSubFunction(root->_right);
	}

	void InOrder()
	{
		if (_root == nullptr)
		{
			return;
		}
		InOrderSubFunction(_root);
		std::cout << std::endl;
	}

    bool IsRBTreeSubFubction(Node* root, int count, const int& black_count)
    {
        if (root == nullptr)
        {
            if (count == black_count)
            {
                return true;
            }
            return false;
        }

        if (root->_color == BLACK)
        {
            count++;
        }

        //还要进行判断是不是有两个连在一起的红结点   
        Node* pparent = root->_parent;
        if (pparent && root->_color == RED && pparent->_color == RED)
        {
            return false;
        }
        
        return IsRBTreeSubFubction(root->_left, count, black_count) && IsRBTreeSubFubction(root->_right, count, black_count);
    }

    bool IsRBTree()
    {
        //如果root为空，就是红黑树
        if (_root == nullptr)
        {
            return true;
        }
        
        if (_root && _root->_color == RED)
        {
            return false;
        }

        //求出一个路径上的黑结点的值
        int black_count = 0;
        Node* cur = _root;
        while (cur)
        {
            if (cur->_color == BLACK)
            {
                black_count++;
            }
            cur = cur->_left;
        }

        int count = 0;
        return IsRBTreeSubFubction(_root, count, black_count);

    }
private:
	Node * _root;
};
