#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <D:\Github\RylModule\vector.h>
using namespace std;

class QuickSort {
  public:
    void randomizedQuickSort(vector<int>& g, int start, int end) {
        int q = 0;
        if (start < end) {
            q = randomizedPartion(g, start, end);
            randomizedQuickSort(g, start, q - 1);
            randomizedQuickSort(g, q + 1, end);
        }
    }
    void quickSort(vector<int>& g, int start, int end) {
        int q = 0;
        if (start < end) {
            q = partition(g, start, end);
            quickSort(g, start, q - 1);
            quickSort(g, q + 1, end);
        }
    }

  private:
    int randomizedPartion(vector<int>&g, int start, int end) {
        int dice_roll = 0;
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine generator(seed);
        uniform_int_distribution<int> distribution(start, end);
        dice_roll = distribution(generator);
        swap(g[dice_roll], g[end]);
        return partition(g, start, end);
    }
    int partition(vector<int>& g, int start, int end) {
        int i = start, j = start - 1;
        for (i = start; i < end; i++) { // end闭区间
            if (g[i] <= g[end])
                swap(g[i], g[++j]); // j闭区间
        }
        swap(g[++j], g[end]);
        return j;
    }
};

// 固定一个锚点,两边夹逼,退化为一个N-2个双指针的问题
class Solution {
  public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        if (nums.size() < 3)
            return ans;
        const int target = 0;
        // sort(nums.begin(), nums.end());
        QuickSort qs;
        qs.randomizedQuickSort(nums, 0, nums.size() - 1);
        auto last = nums.end();
        for (auto l = nums.begin(); l < last - 2; l++) {
            if (l > nums.begin() && *l == *(l - 1)) // 跳过l的重复元素
                continue;
            auto r = last - 1;
            auto m = l + 1;
            while (m < r) {
                if (*l + *m + *r < target) {
                    ++m;
                    while (*m == *(m - 1) && m < r) // 跳过m的重复元素
                        ++m;
                }else if (*l + *m + *r > target) {
                    --r;
                    while (*r == *(r + 1) && m < r) // 跳过r的重复元素
                        --r;
                }else {
                    ans.push_back(vector<int> {*l, *m, *r});
                    --r;
                    ++m;
                    while (*m == *(m - 1) && *r == *(r + 1) && m < r)   // 跳过m和r同时重复的元素 
                        ++m;
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<int> nums = {-1, 0, 1, 2, -1, -4};
    vector<vector<int>> ans = s.threeSum(nums);
    show2DVector(ans);
    return 1;
}