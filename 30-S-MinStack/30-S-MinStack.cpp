#include <stack>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// stack
// time: O(n)
// space: O(n)
class MinStack {
  public:
    MinStack() {

    }
    void push(int x) {
        int cur_min = istk.empty() ? x : ::min(x, istk.top().second);
        istk.push(pair(x, cur_min));
    }
    void pop() {
        istk.pop();
    }
    int top() {
        return istk.top().first;
    }
    int min() {
        return istk.top().second;
    }
  private:
    stack<pair<int, int>> istk;
};

int main() {
    MinStack *obj = new MinStack();
    obj->push(-2);
    obj->push(0);
    obj->push(-3);
    int param_3 = obj->min();
    obj->pop();
    int param_4 = obj->top();
    int param_5 = obj->min();
    cout << param_3 << endl;
    cout << param_4 << endl;
    cout << param_5 << endl;
    return 0;
}