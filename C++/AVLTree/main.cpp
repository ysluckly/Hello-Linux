#include <iostream>
#include "AVLTree.hpp"

void TestAVLTreeInsert()
{
  AVLTree<int, int> avl;
  int avl_array[] = { 3, 4, 2, 6, 1, 3, 5, 15, 7, 16, 14};
  
  for (int i = 0; i < (int)(sizeof(avl_array) / sizeof(avl_array[0])); i++)
  {
    avl.Insert(avl_array[i], 1);
  }

  avl.InOrder();
  std::cout << "AVLTree is balance: 1(true) : 0(false)\n" << "value:" << avl.IsBalance() << std::endl;
}

int main()
{
  TestAVLTreeInsert();
  return 0;
}
