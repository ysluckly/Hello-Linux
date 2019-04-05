/*************************************************************************
    > File Name:    lru.cpp
    > Author:       Hunter
    > Mail:         hunter.520@qq.com 
    > Created Time: Tue 02 Apr 2019 08:16:22 PM PDT
 ************************************************************************/
/*set操作:
 * 我们用一个队列去纪录我们的数据使用的顺序，在队列的最尾端是最早使用的数据，也就是最近使用最少的数据。
 * 1.当set一个key-value后，我们首先寻找这个key是否在哈希map中能找到，如果找到了就找到了对应list中的迭代器了，我们把list对应的那个结点调整到队列首，表示最新使用的，并且把哈希map中key对应的值重新指向调整后的结点
 * 2.如果没有找到说明要增加新数据，先判断容量够不够用，如果够用（size < cap）直接size要++，同时要向队列中插入一个key-value，并且哈希map中也要生成一个key-value指向list中的结点，如果容量(size == cap)不够用就要淘汰最不经常使用的结点(实际上就是list中的尾结点)，怎么删除呢? 先用list中尾结点的key值把哈希map中的映射关系删除掉，然后再删除list中的尾结点，最后再添加新结点。
 *
 * get操作:
 * get操作就是读取对应key值对应的value值，需要做的就是每次读取后，如果key值存在就把key值对应的list结点调整到首部，表示最新使用的，并且调整哈希map中key对应的结点
 * 如果key没有对应的结点就直接返回-1即可。
 * */
#include <iostream>
#include <unordered_map>
#include <list>
#include <assert.h>

using namespace std;
class LRUCache {
public:
    LRUCache(int capacity):cap(capacity),size(0) {
           if(cap == 0)
               assert(false);
    }
    
    int get(int key) {
        int value = -1;
        auto it = key_list_map.find(key);
        if(it==key_list_map.end())
        {
            return -1;
        }
        else
        {
            value = it->second->second;  
            ls.erase(it->second);
            ls.push_front(pair<int,int>(key,value));
            it->second = ls.begin();
  
            return value;
        }
    }
    
    void put(int key, int value) {
        auto it = key_list_map.find(key);
        if(it==key_list_map.end())
        {
            if(cap == size)
            {
                //用list中的key删除unorderedmap中的关系
                key_list_map.erase(ls.back().first);
                ls.pop_back();
            }
            else
            {
                ++size;
            }
        }
        else
        {
            ls.erase(it->second);//用迭代器删除
        }
        //重新入一个新的键值对
        //重新建立映射关系
        ls.push_front(pair<int,int>(key,value));
         key_list_map[key] = ls.begin();
    }
    
    int cap;
    int size;
    std::list< std::pair<int,int> > ls;
    std::unordered_map<int,std::list< std::pair<int,int> >::iterator> key_list_map; 
    
};

int main(int argc, char* argv[])
{

    return 0;
}

