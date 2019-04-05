#pragma once
#include "RBTree.h"

template<class K>
class Set
{
public:
	struct SetKeyOfValue
	{
		const K& operator()(const K& key)
		{
			return key;
		}
	};

	typedef typename RBTree<K, K, SetKeyOfValue>::iterator iterator;

	iterator begin()
	{
		return _tree.begin();
	}

	iterator end()
	{
		return _tree.end();
	}

	pair<iterator, bool> Insert(const K& k)
	{
		return _tree.Insert(k);
	}
private:
	RBTree<K, K, SetKeyOfValue> _tree;
};

void TestSet()
{
	Set<int> s;
	s.Insert(1);
	s.Insert(2);
	s.Insert(2);
	s.Insert(0);
	s.Insert(8);
	s.Insert(6);
	s.Insert(3);
	s.Insert(5);
	s.Insert(4);

	Set<int>::iterator it = s.begin();
	while (it != s.end())
	{
		cout << *it << " ";
		++it;
	}
	cout << endl;

	for (auto e : s)
	{
		cout << e << " ";
	}
	cout << endl;
}