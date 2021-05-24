#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// HT Sort
// time: O(n)
// space: O(n)
class Solution {
  public:
    int hIndex(vector<int> &citations) {
        int ilen = citations.size();
        vector<int> papers(ilen + 1, 0);
        for (auto &citation : citations) {  // 计数排序
            papers[min(citation, ilen)]++;
        }
        int k = ilen;   // k = 当前论文数量
        for (int s = papers[ilen]; k > s; s += papers[k]) {  // s = 引用大于等于k的累计数量
            k--;    
        } // k <= s即至少k篇论文的引用大于k
        return k;
    }
};

int main() {
    Solution s;
    vector<int> citations = {3, 0, 6, 1, 5};
    cout << s.hIndex(citations) << endl;
    return 0;
}