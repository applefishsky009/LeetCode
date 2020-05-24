#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

class Solution2 {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int i = 0, j = 0, g_size = g.size(), s_size = s.size();
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        while (i < g_size && j < s_size) {
            if (s[j] >= g[i]) // 找到饼干, 分配下一个孩子
                i++;
            j++;    // 下一个饼干
        }
        return i;
    }
};

// 快排自己实现
class Solution {
  public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int i = 0, j = 0, g_size = g.size(), s_size = s.size();
        quickSort(g, 0, g_size - 1);
        quickSort(s, 0, s_size - 1);
        while (i < g_size && j < s_size) {
            if (s[j] >= g[i]) // 找到饼干, 分配下一个孩子
                i++;
            j++;    // 下一个饼干
        }
        return i;
    }
  private:
    void quickSort(vector<int>& g, int start, int end) {
        int q = 0;
        if (start < end) {
            q = partition(g, start, end);
            quickSort(g, start, q - 1);
            quickSort(g, q + 1, end);
        }
    }
    int partition(vector<int>& g, int start, int end) {
        int i = start, j = start - 1;   // i快指针,j慢指针,[...,j]表示均小于g[end], [j+1, end - 1]均表示大于等于g[end]
        for (i = start; i < end; i++)
            if (g[i] <= g[end])
                swap(g[i], g[++j]);
        swap(g[++j], g[end]);
        return j;
    }
};

class Solution1 {
public:
    int findContentChildren(vector<int>& g, vector<int>& s) {
        int i = 0, j = 0, cnt = 0, g_size = g.size(), s_size = s.size();
        sort(g.begin(), g.end());
        sort(s.begin(), s.end());
        while (i < g_size) {
            while (j < s_size && s[j++] >= g[i]) {
                cnt++;
                break;
            }
            i++;
        }
        return cnt;
    }
};

int main() {
    Solution s1;
    // vector<int> g = {1, 2, 3}; // children
    // vector<int> s = {1, 1};  // cookies
    vector<int> g = {10, 9, 8, 7}; // children
    vector<int> s = {5, 6, 7, 8};  // cookies
    cout << s1.findContentChildren(g, s) <<endl;
    return 1;
}