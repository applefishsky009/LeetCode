#include <vector>
#include <iostream>
#include <unordered_map>
#include <D:/GitHub/RylModule/vector.h>
using namespace std;

//对于任意一个连通图，我们总可以通过调整节点的删除顺序，把这个连通图中删到只剩下一个节点。且不关注删除顺序。
// time: O(n)
// space: O(n)
class Solution {
  private:
    void dfs(int x, vector<vector<int>> &edge, vector<int> &vis) {
        vis[x] = true;
        for (auto &y : edge[x]) {   // 继续扩展联通分量
            if (!vis[y]) {
                dfs(y, edge, vis);
            }
        }
    }
  public:
    int removeStones(vector<vector<int>>& stones) {
        int n = stones.size();
        vector<vector<int>> edge(n);
        unordered_map<int, vector<int>> rec;    // 存储石头行出现的idx
        for (int i = 0; i < n; ++i) {   // 构建联通图顶点
            rec[stones[i][0]].push_back(i);
            rec[stones[i][1] + 10000].push_back(i);
        }
        for (auto &[_, vec] : rec) {    // 匿名变量
            int k = vec.size();
            for (int i = 1; i < k; ++i) {   // 构建边
                edge[vec[i - 1]].push_back(vec[i]);
                edge[vec[i]].push_back(vec[i - 1]);
            }
        }
        vector<int> vis(n);
        int num = 0;
        for (int i = 0; i < n; ++i) {
            if (!vis[i]) {  // 保留这个石头, 以这个石头为起始点扩展联通分量
                num++;
                dfs(i, edge, vis);
            }
        }
        return n - num; // 总石头 - 保留的石头/联通分量个数
    }
};

int main() {
    Solution s;
    vector<vector<int>> stones = {{0, 0}, {0, 1}, {1, 0}, {1, 2}, {2, 1}, {2, 2}};  // 5
    // vector<vector<int>> stones = {{0, 0}, {0, 2}, {1, 1}, {2, 0}, {2, 2}};  //3
    cout << s.removeStones(stones) << endl;
    return 0;
}