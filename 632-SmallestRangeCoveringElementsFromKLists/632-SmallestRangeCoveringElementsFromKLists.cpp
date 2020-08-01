#include <queue>
#include <cmath>
#include <limits>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// k个数组的极值问题 - 堆 - 注意自己的实现和别人的实现方式稍有不同
// time: O(n * k * lgk)
// space: O(k)
class Solution1 {
  private:
    struct point{
        int val;
        int idx;
        int pos;
        point(int val, int idx, int pos): val(val), idx(idx), pos(pos){};
        bool operator< (const point &other) const {
            return this->val < other.val;
        }
        bool operator> (const point &other) const {
            return this->val > other.val;
        }
        bool operator>= (const point &other) const {
            return this->val >= other.val;
        }
        bool operator<= (const point &other) const {
            return this->val <= other.val;
        }
    };
  public:
    vector<int> smallestRange(vector<vector<int>> &nums) {
        priority_queue<point, vector<point>, greater<point>> ipq;  // 最小堆
        int k = nums.size(), small = 0, big = 0;
        vector<int> ans{0, INT_MAX};
        for (int i = 0; i < k; i++) {
            ipq.push(point(nums[i][0], i, 0));
            big = max(big, nums[i][0]);
        }
        do {
            point cur = ipq.top(); ipq.pop();
            small = cur.val;    // 出栈最小, 入栈最大
            if (big - small < ans[1] - ans[0]) {
                ans[0] = small;
                ans[1] = big;
            }
            if (cur.pos + 1 < nums[cur.idx].size()) {
                ipq.push(point(nums[cur.idx][cur.pos + 1], cur.idx, cur.pos + 1)); 
                big = max(big, nums[cur.idx][cur.pos + 1]); // 都是有序数组, 可以这样维护最小值
            }
        }while (ipq.size() == k);
        return ans;
    }
};

// k个数组的极值问题 - 堆
// time: O(n * k * lgk)
// space: O(k)
class Solution2 {
  public:
    vector<int> smallestRange(vector<vector<int>> &nums) {
        int k = nums.size(), ileft = 0, iright = INT_MAX, imin = 0, imax = 0;
        vector<int> next(k, 0); // 维护指针
        auto cmp = [&](const int u, const int v) {
          return nums[u][next[u]] > nums[v][next[v]];
        };
        priority_queue<int, vector<int>, decltype(cmp)> ipq(cmp);  // 最小堆, 比较函数依赖于next
        for (int i = 0; i < k; i++) {
            ipq.emplace(i);
            imax = max(imax, nums[i][0]);
        }
        while (true) {
            int row = ipq.top(); ipq.pop();
            imin = nums[row][next[row]];
            if (imax - imin < iright - ileft) {
                ileft = imin;
                iright = imax;
            }
            if (next[row] == nums[row].size() - 1) break;   // 保证next能访问到
            ++next[row];
            imax = max(imax, nums[row][next[row]]); // 因为各个子数组单调递增, 因此可以这样维护
            ipq.emplace(row);
        };
        return {ileft, iright};
    }
};

// Hash + SW
// time: O(n * k + O(V)) V是列表中元素值域
// space: O(nk)
class Solution {
  public:
    vector<int> smallestRange(vector<vector<int>> &nums) {
        int k = nums.size();
        unordered_map<int, vector<int>> indices;
        int xMin = INT_MAX, xMax = INT_MIN;
        for (int i = 0; i < k; ++i) {   // 建立哈希映射表
            for (const int &x : nums[i]) {
                indices[x].push_back(i);
                xMin = min(xMin, x);    // 值域范围最小值
                xMax = max(xMax, x);    // 值域范围最大值
            }
        }
        vector<int> freq(k, 0);
        int inside = 0, iLeft = xMin, iRight = xMin - 1, iBestLeft = xMin, iBestRight = xMax;   // 以值为准更新左右边界
        while (iRight < xMax) {
            ++iRight;   // 滑动窗口右侧更新
            if (indices.count(iRight)) {    // 建立频数表
                for (const int &x : indices[iRight]) {
                    ++freq[x];
                    if (freq[x] == 1)
                        ++inside;
                }
            }
            while (inside == k) {   // 区域计数
                if (iRight - iLeft < iBestRight - iBestLeft) {
                    iBestLeft = iLeft;
                    iBestRight = iRight;
                }
                if (indices.count(iLeft)) { // 更新左边界
                    for (const int &x : indices[iLeft]) {
                        --freq[x];
                        if (freq[x] == 0)
                            --inside;
                    }
                }
                ++iLeft;    // 滑动窗口左侧更新
            }
        }
        return {iBestLeft, iBestRight};
    }
};

int main() {
    Solution s;
    vector<vector<int>> nums0 = {{4, 10, 15, 24, 26}, {0, 9, 12, 20}, {5, 18, 22, 30}};
    vector<vector<int>> nums1 = {{4}, {5}, {6}};
    vector<vector<int>> nums2 = {{1, 2, 3}, {1, 2, 3}, {1, 2, 3}};
    vector<vector<int>> nums3 = {{1}};
    show1DVector(s.smallestRange(nums0));
    show1DVector(s.smallestRange(nums1));
    show1DVector(s.smallestRange(nums2));
    show1DVector(s.smallestRange(nums3));
    return 0;
}