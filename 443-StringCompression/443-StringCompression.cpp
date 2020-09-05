#include <string>
#include <vector>
#include <iostream>
using namespace std;

// 双指针
// time: O(n)
// space: O(1)
class Solution {
  public:
    int compress(vector<char> &chars) {
        char cur = chars[0];
        int slow = 0, fast = 0, cnt = 1;    // 保证有第一个字符
        chars.push_back(1); // 做了边界保护的需要加, 一般不用加
        for (int fast = 1; fast < chars.size(); ++fast) {
            if (chars[fast] == cur) {   // 不是新出现的字符, 计数
                ++cnt;
            } else {    // 新字符
                if (cnt > 1) {  // 数字转化
                    string s_cnt = to_string(cnt);
                    for (auto &c : s_cnt) 
                        chars[++slow] = c;
                }
                chars[++slow] = chars[fast];    // 放在慢指针的位置
                cur = chars[fast];  // 新出现的字符
                cnt = 1;    // 新出现了一个字符
            }
        }
        return slow;
    }
};

int main() {
    Solution s;
    vector<char> chars0 = {'a', 'a', 'b', 'b', 'c', 'c', 'c'};   // 6
    vector<char> chars1 = {'a'};   // 1
    vector<char> chars2 = {'a', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b', 'b'};   // 12
    cout << s.compress(chars0) << endl; // 6
    cout << s.compress(chars1) << endl; // 1
    cout << s.compress(chars2) << endl; // 4
    return 0;
}