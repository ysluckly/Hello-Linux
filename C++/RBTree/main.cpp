#nclude "RBTree.hpp"

void TestRBTree()
{
	RBTree<int, int> rb;
	int rb_array[] = { 3, 4, 2, 6, 1, 3, 5, 15, 7, 16, 14 };

	std::cout << "In Insert Front!" << std::endl;
	for (int i = 0; i < (int)(sizeof(rb_array) / sizeof(rb_array[0])); i++)
	{
		rb.Insert(rb_array[i], 1);
	}
	std::cout << "In Insert End!" << std::endl;

	rb.InOrder();
	std::cout << "RBTree is balance: 1(true) : 0(false)\n" << "value:" << rb.IsRBTree() << std::endl;
}

int main()
{
	TestRBTree();
	return 0;
}
