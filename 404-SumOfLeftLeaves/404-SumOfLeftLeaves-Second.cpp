#include <queue>
#include <vector>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// dfs
// time: O(n)
// space: O(h)
class Solution0 {
  public:
    int sumOfLeftLeaves(TreeNode *root) {
		int ans = 0;
		dfs(root, nullptr, ans);
		return ans;
    }
  private:
	void dfs(TreeNode *root, TreeNode *parent, int &ans) {
		if (!root) return;
		if (parent && parent->left == root && !root->left && !root->right)
		ans += root->val;
		dfs(root->left, root, ans);
		dfs(root->right, root, ans);
	}
};

// bfs
// time: O(n)
// space: O(h)
class Solution1 {
  public:
    int sumOfLeftLeaves(TreeNode *root) {
		int ans = 0;
		if (!root) return ans;
		queue<pair<TreeNode *, TreeNode *>> iq;
		iq.emplace(pair<TreeNode *, TreeNode *> (root, nullptr));
		while(!iq.empty()) {
			auto cur = iq.front(); iq.pop();
			if (cur.second && cur.second->left == cur.first && !cur.first->left && !cur.first->right)
				ans += cur.first->val;
			if (cur.first->left) iq.push(pair<TreeNode *, TreeNode *>(cur.first->left, cur.first));
			if (cur.first->right) iq.push(pair<TreeNode *, TreeNode *>(cur.first->right, cur.first));
		}
		return ans;
    }
};

// bfs
// time: O(n)
// space: O(h)
class Solution {
  public:
    int sumOfLeftLeaves(TreeNode *root) {
		int ans = 0;
		if (!root) return ans;
		queue<TreeNode *> iq;
		iq.emplace(root);
		while(!iq.empty()) {
			auto cur = iq.front(); iq.pop();
			if (cur->left) {
				if (!cur->left->left && !cur->left->right) ans += cur->left->val;	// 左叶子
				else iq.push(cur->left);
			}
			if (cur->right && !(!cur->right->left && !cur->right->right)) iq.push(cur->right);	// 不是右叶子
		}
		return ans;
    }
};

int main() {
    Solution s;
    vector<int> nums = {3, 9, 20, INT_MIN, INT_MIN, 15, 7};	// 24
    // vector<int> nums = {1, INT_MIN, 2};	// 0
    TreeNode *root = constructTree(nums);
    cout << s.sumOfLeftLeaves(root) << endl;
    return 0;
}