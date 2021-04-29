#include <stack>
#include <iostream>
using namespace std;

// Stack
// time: O(n)
// space: O(n)
class MyQueue {
  public:
    MyQueue() {
    }
    void push(int x) {
        itop.push(x);
    }
    int pop() {
        int ans = this->peek();
        ibottom.pop();
        return  ans;
    }
    int peek() {
        if (ibottom.empty()) {
            while (!itop.empty()) {
                ibottom.push(itop.top());
                itop.pop();
            }
        }
        return ibottom.top();
    }
    bool empty() {
        return itop.empty() && ibottom.empty();
    }
  private:
    stack<int> itop;
    stack<int> ibottom;
};

int main() {
    MyQueue *obj = new MyQueue();
    obj->push(1);
    obj->push(2);
    cout << obj->peek() << endl;
    cout << obj->pop() << endl;
    cout << obj->empty() << endl;
    return 0;
}