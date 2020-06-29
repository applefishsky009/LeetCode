#include <set>
#include <map>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>
using namespace std;

// 二叉搜索树-红黑树
// time : n * log(n) 
// space: k
class Solution1 {
  public:
    int findKthLargest(vector<int>& nums, int k) {
        multiset<int> mset;
        for (auto &x : nums) {  // n
            mset.insert(x); // log(n)
            if (mset.size() > k)
                mset.erase(mset.begin());
        }
        return *(mset.begin());
    }
};

// 基于快排的选择方法
// time: O(n)
// space: O(1)
class Solution2 {
  public:
    int findKthLargest(vector<int>& nums, int k) {
        int l = 0, r = nums.size() - 1, q = 0;
        while (l < r) {
            q = randomPartition(nums, l, r);    // 从大到小的partition
            if (q == k - 1) return nums[q]; // 剪枝
            else if (q > k - 1) r = q - 1;
            else l = q + 1;
        }
        return nums[l];
    }
  private:
    int randomPartition(vector<int>& nums, int start, int end) {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(nums.begin() + start, nums.begin() + end, default_random_engine(seed));
        return partition(nums, start, end);
    }
    int partition(vector<int>& nums, int start, int end) {
        int i = start, j = start - 1;
        for (i = start; i < end; i++)
            // if (nums[i] <= nums[end])   // 快指针小, 交换-从小到大
            if (nums[i] > nums[end])
                swap(nums[i], nums[++j]);
        swap(nums[++j], nums[end]);
        return j;
    }
};

// 基于堆排序的选择方法
// time: O(n + klgn)
// space: O(lgn)-递归使用栈空间
class Solution {
  public:
    // 只对前k个进行堆排序
    int findKthLargest(vector<int>& nums, int k) {
        int heapSize = nums.size();
        buildMaxHeap(nums, heapSize);
        for (int i = 0; i < k; i++) {
            swap(nums[0], nums[heapSize - 1]);
            heapSize--;
            maxHeapify(nums, 0, heapSize);  // 逐级下降
        }
        return nums[heapSize];
    }
  private:
    // 建立堆 time: O(n)
    void buildMaxHeap(vector<int> &nums, int heapSize) {
        for (int i = (heapSize >> 1) - 1; i >= 0; i--)
            maxHeapify(nums, i, heapSize);
    }
    // 维护堆 time: O(logn)
    void maxHeapify(vector<int> &nums, int i, int heapSize) {
        int l = (i << 1) + 1, r = (i << 1) + 2, largest = i;
        if (l < heapSize && nums[l] > nums[largest])    // 必须为largest不能为i,因为可能会更新
            largest = l;
        if (r < heapSize && nums[r] > nums[largest])
            largest = r;
        if (largest != i) {
            swap(nums[i], nums[largest]);
            maxHeapify(nums, largest, heapSize);    // 逐级下降
        }
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {3, 2, 1, 5, 6, 4};
    vector<int> nums1 = {3, 2, 3, 1, 2, 4, 5, 5, 6};
    cout << s.findKthLargest(nums0, 2) << endl;
    cout << s.findKthLargest(nums1, 4) << endl;
    return 1;
}