#include <queue>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// 堆
// time: (N*lgK)
// space: (N)
class Solution0 {
  public:
    vector<int> topKFrequent(vector<int> &nums, int k) {
        unordered_map<int, int> occurrences;
        for (auto &v : nums) ++occurrences[v];
        priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(&cmp)> ipq(cmp);
        for (auto &[num, count] : occurrences) {
            if (ipq.size() == k) {
                if (ipq.top().second < count) {
                    ipq.pop();
                    ipq.emplace(num, count);
                }
            } else {
                ipq.emplace(num, count);
            }
        }
        vector<int> ans;
        while (!ipq.empty()) {
            ans.emplace_back(ipq.top().first);
            ipq.pop();
        }
        return ans;
    }
  private:
    static bool cmp(pair<int, int> &m, pair<int, int> &n) { // 默认的less<T>是大顶堆, 可以理解为如果cmp为true则需要heapify
        return m.second > n.second; // 小顶堆, 右侧为堆顶
    }
};

// 基于快排
// time: O(N)
// space: O(N)
class Solution {
  public:
    vector<int> topKFrequent(vector<int> &nums, int k) {
        unordered_map<int, int> occurrences;
        for (auto &v : nums) ++occurrences[v];
        vector<pair<int, int>> values;
        for (auto &kv : occurrences) values.push_back(kv);
        vector<int> ans;
        randomizeQuickSort(values, 0, values.size() - 1, ans, k);
        return ans;
    }
  private:
    void randomizeQuickSort(vector<pair<int, int>> &v, int start, int end, vector<int> &ans, int k) {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(v.begin() + start, v.begin() + end, default_random_engine(seed));
        quickSort(v, start, end, ans, k);
    }
    void quickSort(vector<pair<int, int>> &v, int start, int end, vector<int> &ans, int k) {
        if (start <= end) { // 纯粹的快排是小于, 因为等于不需要排序, 但这里需要考虑start = end时找目标的问题, 需要等于
            int index = partition(v, start, end);
            if (index - start >= k) // 比k个多, 继续分治
                quickSort(v, start, index - 1, ans, k);
            else {  // 比k个少, [start, index]必然是目标
                for (int i = start; i <= index; ++i)
                    ans.push_back(v[i].first);
                if (k > index - start + 1)  // 在右侧找剩下的元素
                    quickSort(v, index + 1, end, ans, k - (index - start + 1));
            }
        }
    }
    int partition(vector<pair<int, int>> &v, int start, int end) {
        int i = start, j = start - 1;
        for (int i = start; i < end; ++i)
            if (v[i].second >= v[end].second)    // 将大值放在该放的位置上
                swap(v[i], v[++j]);
        swap(v[++j], v[end]);
        return j;
    }
};

int main() {
    Solution s;
    // vector<int> nums0 = {1, 1, 1, 2, 2, 3};
    // show1DVector(s.topKFrequent(nums0, 2));
    vector<int> nums1 = {1};
    show1DVector(s.topKFrequent(nums1, 1));
    return 0;
}