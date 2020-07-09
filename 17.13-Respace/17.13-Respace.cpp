#include <cmath>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

// 字典树标准写法
class Trie {
  public:
    Trie* next[26] = {nullptr};
    bool isEnd;
    Trie() {isEnd = false;}
    void insert(string s) {
        Trie *curPos = this;
        for (int i = s.size() - 1; i >= 0; --i) {
            int t = s[i] - 'a';
            if (curPos->next[t] == nullptr)
                curPos->next[t] = new Trie();
            curPos = curPos->next[t];
        }
        curPos->isEnd = true;
    }
};

// Trie + dp - dp[i]表示前i个字符最小的未识别数量, 问题转化为和前n状态相关的状态转移dp, 每个字符都要对过去的字符串反向扫描一次
// dp[i] = min(dp[i], dp[j - 1]) if dp[j, i]代表的sentence[j - 1, i - 1]在字典中找到, 其中j <= i
// dp[i] = dp[i - 1] + 1 if 没有找到的dp[j, i]
// time: O(|dictionary + n^2|)
// space: O(|dictionary|*26 + n)
class Solution1 {
  public:
    int respace(vector<string>& dictionary, string sentence) {
        int len = sentence.size(), inf = 0x3f3f3f3f;
        Trie* root = new Trie();    // 构造字典树
        for (auto &word: dictionary)
            root->insert(word);
        vector<int> dp(len + 1, inf);
        dp[0] = 0;
        for (int i = 1; i <= len; i++) {
            dp[i] = dp[i - 1] + 1;
            Trie* curPos = root;
            for (int j = i; j >= 1; --j) {  // 沿字典树搜索
                int t = sentence[j - 1] - 'a';
                if (curPos->next[t] == nullptr)
                    break;
                else if (curPos->next[t]->isEnd)
                    dp[i] = min(dp[i], dp[j - 1]);
                if (dp[i] == 0)
                    break;
                curPos = curPos->next[t];
            }
        }
        return dp[len];
    }
};

class RKHash {
  public:
    using LL = long long;
    static constexpr LL P = (1LL << 31) - 1;    // INT_MAX 素数 - 取模 static 所有类实例共用 constexpr编译时可计算 LL字符后缀
    static constexpr LL BASE = 41;  // 素数 - 进制  不用写构造函数, 因为完全可以不支持自定义素数

    LL getHash(const string &s) {
        LL hashValue = 0;
        for (int i = s.size() - 1; i >= 0; --i) {
            hashValue = hashValue * BASE + s[i] - 'a' + 1;
            hashValue %= P;
        }
        return hashValue;
    }
};

// dp + RK方法- dp[i]表示前i个字符最小的未识别数量, 问题转化为和前n状态相关的状态转移dp, 每个字符都要对过去的字符串反向扫描一次
// dp[i] = min(dp[i], dp[j - 1]) if dp[j, i]代表的sentence[j - 1, i - 1]在字典中找到, 其中j <= i
// dp[i] = dp[i - 1] + 1 if 没有找到的dp[j, i]
// time: O(|dictionary + n^2|)
// space: O(n + q) q为词典中单词个数
class Solution {
  public:
    int respace(vector<string>& dictionary, string sentence) {
        using LL = long long;
        unordered_set<LL> hashValues;
        RKHash irkhash;
        for(const auto &word : dictionary)
            hashValues.insert(irkhash.getHash(word));
        vector<int> dp(sentence.size() + 1, sentence.size());   // 带初始状态的dp
        dp[0] = 0;
        for (int i = 1; i <= sentence.size(); ++i) {    // dp索引
            dp[i] = dp[i - 1] + 1;
            LL hashValue = 0;
            for (int j = i; j >= 1; j--) {  // dp[j,i]代表sentence[j - 1, i - 1]
                int t = sentence[j - 1] - 'a' + 1;  
                hashValue = hashValue * irkhash.BASE + t;
                hashValue %= irkhash.P;
                if (hashValues.find(hashValue) != hashValues.end())
                    dp[i] = min(dp[i], dp[j - 1]);
            }
        }
        return dp[sentence.size()];
    }
};

int main() {
    Solution s;
    vector<string> dict = {"looked", "just", "like", "her", "brother"};
    string sent = "jesslookedjustliketimherbrother";
    cout << s.respace(dict, sent) << endl;
    return 0;
}