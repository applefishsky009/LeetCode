#include <stack>
#include <limits>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// 显式中序遍历
// time: O(n)
// space: O(n)
class Solution0 {
  public:
	void recoverTree(TreeNode *root) {
		vector<TreeNode *> ordered_num;
		inorderTree(root, ordered_num);
		TreeNode *ip = nullptr, *iq = nullptr;
		for (int i = 0; i < ordered_num.size(); ++i) {
			int pre = i - 1 < 0 ? INT_MIN : ordered_num[i - 1]->val;	// 前
			int cur = ordered_num[i]->val;	// 后
			int post = i + 1 >= ordered_num.size() ? INT_MAX : ordered_num[i + 1]->val;
			if (!ip && cur > pre && cur > post)	// 找peek, 最先出现一定是目标, 可能由于bottom产生第二个bottom
				ip = ordered_num[i];
			if (cur < pre && cur < post)	// 找bottom, 最后出现的一定是目标, 可能由于peek会产生第一个伪bottom
				iq = ordered_num[i++];
		}
		swap(ip->val, iq->val);
	}
  private:
	void inorderTree(TreeNode *root, vector<TreeNode *> &nums) {
		if (!root) return;
		inorderTree(root->left, nums);
		nums.push_back(root);
		inorderTree(root->right, nums);
	}
};

// 隐式中序遍历
// time: O(n)
// space: O(n)
class Solution1 {
  public:
	void recoverTree(TreeNode *root) {
		stack<TreeNode *> istk;
		TreeNode *x = nullptr, *y = nullptr, *pred = nullptr;
		while (!istk.empty() || root != nullptr) {
			while (root != nullptr) {	// root存在前驱, 先访问前驱
				istk.push(root);
				root = root->left;
			}
			root = istk.top(); istk.pop();
			if (pred != nullptr && root->val < pred->val) {	// 下降, 第一个异常点
				y = root;	// y记录第一->第二个异常点
				if (x == nullptr) x = pred;	// x记录第一个异常点
				else break;	// 第一个异常点已经记录过, 跳出
			}
			pred = root;
			root = root->right;	// 尝试向右访问
		}
		swap(x->val, y->val);
	}
};

// Morris中序遍历
// time: O(n)
// space: O(1)
class Solution {
  public:
	void recoverTree(TreeNode *root) {
		TreeNode *x = nullptr, *y = nullptr, *pred = nullptr, *predecessor = nullptr;
		while (root) {
			if (root->left) {	// 说明前驱存在, 访问左孩子
				predecessor = root->left;
				while (predecessor->right && predecessor->right != root)	// 前驱存在且没有指向当前节点
					predecessor = predecessor->right;
				if (!predecessor->right) {	// 前驱指向当前节点
					predecessor->right = root;
					root = root->left;	// 遍历左子树, 前序
				} else { // 左子树已经遍历过了, 这里是中序了
					if (pred && root->val < pred->val) {
						y = root;	// y记录第一->最后一个异常点
						if (!x) x = pred;	// x记录第一个异常点
					}
					pred = root;	// 记录前驱
					predecessor->right = nullptr;
					root = root->right;	// 后序
				}
			} else { // 如果没有左孩子, 直接访问右孩子
				if (pred && root->val < pred->val) {
					y = root;
					if (!x) x = pred;
				}
				pred = root;
				root = root->right;
			}
		}
		swap(x->val, y->val);
	}
};

int main() {
	Solution s;
	// vector<int> nums0 = {1, 3, INT_MIN, INT_MIN, 2};
	// vector<int> nums0 = {146, 71, -13, 55, INT_MIN, 231, 399, 321, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, -33};
	vector<int> nums0 = {3, 1, 4, INT_MIN, INT_MIN, 2};
	TreeNode *root = constructTree(nums0);
	showTree(root);
	s.recoverTree(root);
	showTree(root);
	return 0;
}