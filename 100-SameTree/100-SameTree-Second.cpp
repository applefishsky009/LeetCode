#include <queue>
#include <limits>
#include <vector>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// 递归
// time: O(min(m, n))
// space: O(min(m, n))
class Solution0 {
  public:
	bool isSameTree(TreeNode *p, TreeNode *q) {
		if (!p && !q) return true;
		if (!p || !q) return false;
		return p->val == q->val && isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
	}

};

// 迭代
// time: O(min(m, n))
// space: O(min(m, n))
class Solution {
  public:
	bool isSameTree(TreeNode *p, TreeNode *q) {
		if (!p && !q) return true;
		if (!p || !q) return false;
		queue<TreeNode*> ip, iq;
		ip.push(p); iq.push(q);
		while (!ip.empty() && !iq.empty()) {
			auto pnode = ip.front(), qnode = iq.front();
			ip.pop(); iq.pop();
			if (pnode->val != qnode->val) return false;
			auto pleft = pnode->left, pright = pnode->right, qleft = qnode->left, qright = qnode->right;
			if ((!pleft ^ !qleft) || (!pright ^ !qright)) return false;	// 异或
			if (pleft) ip.push(pleft);
			if (pright) ip.push(pright);
			if (qleft) iq.push(qleft);
			if (qright) iq.push(qright);
		}
		return ip.empty() && iq.empty();
	}
};

int main() {
	Solution s;
	vector<int> p0 = {1, 2, 3};
	vector<int> q0 = {1, 2, 3};	// 1
	vector<int> p1 = {1, 2};
	vector<int> q1 = {1, INT_MIN, 2};	// 0
	TreeNode *pTree0 = constructTree(p0);
	TreeNode *qTree0 = constructTree(q0);
	TreeNode *pTree1 = constructTree(p1);
	TreeNode *qTree1 = constructTree(q1);
	cout << s.isSameTree(pTree0, qTree0) << endl;
	cout << s.isSameTree(pTree1, qTree1) << endl;
	return 0;
}