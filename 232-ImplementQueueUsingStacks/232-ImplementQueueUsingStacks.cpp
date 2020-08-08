#include <stack>
#include <iostream>
using namespace std;

// 两个栈 - 压入时放在最下面
// time: 压入O(n), 弹出O(1)
// space: O(n)
class MyQueue {
  public:
    MyQueue() {
        ;
    }
    void push(int x) {
        while (!istack_up.empty()) {
            istack_bottom.push(istack_up.top());
            istack_up.pop();
        }
        istack_up.push(x);
        while (!istack_bottom.empty()) {
            istack_up.push(istack_bottom.top());
            istack_bottom.pop();            
        }
    }
    int pop() {
        int cur = istack_up.top();
        istack_up.pop();
        return cur;
    }
    int peek() {    // top
        return istack_up.top();
    }
    bool empty() {
        return istack_up.empty();
    }
  private:
    stack<int> istack_up;   // 负责存放数组
    stack<int> istack_bottom;   // 负责push的时候数据转移
};

// 两个栈
// time: 压入O(1), 弹出O(1)
// space: O(n)
class MyQueue1 {
  public:
    MyQueue1() {
        ;
    }
    void push(int x) {
        istack_bottom.push(x);
    }
    int pop() {
        if (istack_up.empty()) {
            while (!istack_bottom.empty()) {
                istack_up.push(istack_bottom.top());
                istack_bottom.pop();
            }
        }
        int cur = istack_up.top();
        istack_up.pop();
        return cur;
    }
    int peek() {    // top
        if (istack_up.empty()) {
            while (!istack_bottom.empty()) {
                istack_up.push(istack_bottom.top());
                istack_bottom.pop();
            }
        }
        return istack_up.top();
    }
    bool empty() {
        return istack_up.empty() && istack_bottom.empty();
    }
  private:
    stack<int> istack_up;   // 负责pop
    stack<int> istack_bottom;   // 负责push
};

int main() {
    MyQueue *iqueue = new MyQueue();
    // iqueue->push(1);
    // iqueue->push(2);
    // cout << iqueue->peek() << endl; // 1
    // cout << iqueue->pop() << endl;  // 1
    // cout << iqueue->empty() << endl;    // 0
    iqueue->push(1);
    iqueue->push(2);
    cout << iqueue->peek() << endl; // 1
    iqueue->push(3);
    cout << iqueue->peek() << endl; // 1
    return 0;
}
