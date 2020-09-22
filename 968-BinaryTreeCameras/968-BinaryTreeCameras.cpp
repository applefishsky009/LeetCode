#include <vector>
#include <limits>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// dfs + status(和dp思路有点像)
// https://leetcode.com/problems/binary-tree-cameras/discuss/211180/JavaC%2B%2BPython-Greedy-DFS
// 状态a: root放置了摄像头, 覆盖整棵树所需要的摄像头数目, 树本身被覆盖完全且根节点有摄像头
// 状态b: 覆盖整棵树需要的摄像头数目, 无论root是否放置摄像头, 树本身是被覆盖完全的
// 状态c: 覆盖两颗子树需要的摄像头数目, 无论root本身是否被监控到, 子树被覆盖完全
// time: O(n)
// space: O(n)
class Solution {
  public:
    struct Status {
        int a, b, c;    // a >= b >= c has camera | not needed | no camera
    };
    int minCameraCover(TreeNode *root) {
        auto [a, b, c] = dfs(root); // a因为root一定有摄像头, 可能有多余摄像头, c因为不考虑root的覆盖性, 可能少摄像头
        return b;
    }
  private:
    Status dfs(TreeNode *root) {
        if (!root) return {INT_MAX / 2, 0, 0};  // 表示不可能放置摄像头, 一定会被min去掉
        auto [la, lb, lc] = dfs(root->left);    // lc表示不管root->left(没有摄像头), 只覆盖其子树
        auto [ra, rb, rc] = dfs(root->right);   // rb表示覆盖整棵子树所需的摄像头数目, root可能监控或不监控
        int a = lc + rc + 1;    // 在root放置摄像头, 保证完全覆盖, 如果c是a得来, 就有浪费, 如果c是lb和rb得来, root刚好覆盖了自身和左右孩子
        int b = min(a, min(la + rb, ra + lb));  // 在root放置摄像头, 或root不放置, root的监控在左孩子或右孩子处, 确保恰好覆盖
        int c = min(a, lb + rb);    // 在root放置摄像头保证子树被覆盖, 或root没有摄像头, 确保子树被覆盖
        return {a, b, c};
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {0, 0, INT_MIN, 0, 0};
    TreeNode *root = constructTree(nums0);
    cout << s.minCameraCover(root) << endl;
    return 0;
}