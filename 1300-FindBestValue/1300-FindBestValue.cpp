#include <cmath>
#include <vector>
#include <chrono>
#include <random>
#include <iostream>
#include <algorithm>
using namespace std;

class QuickSort {
  public:
    void quickSort(vector<int> &g, int start, int end) {
        int q = 0;
        if (start < end) {
            q = partition(g, start, end);
            quickSort(g, start, q - 1);
            quickSort(g, q + 1, end);
        }
    }
    void randomizedQuickSort(vector<int> &g, int start, int end) {
        int q = 0;
        if (start < end) {
            q = randomizedPartition(g, start, end);
            randomizedQuickSort(g, start, q - 1);
            randomizedQuickSort(g, q + 1, end);
        }
    }
  private:
    int partition(vector<int> &g, int start, int end) {
        int i = start, j = start - 1;
        for (i = start; i < end; i++)
            if (g[i] <= g[end]) // 快指针小, 交换
                swap(g[i], g[++j]);
        swap(g[++j], g[end]);
        return j;
    }
    int randomizedPartition(vector<int> &g, int start, int end) {
        int dice_roll = 0;
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine generator(seed);
        uniform_int_distribution<int> distribution(start, end);
        dice_roll = distribution(generator);
        swap(g[dice_roll], g[end]);
        return partition(g, start, end);
    }
};

class Solution {
  public:
    int findBestValue(vector<int>& arr, int target) {
        int n = arr.size(), i = 0;
        // sort(arr.begin(), arr.end());
        QuickSort qs;
        qs.randomizedQuickSort(arr, 0, n - 1);
        int l = 0, r = arr[n - 1], ans = -1;    // 记录值而不是下标
        vector<int> prefix(n + 1, 0);
        for (i = 1; i < n; i++) // 前缀和,注意大小多一个
            prefix[i] = prefix[i - 1] + arr[i - 1];
        while (l <= r) {    // 二分查找, 闭区间模板
            int m = (l + r) / 2;    // 向下取整, 二分要确保m在l,r之间,分母不为2会有问题
            auto iter = lower_bound(arr.begin(), arr.end(), m); // 超尾
            int cur = prefix[iter - arr.begin()] + (arr.end() - iter) * m;  // 和
            if (cur <= target) {
                ans = m;    // 查找不大于target的第一个值
                l = m + 1;  // 避免死循环,向上收缩
            }
            else 
                r = m - 1;
        }
        int choose_small = check(arr, ans);
        int choose_big = check(arr, ans + 1);
        return abs(choose_small - target) <= abs(choose_big - target) ? ans : ans + 1;  // 相等返回更小值
    }
  private:
    int check(vector<int> &arr, int x) {
        int ret = 0;
        for (const int &num : arr)
            ret += (num > x ? x : num);
        return ret;
    }
};

int main() {
    Solution s;
    vector<int> arr0 = {4, 9, 3};
    vector<int> arr1 = {2, 3, 5};
    vector<int> arr2 = {60864, 25176, 27249, 21296, 20204};
    cout << s.findBestValue(arr0, 10) << endl;
    cout << s.findBestValue(arr1, 10) << endl;
    cout << s.findBestValue(arr2, 56803) << endl;
    return 1;
}