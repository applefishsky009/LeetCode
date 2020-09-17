#include <vector>
#include <iostream>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// (按秩合)并(路径压缩)查集, 假设共m个makeSet, UnionRank, FindPath操作, 则:
// time: O(m)
// space: O(m)
class UnionFind {
  private:
    vector<int> nRank;
    vector<int> parent;
    void makeSet(int n) {   // 将自己初始化为集合代表
        parent.resize(n, 0);
        nRank.resize(n, 0);
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }
    void unionLink(int parentX, int parentY) {
        if (nRank[parentX] > nRank[parentY])    // parentX路径更长, 将parentY子树接在parentX树上, 秩不变
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
    void unionRank(int parentX, int parentY) { // 按秩合并, 无向图
        unionLink(findPath(parentX), findPath(parentY));    // 将集合代表连在一起, 非集合代表是不稳定的
    }
    int findPath(int n) {  // 路径压缩, 首次搜索进行路径更新, 再次搜索一次即可
        if (parent[n] != n)
            parent[n] = findPath(parent[n]);    // 等式右边沿路径向上查找, 等式左边沿搜索树向下更新节点
        return parent[n];
    }

    void unionR(int parentX, int parentY) { // 普通合并
        parent[findPath(parentX)] = findPath(parentY);
    }
    int find(int n) {   // 普通查找
        int r = n;
        while (parent[r] != r)
            r = parent[r];
        return r;
    }
};

// uf, 注意并查集中的parent只能代表集合关系, 不代表边关系, 边的连接关系可以用数组来做
// 对于边[u, v], 如果parent[v] != v, 表示v有两个父节点, [u, v]是导致冲突的边
// 否则, 令parent[v] = u, 找到并查集u和v的祖先, 如果祖先相同, 则一定会导致环, 如果不同, 连通分支u,v合并
// 访问结束后, 如果没有导致冲突出现的边, 说明附加的边一定导致环路出现, 返回环路中最后一条被访问的边
// 如果[u, v]导致冲突, 说明有两条边指向v, 需要选择一条附加边删除, 如果有环, 则当前边不可能是冲突边(冲突不能同时判定为有环), 选择[parent[v], v]删除
// 如果无环, 删除哪个都行, 附加边为最后访问到指向v的边, 即[u, v]
// time: O(nlgn)
// space: O(n)
class Solution {
  public:
    vector<int> findRedundantDirectedConnection(vector<vector<int>> &edges) {
        int nodeCount = edges.size();   // 节点为n的树有n-1条边
        UnionFind iuf(nodeCount + 1);   // 从1开始的并查集, 记录根节点
        auto parent = vector<int> (nodeCount + 1);
        for (int i = 1; i <= nodeCount; ++i)    // 记录父节点, 记录严格的边关系
            parent[i] = i;
        int conflict = -1, cycle = -1;
        for (int i = 0; i < nodeCount; ++i) {
            auto edge = edges[i];
            int node1 = edge[0], node2 = edge[1];
            if (parent[node2] != node2) {   // 父节点计算
                conflict = i;
            } else {    // 虽然是有向图, 但只需要计算其根节点的联通关系即可, 因此可使用路径压缩和按秩合并
                parent[node2] = node1;   // 父节点连接
                if (iuf.findPath(node1) == iuf.findPath(node2)) {   // 寻找根节点, 是否同一联通分量, 有环?
                    cycle = i;
                } else {    // 连通分量合并
                    iuf.unionRank(node1, node2);
                }
            }
        }
        if (conflict < 0) { // 没有冲突, 附加边一定导致有环
            auto redundant = vector<int> {edges[cycle][0], edges[cycle][1]};
            return redundant;
        } else {    // 一个节点有两个父节点, 冲突
            auto conflictEdge = edges[conflict];
            if (cycle >= 0) {   // 冲突且有环, 一定是之前的边, 因为当前边不可能同时被标记
                auto redundant = vector<int> {parent[conflictEdge[1]], conflictEdge[1]};
                return redundant;
            } else {    // 冲突且无环, 结果是当前边
                auto redundant = vector<int> {conflictEdge[0], conflictEdge[1]};
                return redundant;
            }
        }
    }
};

int main() {
    Solution s;
    vector<vector<int>> edges0 = {{1, 2}, {1, 3}, {2, 3}};
    vector<vector<int>> edges1 = {{1, 2}, {2, 3}, {3, 4}, {4, 1}, {1, 5}};
    show1DVector(s.findRedundantDirectedConnection(edges0));
    cout << ends << endl;
    show1DVector(s.findRedundantDirectedConnection(edges1));
    return 0;
}