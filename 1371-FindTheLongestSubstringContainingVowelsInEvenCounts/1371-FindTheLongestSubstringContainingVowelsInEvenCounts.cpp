#include <string>
#include <vector>
#include <cmath>
#include <iostream>
using namespace std;

// 假设目标字符串区间为[left, right],中间一定有偶数个元音字符编码,编码增量为00000,那么[0, left - 1]和[0, right]的编码必然相同.
// 如果[0, left - 1]和[0, right]的编码不相同,那么编码中必然有一位不同，即[left, right]中必然存在奇数的元音字符。
class Solution {
public:
    int findTheLongestSubstring(string s) {
        int i = 0, j = 0, ans = 0, mask = 0, n = s.size();
        const char c[5] = {'a', 'e', 'i', 'o', 'u'};
        vector<int> h(32, n + 1);   // 可能的掩码共32种，初始化为n + 1，因为要维护第一次出现掩码的位置。
        h[0] = -1;  // 这个掩码表示没有出现任何元音字符，字符长度+1。
        for (i = 0; i < n; i++) {
            for (j = 0; j < 5; j++)
                if (s[i] == c[j])
                    mask ^= (1 << j);   // 计算掩码
            ans = max(ans, i - h[mask]);    // 对于当前掩码，用i减去第一次出现这个掩码的位置，即得到一个以i结尾的极大子区间，随i增加，该子区间也增加。
            h[mask] = min(h[mask], i);  // 第一次出现该掩码的位置
        }
        return ans;
    }
};

int main() {
    Solution s;
    // string str = "eleetminicoworoep";  // 13
    string str = "lsss";  // 4
    cout << s.findTheLongestSubstring(str) << endl;
    return 0;
}