#include <stack>
#include <iostream>
using namespace std;

// Stack
// time: O(n)
// space: O(n)
class MinStack {
  public:
    MinStack() {
    }
    void push(int x) {
        inum.push(x);
        if (imin.empty() || x <= imin.top()) {
            imin.push(x);
        }
    }
    void pop() {
        if (inum.top() == imin.top()) {
            imin.pop();
        }
        inum.pop();
    }
    int top() {
        return inum.top();
    }
    int getMin() {
        return imin.top();
    }
  private:
    stack<int> inum;
    stack<int> imin;
};

int main() {
    MinStack *minStack = new MinStack();
    minStack->push(0);
    minStack->push(1);
    minStack->push(0);
    cout << minStack->getMin() << endl;
    minStack->pop();
    cout << minStack->top() << endl;
    cout << minStack->getMin() << endl;
    return 0;
}