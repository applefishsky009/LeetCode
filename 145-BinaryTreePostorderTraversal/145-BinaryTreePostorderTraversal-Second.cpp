#include <stack>
#include <vector>
#include <iostream>
#include <D:\Github\RylModule\tree.h>
#include <D:\Github\RylModule\vector.h>
using namespace std;

// 迭代
// time: O(n)
// space: O(n)
class Solution {
  public:
    vector<int> postorderTraversal(TreeNode *root) {
		vector<int> ans;
		TreeNode *pre = nullptr;
		stack<TreeNode *> istk;
		while (root || !istk.empty()) {
			while (root) {
				istk.emplace(root);
				root = root->left;	// 记录左孩子
			}
			root = istk.top(); istk.pop();
			if (!root->right || pre == root->right) {	// 没有右孩子 或 前一个节点是当前节点的右孩子
				ans.emplace_back(root->val);
				pre = root;
				root = nullptr;
			} else {	// 有右孩子 记录
				istk.emplace(root);
				root = root->right;	// 向右走一步 记录右孩子
			}
		}
		return ans;
    }
};

// 迭代
// time: O(n)
// space: O(n)
class Solution1 {
  public:
    vector<int> postorderTraversal(TreeNode *root) {
		vector<int> ans;
		if (!root) return ans;
		TreeNode *pre = nullptr;	// 指向前一个访问的节点
		stack<TreeNode *> istk;
		istk.emplace(root);
		while (!istk.empty()) {
			root = istk.top();	// pre == root->right从右孩子回溯, pre == root->left表示从左孩子回溯(右孩子为空)
			if ((!root->left && !root->right) || (pre && (pre == root->left || pre == root->right))) {	// 因为保证了右孩子先被访问, 
				ans.push_back(root->val);
				pre = root;
				istk.pop();
			} else {	// 保证了右孩子被记录
				if (root->right)	// 右孩子先入栈, 后访问
					istk.push(root->right);
				if (root->left)		// 左孩子后入栈, 先访问
					istk.push(root->left);
			}
		}
		return ans;
    }
};

// 递归
// time: O(n)
// space: O(n)
class Solution2 {
  public:
    vector<int> postorderTraversal(TreeNode *root) {
		vector<int> ans;
		postorderTraversal(root, ans);
		return ans;
    }
  private:
	void postorderTraversal(TreeNode *root, vector<int> &ans) {
		if (root == nullptr) return;
		postorderTraversal(root->left, ans);
		postorderTraversal(root->right, ans);
		ans.push_back(root->val); //postorderTraversal
	}
};

// Morris遍历
// time: O(n)
// space: O(1)
class Solution3 {
  public:
    vector<int> postorderTraversal(TreeNode *root) {
		vector<int> ans;
		if (!root) return ans;
		TreeNode *p1 = root, *p2 = nullptr;
		while (p1) {
			p2 = p1->left;
			if (p2) {
				while (p2->right && p2->right != p1)	// 找前驱
					p2 = p2->right;
				if (!p2->right) {	// 前驱为空
					p2->right = p1;
					p1 = p1->left;	// step forward
					continue;
				} else {	// 前驱不为空, 倒序输出
					p2->right = nullptr;
					addPath(ans, p1->left);
				}
			}
			p1 = p1->right;	// 访问右子节点
		}
		addPath(ans, root);
		return ans;
    }
  private:
	void addPath(vector<int> &ans, TreeNode *root) {
		vector<int> tmp;
		while (root) {
			tmp.emplace_back(root->val);
			root = root->right;
		}
		reverse(tmp.begin(), tmp.end());
		for (auto &x : tmp) {
			ans.emplace_back(x);
		}
	}
};

int main()
{
    TreeNode *root = constructTree(vector<int> () = {1, 2, 3});
    vector<int> outPostorderTraversal;
    Solution3 s1;
    outPostorderTraversal = s1.postorderTraversal(root);
	show1DVector(outPostorderTraversal);
    return 0;
}