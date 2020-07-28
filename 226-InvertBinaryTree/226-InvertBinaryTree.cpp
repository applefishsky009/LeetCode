#include <queue>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// DFS
// time: O(n)
// space: O(h)
class Solution1 {
  public:
    TreeNode* invertTree(TreeNode *root) {
        if (!root) return nullptr;
        TreeNode *l = root->left, *r = root->right;
        root->left = invertTree(r);
        root->right = invertTree(l);
        return root;
    }  
};

// Iteration
// time: O(n)
// space: O(1)
class Solution {
  public:
    TreeNode* invertTree(TreeNode *root) {
        if (!root) return nullptr;
        queue<TreeNode*> iq;
        iq.push(root);
        while (!iq.empty()) {
            TreeNode *tmp = iq.front();iq.pop();
            TreeNode *tmp_l = tmp->left;
            tmp->left = tmp->right;
            tmp->right = tmp_l;
            if (tmp->left) iq.push(tmp->left);
            if (tmp->right) iq.push(tmp->right);
        }
        return root;
    }
};

int main() {
    Solution s;
    TreeNode *root = constructTree(vector<int> {4, 2, 7, 1, 3, 6, 9});
    showTree(root);
    showTree(s.invertTree(root));
    return 0;
}