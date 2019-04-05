#pragma once

#include "RBTree.h"

template<class K, class V>
class Map
{
public:
	struct MapKeyOfValue
	{
		const K& operator()(const pair<K, V>& kv)
		{
			return kv.first;
		}
	};
	typedef typename RBTree<K, std::pair<K, V>, MapKeyOfValue>::iterator iterator;

	iterator begin()
	{
		return _tree.begin();
	}

	iterator end()
	{
		return _tree.end();
	}

	pair<iterator, bool> Insert(const std::pair<K, V>& kv)
	{
		return _tree.Insert(kv);
	}

	V& operator[](const K& key)
	{
		pair<iterator, bool> ret = Insert(make_pair(key, V()));
		return ret.first->second;
	}
private:
	RBTree<K, std::pair<K, V>, MapKeyOfValue> _tree;
};

#include <string>

void TestMap()
{
	Map<string, string> dict;
	dict.Insert(make_pair("sort", "≈≈–Ú"));
	dict.Insert(make_pair("map", "”≥…‰"));
	dict["left"] = "◊Û±ﬂ";
	dict["left"] = " £”‡";

	Map<string, string>::iterator it = dict.begin();
	while (it != dict.end())
	{
		cout << it->first << ":" << it->second << endl;
		++it;
	}
}