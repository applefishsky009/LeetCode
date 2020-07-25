#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
using namespace std;

// DP idp[i][j]表示数组前i个元素分成j个连续组的各自和的最小值
// idp[i][j] = min(idp[k][j - 1] + sum[k + 1, i]), 0 <= k < i, 前k个数被分为j - 1段
// 初始化: i < j idp[i][j] = INT_MAX i >= j; i < j不合法 - 表示i个元素最多分为i组
// idp[0][0] = 0; j = 1表示前i个数分为一组, 则k = 0, k != 0时idp[k][0]非法.
// time: O(n^2 * m)
// space: O(n * m)
class Solution1 {
  public:
    int splitArray(vector<int> &nums, int m) {
        int len = nums.size();
        vector<vector<long long>> idp(len + 1, vector<long long>(m + 1, LLONG_MAX));
        vector<long long> sub(len + 1, 0);
        for (int i = 0; i < len; ++i)
            sub[i + 1] = sub[i] + nums[i];
        idp[0][0] = 0;
        for (int i = 0; i <= len; ++i)
            for (int j = 1; j <= min(i, m); ++j)    // 最多i或者m组
                for (int k = 0; k < i; ++k) // 前k个数被分为j - 1段
                    idp[i][j] = min(idp[i][j], max(idp[k][j - 1], sub[i] - sub[k]));
        return (int)idp[len][m];
    }
};

// binary search    以x分割, 计算分割数量是否小于m  如果小于m, 说明分割数量太少, x太大.
// time: O(n * lg(sum - maxn))
// space: O(1)
class Solution {
  public:
    int splitArray(vector<int> &nums, int m) {
        int len = nums.size();
        long long left = 0, right = 0;
        for (int i = 0; i < len; ++i) {
            right += nums[i];
            if (left < nums[i])
                left = nums[i];
        }
        while (left < right) {
            long long mid = left + ((right - left) >> 1);
            if (check(nums, mid, m))    // 分割数量太少, mid太大
                right = mid;
            else
                left = mid + 1;
        }
        return left;
    }
  private:
    bool check(vector<int> &nums, int x, int m) {   // 以x分割, 计算分割数量是否小于m
        long long sum = 0;
        int cnt = 1, len = nums.size();
        for (int i = 0; i < len; ++i) {
            if (sum + nums[i] > x) {
                cnt++;
                sum = nums[i];
            } else
                sum += nums[i];
        }
        return cnt <= m;
    }
};

int main() {
    Solution s;
    vector<int> nums = {7, 2, 5, 10 ,8};
    cout << s.splitArray(nums, 2) << endl;
    return 0;
}