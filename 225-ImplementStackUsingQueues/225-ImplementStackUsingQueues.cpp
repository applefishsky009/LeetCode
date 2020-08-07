#include <queue>
#include <iostream>
using namespace std;

// 一个队列
// time: 压入O(1), 弹出O(n)
// space: O(n)
class MyStack0 {
  public:
    MyStack0() {
        ;
    }
    void push(int x) {
        ip.push(x);
    }
    int pop() {
        int n = ip.size(), cur = 0;
        for (int i = 0; i < n - 1; ++i) {
            cur = ip.front(); 
            ip.pop();
            ip.push(cur);
        }
        cur = ip.front();
        ip.pop();
        return cur;
    }
    int top() {
        int n = ip.size(), cur = 0;
        for (int i = 0; i < n; ++i) {
            cur = ip.front(); 
            ip.pop();
            ip.push(cur);
        }
        return cur;
    }
    bool empty() {
        return ip.empty();
    }
  private:
    queue<int> ip;
};

// 一个队列
// time: 压入O(n), 弹出O(1)
// space: O(n)
class MyStack {
  public:
    MyStack() {
        ;
    }
    void push(int x) {
        int n = ip.size(), cur = 0;
        ip.push(x);
        for (int i = 0; i < n; ++i) {
            cur = ip.front(); 
            ip.pop();
            ip.push(cur);
        }
    }
    int pop() {
        int cur = ip.front();
        ip.pop();
        return cur;
    }
    int top() {
        int cur = ip.front();
        return cur;
    }
    bool empty() {
        return ip.empty();
    }
  private:
    queue<int> ip;
};

int main() {
    MyStack *istack = new MyStack();
    istack->push(1);
    istack->push(2);
    cout << istack->top() << endl;   // 2
    cout << istack->pop() << endl;   // 2
    cout << istack->empty() << endl; // 0
    return 0;
}