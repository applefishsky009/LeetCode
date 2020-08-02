#include <stack>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// 递归preOrder - 变种
// time: O(n)
// space: O(n)
class Solution1 {
  public:
	void flatten(TreeNode *root) {
		TreeNode *pre = new TreeNode(0);
		pre->left = root;
		preOrderTree(pre, root);
		root = pre->right;
	}
  private:
	void preOrderTree(TreeNode *&pre, TreeNode *root) {	// pre需要引用
		if (!root) return;
		TreeNode *left = root->left, *right = root->right;
		pre->left = nullptr;
		pre->right = root;
		pre = pre->right;
		preOrderTree(pre, left);
		preOrderTree(pre, right);
	}
};

// 迭代preOrder - 变种
// time: O(n)
// space: O(n)
class Solution2 {
  public:
	void flatten(TreeNode *root) {
		if (!root) return;
		stack<TreeNode*> istk;
		istk.push(root);
		TreeNode *pre = nullptr;
		while (!istk.empty()) {
			TreeNode *cur = istk.top(); istk.pop();
			if (pre != nullptr) {	// 新的连接关系
				pre->left = nullptr;
				pre->right = cur;
			}
			TreeNode *left = cur->left, *right = cur->right;
			if (right) istk.push(right);
			if (left) istk.push(left);	// 后进先出
			pre = cur;
		}
	}
};

// Morris遍历法 - 变种
// time: O(n)
// space: O(1)
class Solution {
  public:
	void flatten(TreeNode *root) {
		TreeNode *cur = root;
		while (cur) {
			if (cur->left) {	// 前驱存在
				auto next = cur->left;
				auto predecessor = next;	// 找前驱
				while (predecessor->right)
					predecessor = predecessor->right;
				predecessor->right = cur->right;	// 右子树接给前驱
				cur->left = nullptr;	// 左子树接给右子树
				cur->right = next;
			}
			cur = cur->right;	// 处理下一个节点
		}
	}
};

int main() {
	Solution s;
	TreeNode *root= constructTree(vector<int>{1, 2, 5, 3, 4, 6});
	showTree(root);
	s.flatten(root);
	showTree(root);
	return 0;
}