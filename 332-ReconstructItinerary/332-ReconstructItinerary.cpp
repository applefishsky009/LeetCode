#include <queue>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// Hierholzer算法 - 后序入栈问题 - 欧拉回路/欧拉通路问题
// 非死胡同一定会回到当前节点, 死胡同分支不会, 从后往前看, 只有当这个节点没边可走时才是当前的最后一步, 否则可走的边到达的点才是最后一步
// time: O(mlgm)
// space: O(m)
class Solution {
  public:
    vector<string> findItinerary(vector<vector<string>> &tickets) {
        vector<string> istk;
        unordered_map<string, priority_queue<string, vector<string>, greater<string>>> iumap;
        for (auto &it : tickets)
            iumap[it[0]].emplace(it[1]);
        dfs("JFK", istk, iumap);    // 从起点出发进行dfs
        reverse(istk.begin(), istk.end());
        return istk;
    }
  private:
    void dfs(const string &cur, vector<string> &istk, unordered_map<string, priority_queue<string, vector<string>, greater<string>>> &iumap) {
        while (iumap.count(cur) && iumap[cur].size() > 0) {
            string tmp = iumap[cur].top();
            iumap[cur].pop();   // 删除对应的边
            dfs(move(tmp), istk, iumap);    // 对非死胡同进行dfs
        }
        istk.emplace_back(cur); // 没有可移动路径, 入栈
    }
};

int main() {
    Solution s;
    // vector<vector<string>> tickets = {{"MUC", "LHR"}, {"JFK", "MUC"}, {"SFO", "SJC"}, {"LHR", "SFO"}};
    // vector<vector<string>> tickets = {{"JFK", "LHR"}, {"LHR", "JFK"}, {"JFK", "AAA"}};
    vector<vector<string>> tickets = {{"JFK", "SFO"}, {"JFK", "ATL"}, {"SFO", "ATL"}, {"ATL", "JFK"}, {"ATL", "SFO"}};
    show1DVector(s.findItinerary(tickets));
    return 0;
};