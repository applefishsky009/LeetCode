#include <vector>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// BS
// time: O(nlgn)
// space: O(n)
class Solution {
  public:
    vector<int> findRightInterval(vector<vector<int>> &intervals) {
        int i = 0, start = 0, end = 0, mid = 0;
        vector<int> ans(intervals.size(), -1);
        for (i = 0; i < intervals.size(); ++i) {    // O(n)
            intervals[i].push_back(i);
        }
        sort(intervals.begin(), intervals.end(), [&](const auto &v1, const auto &v2){   // O(nlgn)
            return v1[0] < v2[0];
        });
        for (i = 0; i < intervals.size() - 1; ++i) {    // O(n)
            start = i;  // 注意区间可以是自己的右区间
            end = intervals.size() - 1;
            while (start <= end) {  // 找右区间 O(lgn)
                mid = start + ((end - start) >> 1);
                if (intervals[mid][0] < intervals[i][1]) {   // 一定在右侧区间
                    start = mid + 1;
                } else {    // 在左侧区间或者当前位置
                    end = mid - 1;
                }
            }   // 最终一定回归到start位置
            if (start < intervals.size())   // 更新右区间
                ans[intervals[i][2]] = intervals[start][2];
        }
        return ans;
    }
};

int main() {
    Solution s;
    // vector<vector<int>> intervals = {{3, 4}, {2, 3}, {1, 2}};    // -1 0 1
    // vector<vector<int>> intervals = {{1, 4}, {2, 3}, {3, 4}};   // -1 2 -1
    vector<vector<int>> intervals = {{1, 1}, {3, 4}};   // 0 -1
    show1DVector(s.findRightInterval(intervals));
    return 0;
}