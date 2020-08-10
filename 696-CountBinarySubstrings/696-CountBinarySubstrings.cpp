#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

// 暴力 - 超时
// time: O(n^2)
// space: O(1)
class Solution0 {
  public:
    int countBinarySubstrings(string s) {
        int zeroCount = 0, oneCount = 0, ans = 0;;
        for (int i = 0; i < s.size(); ++i) {
            int j = i;
            char start = s[j];
            zeroCount = 0; 
            oneCount = 0; 
            while (j < s.size() && s[j] == start) {
                ++zeroCount;
                ++j;
            }
            while (j < s.size() && s[j] != start) {
                ++j;
                ++oneCount;
                if (oneCount == zeroCount) {
                    ++ans;
                    break;
                }
            }

        }
        return ans;
    }
};

// 按字符分组-缓存记录01长度-可以缓存所有长度
// time: O(n)
// space: O(1)
class Solution1 {
  public:
    int countBinarySubstrings(string s) {
        int zeroCount = 0, oneCount = 0, ans = 0, i = 0;
        while (i < s.size()) {
            char start = s[i];
            while (i < s.size() && s[i] == start) {
                ++i;
                ++zeroCount;
            }
            ans += min(oneCount, zeroCount);
            oneCount = 0;
            while (i < s.size() && s[i] != start) {
                ++i;
                ++oneCount;
            }
            ans += min(oneCount, zeroCount);
            zeroCount = 0;
        }
        ans += min(oneCount, zeroCount);
        return ans;
    }
};

// 按字符分组
// time: O(n)
// space: O(1)
class Solution {
  public:
    int countBinarySubstrings(string s) {
        int last = 0, oneCount = 0, ans = 0, i = 0;
        while (i < s.size()) {
            char start = s[i];
            int count = 0;
            while (i < s.size() && s[i] == start) {
                ++i;
                ++count;
            }
            ans += min(last, count);
            last = count;
        }
        return ans;
    }
};

int main() {
    Solution s;
    string s0 = "10101"; // 4
    string s1 = "00110011"; // 6
    string s2 = "00110"; // 3
    string s3 = "00100"; // 2
    cout << s.countBinarySubstrings(s0) << endl;
    cout << s.countBinarySubstrings(s1) << endl;
    cout << s.countBinarySubstrings(s2) << endl;
    cout << s.countBinarySubstrings(s3) << endl;
    return 0;
}