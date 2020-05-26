#include <list>
#include <iostream>
#include <iterator>
#include <unordered_map>
using namespace std;

//经典页面置换算法，相似的经典问题ip消息时间窗算法，一起分析
class LRUCache {
  private:
    struct CacheNode{
        int key;
        int value;
        CacheNode(int k, int v) : key(k), value(v) {};
    };
    int capacity;
    list<CacheNode> valList;
    unordered_map<int, list<CacheNode>::iterator> listMap;

  public:
    LRUCache(int capacity) {
        this->capacity = capacity;
    }

    int get(int key) {
        if (listMap.find(key) == listMap.end())
            return -1;
        valList.splice(valList.begin(), valList, listMap[key]);
        // listMap[key] = valList.begin(); // C++98 is iterator C++11 is const iterator
        return listMap[key]->value;
    }

    void put(int key, int value) {
        if (listMap.find(key) == listMap.end()) { // 没找到，插入
            if (valList.size() == capacity) { // 容量已满，删除
                listMap.erase(valList.back().key);
                valList.pop_back();
            }
            valList.push_front(CacheNode(key, value));
            listMap[key] = valList.begin();
        } else {
            listMap[key]->value = value;    // 值重置
            valList.splice(valList.begin(), valList, listMap[key]);
            // listMap[key] = valList.begin(); // C++98 is iterator C++11 is const iterator
        }
    }
};

int main()
{
    LRUCache example(5);
    example.put(1, 10);
    example.put(2, 9);
    example.put(3, 8);
    example.put(4, 7);
    example.put(5, 6);
    for (int i = 1; i <= 5; ++i)
        cout << example.get(i) << endl;
    example.put(11, 11);
    for (int i = 1; i <= 5; ++i)
        cout << example.get(i) << endl;
    return 0;
}