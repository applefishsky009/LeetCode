#include <stack>
#include <iostream>
using namespace std;

class CQueue1 {
  public:
    CQueue() {

    }
    void appendTail(int val) {
        if (input.empty())
            tranStack();
        input.push(val);
    }
    int deleteHead() {
        int ans = 0;
        if (output.empty())
            tranStack();
        if (output.empty()) return -1;
        ans = output.top();
        output.pop();
        return ans;
    }
  private:
    stack<int> input;
    stack<int> output;
    void tranStack() {
        if (input.empty()) {
            while(!output.empty()) {
                input.push(output.top());
                output.pop();
            }
        } else {
            while (!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }
    }
};

// 去除重复操作
class CQueue {
  public:
    CQueue() {
        while (!input.empty()) input.pop();
        while (!output.empty()) output.pop();
    }
    void appendTail(int val) {
        input.push(val);
    }
    int deleteHead() {
        int ans = 0;
        if (output.empty()) {   //先进先出,input在上,output在下,栈底背靠背
            while (!input.empty()) {
                output.push(input.top());
                input.pop();
            }
        }
        if (output.empty()) return -1;
        ans = output.top();
        output.pop();
        return ans;
    }
  private:
    stack<int> input;
    stack<int> output;
};

int main() {
    CQueue cq;
    cq.appendTail(3);
    cout << cq.deleteHead() << endl;
    cout << cq.deleteHead() << endl;
    // cout << cq.deleteHead() << endl;
    // cq.appendTail(5);
    // cq.appendTail(2);
    // cout << cq.deleteHead() << endl;
    // cout << cq.deleteHead() << endl;
    return 1;
}
