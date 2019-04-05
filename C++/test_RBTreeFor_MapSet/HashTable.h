#pragma once
#include <vector>

template<class Value>
struct HashNode
{
	HashNode* _next;
	Value _value;

	HashNode(const Value& v)
		:_value(v)
		, _next(nullptr)
	{}
};

// 前置声明
template<class K, class Value, class KeyOfValue, class Hash>
class HashTable;

template<class K, class Value, class KeyOfValue, class Hash>
struct HTIterator
{
	typedef HashNode<Value> Node;

	typedef HTIterator<K, Value, KeyOfValue, Hash> Self;
	typedef HashTable<K, Value, KeyOfValue, Hash> HT;

	Node* _node;
	HT* _ht;

	HTIterator(Node* node, HT* ht)
		:_node(node)
		, _ht(ht)
	{}

	Self& operator++()
	{
		// 1.如果当前桶还未走完，则取桶中的下一个数据
		// 2.如果当前桶走完了，则找下一个不为空的桶
		KeyOfValue kov;
		if (_node->_next)
		{
			_node = _node->_next;
		}
		else
		{
			// 从下一个位置开始找
			size_t index = _ht->HashFunc(kov(_node->_value), _ht->_table.size());
			index += 1;
			for (; index < _ht->_table.size(); ++index)
			{
				if (_ht->_table[index] != nullptr)
				{
					_node = _ht->_table[index];
					break;
				}
			}

			if (index == _ht->_table.size())
			{
				_node = nullptr;
			}
		}

		return *this;
	}

	Value& operator*()
	{
		return _node->_value;
	}

	Value* operator->()
	{
		return &_node->_value;
	}

	bool operator!=(const Self& s)
	{
		return _node != s._node;
	}
};

template<class K, class Value, class KeyOfValue, class Hash>
class HashTable
{
	template<class K, class Value, class KeyOfValue, class Hash>
	friend struct HTIterator;

	typedef HashNode<Value> Node;
public:
	typedef HTIterator<K, Value, KeyOfValue, Hash> iterator;

	// 拷贝 + 析构 待完成

	iterator begin()
	{
		for (size_t i = 0; i < _table.size(); ++i)
		{
			if (_table[i] != nullptr)
			{
				return iterator(_table[i], this);
			}
		}

		return iterator(nullptr, this);
	}

	iterator end()
	{
		return iterator(nullptr, this);
	}

	size_t GetNextPrime(size_t prime)
	{
		static const int PRIMECOUNT = 28;
		static const size_t primeList[PRIMECOUNT] =
		{
			53ul, 97ul, 193ul, 389ul, 769ul,
			1543ul, 3079ul, 6151ul, 12289ul, 24593ul,
			49157ul, 98317ul, 196613ul, 393241ul, 786433ul,
			1572869ul, 3145739ul, 6291469ul, 12582917ul, 25165843ul,
			50331653ul, 100663319ul, 201326611ul, 402653189ul, 805306457ul,
			1610612741ul, 3221225473ul, 4294967291ul
		};

		size_t i = 0;
		for (; i < PRIMECOUNT; ++i)
		{
			if (primeList[i] > prime)
				return primeList[i];
		}
		return primeList[i];
	}

	void CheckCapacity()
	{
		// 负载因子到1时增容
		KeyOfValue kov;
		if (_size == _table.size())
		{
			vector<Node*> newtable;
			newtable.resize(GetNextPrime(_table.size()));
			for (size_t i = 0; i < _table.size(); ++i)
			{
				Node* cur = _table[i];
				while (cur != nullptr)
				{
					size_t index = HashFunc(kov(cur->_value), newtable.size());
					Node* next = cur->_next;

					// 迁移头插到新表
					cur->_next = newtable[index];
					newtable[index] = cur;

					cur = next;
				}

				_table[i] = nullptr;
			}

			_table.swap(newtable);
		}
	}

	pair<iterator, bool> Insert(const Value& v)
	{
		CheckCapacity();

		KeyOfValue kov;
		size_t index = HashFunc(kov(v), _table.size());

		Node* cur = _table[index];
		while (cur != nullptr)
		{
			if (kov(cur->_value) == kov(v))
			{
				//return false;
				return make_pair(iterator(cur, this), false);
			}

			cur = cur->_next;
		}

		// 头插
		Node* newnode = new Node(v);
		newnode->_next = _table[index];
		_table[index] = newnode;
		++_size;

		//return true;
		return make_pair(iterator(newnode, this), false);
	}

	void PrintBucketNum()
	{
		int maxnum = 0;
		for (size_t i = 0; i < _table.size(); ++i)
		{
			size_t num = 0;
			Node* cur = _table[i];
			while (cur)
			{
				++num;
				cur = cur->_next;
			}
			cout << num << endl;

			if (maxnum < num)
				maxnum = num;
		}

		cout << "max:" << maxnum << endl;
	}

	size_t HashFunc(const K& key, size_t n)
	{
		Hash hash;
		return hash(key) % n;
	}
private:
	vector<Node*> _table;	// 哈希表
	size_t _size = 0;		// 有效数据个数
};