#include <chrono>
#include <random>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

// 快排模板
class QuickSort {
  public:
    void randomQuickSort(vector<int> &g, int start, int end) {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(g.begin() + start, g.begin() + end - 1, default_random_engine(seed));
        quickSort(g, start, end);
    }
    void quickSort(vector<int> &g, int start, int end) {
        if (start < end) {
            int q = partition(g, start, end);
            quickSort(g, start, q - 1);
            quickSort(g, q + 1, end);
        }
    }
  private:
    int partition(vector<int> &g, int start, int end) {
        int j = start - 1;
        for (int i = start; i < end; ++i)
            if (g[i] < g[end])  // 从小到大排序
                swap(g[i], g[++j]);
        swap(g[++j], g[end]);
        return j;
    }
};

// 快排找第k大的数 - 因为重复的数不能计入k, 因此快排不能提前返回
// time: O(nlgn)
// time: O(1)
class Solution0 {
  public:
    int thirdMax(vector<int> &nums) {
        // QuickSort qs;
        // qs.randomQuickSort(nums, 0, nums.size() - 1);
        sort(nums.begin(), nums.end());
        int pre = INT_MIN, cnt = 0;
        vector<int> ans(3, INT_MIN);
        for (int i = nums.size() - 1; i >= 0; i--) {
            if (nums[i] != pre) {
                pre = nums[i];
                ans[cnt] = pre;
                if (++cnt == 3) 
                    return pre;
            }
        }
        return max(ans[0], max(ans[1], ans[2]));
    }
};

// 堆排
class HeapSort {
  public:
    HeapSort(vector<int> &h) : start(0), end(h.size() - 1), heapSize(h.size()), heapLength(h.size()) {};
    HeapSort(vector<int> &h, int s, int e) : start(s), end(e), heapSize(e - s + 1), heapLength(e - s + 1) {};
    void heapSort(vector<int> &g) {
        buildMaxHeap(g);
        for (int i = end; i >= start; i--) {
        // for (int i = end; i >= max(start, end - 3); i--) {
            swap(g[start], g[i]);
            --heapSize; // 更新的是有效长度
            maxHeapfify(g, start);
        }
    }
  private:
    int start;  // 起始点-闭区间
    int end;    // 起始点-闭区间
    int heapSize;   // 有效长度dd
    int heapLength; // 容量大小
    void maxHeapfify(vector<int> &g, int i) {
        int l = left(i), r = right(i), largest = i;
        if (l < start + heapSize && g[largest] < g[l])
            largest = l;
        if (r < start + heapSize && g[largest] < g[r])
            largest = r;
        if (largest != i) {
            swap(g[i], g[largest]);
            maxHeapfify(g, largest);    // 逐级下降
        }
    }
    void buildMaxHeap(vector<int> &g) { // O(n)
        for (int i = start + (heapLength >> 1) - 1; i >= start; --i)    // 初始化用容量
            maxHeapfify(g, i);
    }
    int left(int i) {return  ((i - start) << 1) + start + 1;};
    int right(int i) {return  ((i - start) << 1) + start + 2;};
};

// 堆排找第k大的数 - 因为重复的数不能计入k, 因此快排不能提前返回 同理堆排序也不能提前返回, 除非去重后使用堆排可达O(n)
// time: O(nlgn)
// time: O(1)
class Solution1 {
  public:
    int thirdMax(vector<int> &nums) {
        HeapSort hs(nums);
        hs.heapSort(nums);
        // sort(nums.begin(), nums.end());
        int pre = INT_MIN, cnt = 0;
        vector<int> ans(3, INT_MIN);
        for (int i = nums.size() - 1; i >= 0; i--) {
        // for (int i = nums.size() - 1; i >= max(0, (int)nums.size() - 3); i--) {
            if (nums[i] != pre) {
                pre = nums[i];
                ans[cnt] = pre;
                if (++cnt == 3) 
                    return pre;
            }
        }
        return max(ans[0], max(ans[1], ans[2]));
    }
};

// 堆排
class HeapSort {
  public:
    HeapSort(vector<int> &h) : start(0), end(h.size() - 1), heapSize(h.size()), heapLength(h.size()) {};
    HeapSort(vector<int> &h, int s, int e) : start(s), end(e), heapSize(e - s + 1), heapLength(e - s + 1) {};
    void heapSort(vector<int> &g) {
        buildMaxHeap(g);
        // for (int i = end; i >= start; i--) {
        for (int i = end; i >= max(start, end - 3); i--) {
            swap(g[start], g[i]);
            --heapSize; // 更新的是有效长度
            maxHeapfify(g, start);
        }
    }
  private:
    int start;  // 起始点-闭区间
    int end;    // 起始点-闭区间
    int heapSize;   // 有效长度dd
    int heapLength; // 容量大小
    void maxHeapfify(vector<int> &g, int i) {
        int l = left(i), r = right(i), largest = i;
        if (l < start + heapSize && g[largest] < g[l])
            largest = l;
        if (r < start + heapSize && g[largest] < g[r])
            largest = r;
        if (largest != i) {
            swap(g[i], g[largest]);
            maxHeapfify(g, largest);    // 逐级下降
        }
    }
    void buildMaxHeap(vector<int> &g) { // O(n)
        for (int i = start + (heapLength >> 1) - 1; i >= start; --i)    // 初始化用容量
            maxHeapfify(g, i);
    }
    int left(int i) {return  ((i - start) << 1) + start + 1;};
    int right(int i) {return  ((i - start) << 1) + start + 2;};
};

// 堆排去重优化
// time: O(n)
// time: O(n)
class Solution {
  public:
    int thirdMax(vector<int> &nums) {
        vector<int> num_cur;
        unordered_set<int> iuset;
        for (auto &x : nums) {  // 去重
            if (iuset.count(x) == 0) {
                iuset.emplace(x);
                num_cur.push_back(x);
            }
        }
        HeapSort hs(num_cur);
        hs.heapSort(num_cur);
        return num_cur.size() > 2 ? num_cur[num_cur.size() - 3] : num_cur[num_cur.size() - 1];
    }
};

// 直接维护三个变量
// time: O(n)
// time: O(1)
class Solution2 {
  public:
    int thirdMax(vector<int> &nums) {
        long long m1 = -3e9, m2 = -3e9, m3 = -3e9;
        for (auto &x : nums) {
            if (x == m1 || x == m2 || x == m3) continue;
            if (x > m1) {   // m1是最大的数, 全部一次更新
                m3 = m2;
                m2 = m1;
                m1 = x;
            } else if (x > m2) {    // m2是次大的数, 更新次大和第三大
                m3 = m2;
                m2 = x;
            } else if (x > m3) {    // m3是第三大, 直接更新第三大
                m3 = x;
            }
        }
        return m3 == -3e9 ? m1 : m3;
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {3, 2, 1};  // 1
    vector<int> nums1 = {1, 2}; // 2
    vector<int> nums2 = {2, 2, 3, 1};   // 1
    vector<int> nums3 = {1, 1, 1};   // 1
    cout << s.thirdMax(nums0) << endl;
    cout << s.thirdMax(nums1) << endl;
    cout << s.thirdMax(nums2) << endl;
    cout << s.thirdMax(nums3) << endl;
    return 0;
}