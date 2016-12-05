#include <list>
#include <iostream>
#include <iterator>
#include <unordered_map>
using namespace std;

//经典页面置换算法，相似的经典问题ip消息时间窗算法，一起分析
class LRUCache
{
  private:
    struct CacheNode
    {
        int key;
        int value;
        CacheNode(int k, int v) : key(k), value(v){};
    };
    int capacity;
    list<CacheNode> valList;
    unordered_map<int, list<CacheNode>::iterator> listMap;

  public:
    LRUCache(int capacity)
    {
        this->capacity = capacity;
    }

    int get(int key)
    {
        if (listMap.find(key) == listMap.end())
            return -1;
        valList.splice(valList.begin(), valList, listMap[key]);
        //cacheMap[key] = cacheList.begin();    splice()方法不会使迭代器失效，因此不需要这一句
        return listMap[key]->value;
    }

    void set(int key, int value)
    {
        if (listMap.find(key) == listMap.end())
        {
            if (valList.size() == capacity)
            {
                //这里要根据链表最后一个的值来擦除哈希表的键，因此链表结构必须是键值结构体,单纯的int不能逆向访问
                listMap.erase(valList.back().key);
                valList.pop_back();
            }
            valList.push_front(CacheNode(key, value));
            listMap[key] = valList.begin();
        }
        else
        {
            listMap[key]->value = value;
            valList.splice(valList.begin(), valList, listMap[key]);
            //cacheMap[key] = cacheList.begin();
        }
    }
};

int main()
{
    LRUCache example(5);
    example.set(1, 10);
    example.set(2, 9);
    example.set(3, 8);
    example.set(4, 7);
    example.set(5, 6);
    for (int i = 1; i <= 5; ++i)
        cout << example.get(i) << endl;
    example.set(11, 11);
    for (int i = 1; i <= 5; ++i)
        cout << example.get(i) << endl;
    return 0;
}