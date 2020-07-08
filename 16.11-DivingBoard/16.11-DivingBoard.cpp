#include <vector>
#include <iostream>
// #include <unordered_set>
#include <set>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// 使用set去重排序
// time: O(k)
// space: O(1)
class Solution1 {
  public:
    vector<int> divingBoard(int shorter, int longer, int k) {
        int len = shorter * k, short_cnt = k;
        // unordered_set<int> ius;
        set<int> is;
        vector<int> ans;
        if (k == 0) return ans;
        do{
            is.insert(len);
            len -= shorter;
            len += longer;
            short_cnt--;
        } while(short_cnt >= 0);
        for (auto p = is.begin(); p != is.end(); p++)
            ans.push_back(*p);
        return ans;
    }
};

// 实际上就是有序的
// time: O(k)
// space: O(1)
class Solution2 {
  public:
    vector<int> divingBoard(int shorter, int longer, int k) {
        if (k == 0) return vector<int> {};
        int len = shorter * k, short_cnt = k;
        if (shorter == longer) return vector<int> (1, len);
        vector<int> ans;
        do{
            ans.push_back(len);
            len -= shorter;
            len += longer;
            short_cnt--;
        } while(short_cnt >= 0);
        return ans;
    }
};

// 进一步优化 - 使用det, 优化掉push_back
// time: O(k)
// space: O(1)
class Solution {
  public:
    vector<int> divingBoard(int shorter, int longer, int k) {
        if (k == 0) return vector<int> {};
        int len = shorter * k, short_cnt = k, det = longer - shorter;
        if (shorter == longer) return vector<int> (1, len);
        vector<int> ans(k + 1, 0);
        do{
            ans[k - short_cnt] = len;
            len += det;
        } while(--short_cnt >= 0);
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> ans0 = s.divingBoard(1, 1, 3);
    vector<int> ans1 = s.divingBoard(1, 2, 3);
    show1DVector(ans0);
    show1DVector(ans1);
    return 0;
}