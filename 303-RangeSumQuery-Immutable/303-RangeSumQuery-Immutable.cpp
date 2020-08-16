#include <vector>
#include <iostream>
using namespace std;

// DP Cache - sums[i]表示不包含i的前缀和
// time: 查询O(1) 预计算O(n)
// space: O(n)
class NumArray{
  public:
    NumArray(vector<int> &nums) {
        sums.resize(nums.size() + 1, 0);
        for (int i = 1; i <= nums.size(); ++i)
            sums[i] = sums[i - 1] + nums[i - 1];    // 前n项和
    }
    int sumRange(int i, int j) {
        return sums[j + 1] - sums[i];   // [i, j]的和
    }
  private:
    vector<int> sums;
};

int main() {
    vector<int> nums0 = {-2, 0, 3, -5, 2, -1};
    NumArray s(nums0);
    cout << s.sumRange(0, 2) << endl;   // 1
    cout << s.sumRange(2, 5) << endl;   // -1
    cout << s.sumRange(0, 5) << endl;   // -3
    return 0;
}