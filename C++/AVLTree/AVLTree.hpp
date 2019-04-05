#pragma once

#include <iostream>
#include <assert.h>

template<class K, class V>
struct AVLTreeNode 
{
  struct AVLTreeNode<K, V>* _left;
  struct AVLTreeNode<K, V>* _right;
  struct AVLTreeNode<K, V>* _parent;

  K _key;
  V _value;
  int _bf;//平衡因子
  AVLTreeNode(const K& k, const V& v):_key(k),_value(v),_bf(0),_left(nullptr),_right(nullptr),_parent(nullptr)
  {}
};

template<class K, class V>
class AVLTree 
{
public:
  //typedef是在编译时处理的，需要知道具体的类型
  typedef struct AVLTreeNode<K, V> Node;
  AVLTree():_root(nullptr)
  {}

  ~AVLTree()
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
    //记录下改变结点的前一个节点
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

    subtree_right->_bf = parent->_bf = 0;
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
      if (pparent->_left == parent)
      {
        pparent->_left = subtree_left;
      }
      else 
      {
        pparent->_right = subtree_left;
      }
    }

    subtree_left->_bf = parent->_bf = 0;
  }

  void LeftRightRotate(Node* parent)
  {
    Node* subtree_left = parent->_left;
    int mid_node_bf = parent->_left->_right->_bf;

    LeftRotate(parent->_left);
    RightRotate(parent);

    if (mid_node_bf == -1)
    {
      parent->_bf = -1;
    }
    if (mid_node_bf == 1)
    {
      subtree_left->_bf = 1;
    }
  }

  void RightLeftRotate(Node* parent)
  {
    Node* subtree_right = parent->_right;
    int mid_node_bf = parent->_right->_left->_bf;

    RightRotate(parent->_right);
    LeftRotate(parent);

    if (mid_node_bf == 1)
    {
      subtree_right->_bf = -1;
    }
    if (mid_node_bf == -1)
    {
      parent->_bf = 1;
    }
  }

  bool Insert(const K& k, const V& v)
  {
    if (_root == nullptr)
    {
      _root = new Node(k, v);
      return true;
    }
    
    Node* insert_node = new Node(k, v);
    Node* parent = nullptr;
    Node* cur = _root;
    while (cur)
    {
      if (cur->_key == k)
      {
        return false;//表示整个树中已经有这一个节点了，不需要在进行插入
      }
      else if (cur->_key < k)
      {
        //右子树
        parent = cur;
        cur = cur->_right;
      }
      else 
      {
        //左子树
        parent = cur;
        cur = cur->_left;
      }
    }
    //表示找到了插入的位置，进行插入
    if (parent->_key > k)
    {
      parent->_left = insert_node;
    }
    else 
    {
      parent->_right = insert_node;
    }
    insert_node->_parent = parent;

    //插入完毕之后需要判断这个数还是不是AVL树，如果不是的话需要进行调整
    //调整
    //1.插入的结点在parent的左边bf--,插入结点在parent的右边bf++
    //2.改变之后parent的bf==0，表示整个parent的树的高度没有改变，只是对于左子树或者右子树进行填充，所以更新结束
    //3.parent的bf的绝对值等于1，说明parent的高度改变了，继续向上更新
    //4.parent的bf的绝对值等于2，此时parent树已经不是AVL树了，进行旋转，将其变成AVL树
    
    //终止更新有三种情况：
    //1.更新到bf==0，高度没有改变
    //2.更新到|bf|==2，高度改变了需要进行旋转
    //3.更新到根节点，一直是|bf|==1，需要一直更新
    
    while (parent)
    {
      if (insert_node == parent->_right)
      {
        parent->_bf++;
      }
      else if (insert_node == parent->_left) 
      {
        parent->_bf--;
      }

      if (parent->_bf == 0)
      {
        //高度没有改变，不需要调整
        break;
      }
      else if (abs(parent->_bf) == 1)
      {
        //高度改变，一直向上调整
        insert_node = parent;
        parent = insert_node->_parent;
      }
      else if (abs(parent->_bf) == 2)
      {
        //需要进行旋转
        //四种类型的旋转
        
        if (parent->_bf == -2)
        {
          if (parent->_left->_bf == -1)
          {
            //右单旋
            RightRotate(parent);
          }
          else 
          {
            //左右单旋
            LeftRightRotate(parent);
          }
        }
        else if (parent->_bf == 2)
        {
          if (parent->_right->_bf == 1)
          {
            //左单旋
            LeftRotate(parent);
          }
          else 
          {
            //右左单旋
            RightLeftRotate(parent);
          }
        }
        break;//更新结束直接不再更新
      }
      else 
      {
        //出现异常错误
        assert(false);
      }
    }
  }

  void InOrderSubFunction(Node* root)
  {
    if (root == nullptr)
    {
      return ;
    }

    InOrderSubFunction(root->_left);
    std::cout << root->_key << " ";
    InOrderSubFunction(root->_right);
  }

  void InOrder()
  {
    InOrderSubFunction(_root);
    std::cout << std::endl;
  }

  int Height(Node* root)
  {
    if (root == nullptr)
    {
      return 0;
    }

    int left = Height(root->_left);
    int right = Height(root->_right);

    return left > right ? left + 1 : right + 1;
  }

  bool IsBalanceSubFunction(Node* root)
  {
    if (root == nullptr)
    {
      return true;
    }

    int left = Height(root->_left);
    int right = Height(root->_right);

    return (abs(right - left) < 2) \
      && (IsBalanceSubFunction(root->_left)) \
      && (IsBalanceSubFunction(root->_right));
  }

  bool IsBalance()
  {
    return IsBalanceSubFunction(_root);
  }

private:
  Node* _root;
};
