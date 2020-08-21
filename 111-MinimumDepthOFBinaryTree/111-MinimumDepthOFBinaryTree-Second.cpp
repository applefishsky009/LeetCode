#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// 递归-注意这道题是到叶子结点, 有孩子的节点不算
// time: O(n)
// space: O(h)
class Solution0 {
  public:
    int minDepth(TreeNode *root) {
        if (!root) return 0;    // 根节点的空孩子, 单独处理
        return minDepthP(root);
    }
  private:
    int minDepthP(TreeNode *root) {
        if (!root) return INT_MAX;  // 非叶子节点的空孩子, 返回奇异值, 必然不参与下次计算
        if (!root->left && !root->right) return 1;  // 叶子结点, 返回
        return min(minDepthP(root->left), minDepthP(root->right)) + 1;  // 非叶子节点不为空, 递归
    }
};

// 迭代
// time: O(n)
// space: O(h)
class Solution {
  public:
    int minDepth(TreeNode *root) {
        if (!root) return 0;    // 根节点的空孩子, 单独处理
        queue<pair<TreeNode*, int>> iq;
		iq.emplace(root, 1);
		while (!iq.empty()) {
			TreeNode *node = iq.front().first;
			int depth = iq.front().second;
			iq.pop();
			if (!node->left && !node->right) return depth;
			if (node->left) iq.emplace(node->left, depth + 1);
			if (node->right) iq.emplace(node->right, depth + 1);
		}
		return 0;
    }
};

int main() {
    Solution s;
    // vector<int> nums0 = {3, 9, 20, INT_MIN, INT_MIN, 15, 7};
    vector<int> nums0 = {1, 2};
    TreeNode *root = constructTree(nums0);
    cout << s.minDepth(root) << endl;
    return 0;
}