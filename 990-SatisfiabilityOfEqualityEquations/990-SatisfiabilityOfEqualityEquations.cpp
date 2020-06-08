#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
using namespace std;

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
};

class Solution {
  public:
    bool equationsPossible(vector<string>& equation) {
        UnionFind uf(26);
        char left, right;
        for (auto &x : equation)
            if (x[1] == '=')
                uf.unionRank(x[0] - 'a', x[3] - 'a');
        for (auto &x : equation)
            if (x[1] == '!')
                if (uf.findPath(x[0] - 'a') == uf.findPath(x[3] - 'a'))
                    return false;
        return true;
    }
};

int main() {
    Solution s;
    // vector<string> input = {"a==b","b!=a"};
    vector<string> input = {"f==a", "a==b", "f!=e", "a==c", "b==e", "c==f"};
    cout << s.equationsPossible(input) << endl;
    return 1;
}