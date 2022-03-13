#include <string>
#include <vector>
#include <chrono>
#include <random>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

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
        int i = start,  j = start - 1;
        for (i = start; i < end; ++i)
            if (g[i] >= g[end])
                swap(g[i], g[++j]);
        swap(g[++j], g[end]);
        return j;
    }
};


// time: nlg(n)
// space: O(n)
class Solution {
public:
    vector<string> findRelativeRanks(vector<int> &score) {
        QuickSort qs;
        vector<int> score_bf(score);
        qs.quickSort(score_bf, 0, score_bf.size() - 1);
        unordered_map<int, string> umap;    // 可以用pair来优化
        vector<string> ans(score_bf.size(), "");
        for (int i = 0; i < score_bf.size(); ++i) {
            if (i == 0) {   // 三种情况可以列表优化
                umap[score_bf[i]] = "Gold Medal";
            } else if (i == 1) {
                umap[score_bf[i]] = "Silver Medal";
            } else if (i == 2) {
                umap[score_bf[i]] = "Bronze Medal";
            } else {
                umap[score_bf[i]] = to_string(i + 1);
            }
        }
        for (int i = 0; i < score.size(); ++i) {
            ans[i] = umap[score[i]];
        }
        return ans;
    }
};

class Solution1 {
public:
    vector<string> findRelativeRanks(vector<int>& score) {
        int n = score.size();
        string desc[3] = {"Gold Medal", "Silver Medal", "Bronze Medal"};
        vector<pair<int, int>> arr;

        for (int i = 0; i < n; ++i) {
            arr.emplace_back(make_pair(-score[i], i));
        }
        sort(arr.begin(), arr.end());
        vector<string> ans(n);
        for (int i = 0; i < n; ++i) {
            if (i >= 3) {
                ans[arr[i].second] = to_string(i + 1);
            } else {
                ans[arr[i].second] = desc[i];
            }
        }
        return ans;
    }
};

int main() {
    Solution s1;
    vector<int> score = {10, 3, 8, 9, 4};
    // vector<int> score = {5, 4, 3, 2, 1};
    auto ans = s1.findRelativeRanks(score);
    for (auto &sc : ans) {
        cout << sc << endl;
    }
    return 0;
}