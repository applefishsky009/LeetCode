#include <string>
#include <iostream>
using namespace std;

// DFS, 存在重复搜索的情况，可以优化
class Solution1 {
  public:
    int translateNum(int num) {
        return dfs(num);
    }
  private:
    int dfs(int num) {
        if (num < 10)
            return 1;
        return (num % 100 > 25 || num % 100 < 10) ? dfs(num / 10) : dfs(num / 10) + dfs(num / 100);
    }
};

// 动态规划,只与过去两个状态有关,因此用两个变量存起来
class Solution {
  public:
    int translateNum(int num) {
        string src = to_string(num);
        int p = 0, q = 0, r = 1;    // 
        for (int i = 0; i < src.size(); i++) {
            p = q; q = r; r = 0; r += q;    // r += q是当前位,解没有变多
            if (i == 0) // 不能取到过去的两个字符
                continue;
            auto pre = src.substr(i - 1, 2);
            if (pre <= "25" && pre >= "10") // 过去两位,解增加了
                r += p;
        }
        return r;
    }
};

int main() {
    Solution s;
    cout << s.translateNum(12258) << endl;
    cout << s.translateNum(648006092) << endl;
    cout << s.translateNum(506) << endl;
    cout << s.translateNum(0) << endl;
    return 1;
}