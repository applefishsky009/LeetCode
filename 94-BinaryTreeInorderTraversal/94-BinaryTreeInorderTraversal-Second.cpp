#include <stack>
#include <vector>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// dfs
// time: O(n)
// space: O(n)
class Solution0 {
  public:
	vector<int> inorderTraversal(TreeNode *root) {
		vector<int> ans;
		dfs(root, ans);
		return ans;
	}
  private:
	void dfs(TreeNode *root, vector<int> &ans) {
		if (!root) return;
		if (root->left) dfs(root->left, ans);
		ans.emplace_back(root->val);
		if (root->right) dfs(root->right, ans);
	}
};

// 迭代
// time: O(n)
// space: O(n)
class Solution1 {
  public:
	vector<int> inorderTraversal(TreeNode *root) {
		vector<int> ans;
		stack<TreeNode *> istk;
		while (root || !istk.empty()) {
			while(root) {
				istk.emplace(root);
				root = root->left;
			}
			if (!istk.empty()) {
				root = istk.top(); istk.pop();
				ans.emplace_back(root->val);
				root = root->right;
			}
		}
		return ans;
	}
};

// Morris中序遍历
// time: O(n)
// space: O(1)
class Solution {
  public:
	vector<int> inorderTraversal(TreeNode *root) {
		vector<int> ans;
		TreeNode *predecessor = nullptr;
		while (root) {
			if (root->left) {	// 有左孩子找后继
				predecessor = root->left;
				while (predecessor->right && predecessor->right != root)	// 找后继
					predecessor = predecessor->right;
				if (predecessor->right == nullptr) {	// 左子树没有被遍历, 预处理后继连接关系, 继续遍历左子树
					predecessor->right = root;
					root = root->left;
				} else {	// 左子树遍历完成, 恢复连接关系
					ans.push_back(root->val);	// 中序遍历的操作, 可被替换
					predecessor->right = nullptr;
					root = root->right;
				}
			} else {	// 没有左孩子, 直接访问右孩子
				ans.push_back(root->val);	// 中序遍历的操作, 可被替换
				root = root->right;
			}
		}
		return ans;
	}
};

int main() {
	Solution s;
	vector<int> nums0 = {1, INT_MIN, 2, INT_MIN, INT_MIN, 3};
	TreeNode *root0 = constructTree(nums0);
	show1DVector(s.inorderTraversal(root0));
	return 0;
}