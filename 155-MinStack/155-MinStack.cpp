#include <stack>
#include <iostream>
#include <algorithm>
using namespace std;

class MinStack
{
  private:
    stack<int> numStack;
    stack<int> minStack;

  public:
    void push(int x)
    {
        numStack.push(x);
        minStack.empty() ? minStack.push(x) : minStack.push(min(x, minStack.top()));
        //if (minStack.empty() || x <= getMin())  minStack.push(x); //update min only neccesary
    }

    void pop()
    {
        minStack.pop();
        //if (numStack.top() == getMin())  minStack.pop();  //update min only neccesary
        numStack.pop();
    }

    int top()
    {
        return numStack.top();
    }

    int getMin()
    {
        return minStack.top();
    }
};

int main()
{
    MinStack minStack; // = new MinStack();
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    cout << minStack.getMin() << endl;
    minStack.pop();
    cout << minStack.getMin() << endl;
    minStack.pop();
    cout << minStack.getMin() << endl;
    cout << minStack.top() << endl;
    return 0;
}