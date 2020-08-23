#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// 模拟
// time: O(n)
// space: O(1)
class Solution0 {
  public:
    vector<string> fizzBuzz(int n) {
        vector<string> ans(n, "");
        for (int i = 1; i <= n; ++i) {
            ans[i - 1] += i % 3 == 0 ? "Fizz" : "";
            ans[i - 1] += i % 5 == 0 ? "Buzz" : "";
            ans[i - 1] += ans[i - 1].size() == 0 ? to_string(i) : "";
        }
        return ans;
    }
};

// 进阶 - 无数映射关系
// time: O(n)
// space: O(1)
class Solution {
  public:
    vector<string> fizzBuzz(int n) {
        vector<string> ans(n, "");
        map<int, string> imap = {{3, "Fizz"}, {5, "Buzz"}};
        for (int i = 1; i <= n; ++i) {
            for (auto p = imap.begin(); p != imap.end(); ++p)
                ans[i - 1] += i % p->first == 0 ? p->second : "";
            ans[i - 1] += ans[i - 1].size() == 0 ? to_string(i) : "";
        }
        return ans;
    }
};

int main() {
    Solution s;
    show1DVector(s.fizzBuzz(15));
    return 0;
}