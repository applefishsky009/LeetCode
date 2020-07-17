#include <queue>
#include <vector>
#include <iostream>
using namespace std;

// DFS
// time: O(n + m)   n为点m为边
// space: O(n)
class Solution1 {
  public:
    bool isBipartite(vector<vector<int>> &graph) {
        int len = graph.size();
        vector<int> color(len, 0);  // 0 未染色 1 奇书步色红色 2 偶数步色绿色
        for (int i = 0; i < len; i++)
            if (color[i] == 0 && !dfsColor(graph, i, 1, color))
                return false;
        return true;
    }
  private:
    bool dfsColor(vector<vector<int>> &graph, int start, int step, vector<int> &color) {
        int color_now = step & 1 ? 1 : 2;   // 染色
        for (int i = 0; i < graph[start].size(); i++) {
            if (color[graph[start][i]] == 0) {
                color[graph[start][i]] = color_now;
                if (!dfsColor(graph, graph[start][i], step + 1, color)) // dfs
                    return false;
            }
            else if (color[graph[start][i]] != color_now)   // 不能染色
                return false;
        }
        return true;    // 正常染色
    }
};

// BFS
// time: O(n + m)   n为点m为边
// space: O(n)
class Solution2 {
  public:
    bool isBipartite(vector<vector<int>> &graph) {
        int len = graph.size();
        vector<int> color(len, 0);
        for (int i = 0; i < len; ++i) {
            if (color[i] != 0) continue;
            queue<int> iq; iq.push(i);
            color[i] = 2;
            while (!iq.empty()) {
                int tmp = iq.front(); iq.pop();
                int color_next = color[tmp] == 2 ? 1 : 2;   // 染色
                for (int j = 0; j < graph[tmp].size(); ++j) {
                    if (color[graph[tmp][j]] == 0) {    // 没有染过色, 记录步骤
                        color[graph[tmp][j]] = color_next;
                        iq.push(graph[tmp][j]);
                    }
                    else if (color[graph[tmp][j]] != color_next)    // 染色不对
                        return false;
                }
            }
        }
        return true;
    }
};

// (按秩合)并(路径压缩)查集
class UnionFind {
  private:
    vector<int> parent;
    vector<int> nRank;
    void makeSet(int n) {   // 将自己初始化为集合代表
        parent.resize(n, 0);
        nRank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    void unionLink(int parentX, int parentY) {
        if (nRank[parentX] > nRank[parentY])    // parentX路径更长,将parentY子树接在parentX树上,秩不变
            parent[parentY] = parentX;
        else {
            parent[parentX] = parentY;  // 将parentX子树接在parentY树上
            if (nRank[parentX] == nRank[parentY])   // 等秩,从parentX子树搜索必然会有parentY秩增加
                ++nRank[parentY];
        }
    }

  public:
    UnionFind(int n) {
        makeSet(n);
    }
    void unionRank(int parentX, int parentY) { // 按秩合并
        unionLink(findPath(parentX), findPath(parentY));    // 将集合代表连在一起,非集合代表是不稳定的
    }
    int findPath(int n) {  // 路径压缩,首次搜索进行路径更新,再次搜索一次即可
        if (parent[n] != n)
            parent[n] = findPath(parent[n]);    // 等式右边沿路径向上查找,等式左边沿搜索树向下更新节点
        return parent[n];
    }

    void unionR(int parentX, int parentY) { // 普通合并
        parent[parentX] = parentY;
    }
    int find(int n) {
        int r = n;
        while (parent[r] != r)
            r = parent[r];
        return r;
    }
};

// UF - 合并对手, 只要和对手不在一个颜色即可
// time: O(n + m)   n为点m为边
// space: O(n)
class Solution {
  public:
    bool isBipartite(vector<vector<int>> &graph) {
        int len = graph.size();
        vector<int> color(len, 0);
        UnionFind iuf(len);
        for (int i = 0; i < len; ++i) {
            if (graph[i].empty()) continue;
            int color = iuf.findPath(i);
            int color_next = iuf.findPath(graph[i][0]);
            if (color_next == color) return false;
            for (int j = 1; j < graph[i].size(); ++j) {
                color_next = iuf.findPath(graph[i][j]);
                if (color_next == color)
                    return false;
                iuf.unionRank(graph[i][0], graph[i][j]);
            }
        }
        return true;
    }
};

int main() {
    Solution s;
    vector<vector<int>> nums0 = {{1, 3}, {0, 2}, {1, 3}, {0, 2}};
    vector<vector<int>> nums1 = {{1, 2, 3}, {0, 2}, {0, 1, 3}, {0, 2}};
    cout << s.isBipartite(nums0) << endl;
    cout << s.isBipartite(nums1) << endl;
    return 0;
}
