#include <queue>
#include <limits>
#include <vector>
#include <unordered_map>
#include <D:\Github\RylModule\tree.h>
using namespace std;

// dfs
// time: O(n^2)
// space: O(n)
class Solution0 {
  public:
    vector<vector<int>> pathSum(TreeNode *root, int sum) {
        vector<int> path;
        vector<vector<int>> matrix;
        dfs(matrix, path, root, sum);
        return matrix;
    }
  private:
    void dfs(vector<vector<int>> &matrix, vector<int> &path, TreeNode *root, int sum) {
        if (!root) return;
        path.emplace_back(root->val);
        sum -= root->val;
        if (!root->left && !root->right && sum == 0) {
            matrix.push_back(vector<int> (path));
            // path.pop_back(); // 交给下一层去返回
            // return;
        }
        dfs(matrix, path, root->left, sum);
        // path.pop_back();
        dfs(matrix, path, root->right, sum);
        path.pop_back();
    }
};

// bfs
// time: O(n^2)
// space: O(n)
class Solution {
  public:
    vector<vector<int>> pathSum(TreeNode *root, int sum) {
        if (!root) return ans;
        queue<TreeNode *> iq_node;
        queue<int> iq_sum;
        iq_node.emplace(root);
        iq_sum.emplace(0);
        while (!iq_node.empty()) {
            TreeNode *node = iq_node.front(); iq_node.pop();
            int rec = iq_sum.front() + node->val; iq_sum.pop(); // 当前路径和
            if (!node->left && !node->right) {
                if (rec == sum)
                    getPath(node);
            } else {
                if (node->left) {
                    parent[node->left] = node;
                    iq_node.emplace(node->left);
                    iq_sum.emplace(rec);
                }
                if (node->right) {
                    parent[node->right] = node;
                    iq_node.emplace(node->right);
                    iq_sum.emplace(rec);
                }
            }
        }
        return ans;
    }
  private:
    vector<vector<int>> ans;
    unordered_map<TreeNode *, TreeNode *> parent;
    void getPath(TreeNode *node) {
        vector<int> cur;
        while (node != nullptr) {
            cur.emplace_back(node->val);
            node = parent[node];
        }
        reverse(cur.begin(), cur.end());
        ans.emplace_back(cur);
    }
};

int main() {
    TreeNode *root = constructTree(vector<int>() = {5, 4, 8, 11, INT_MIN, 13, 4, 7, 2, INT_MIN, INT_MIN, INT_MIN, INT_MIN, 5, 1});
    showTree(root);
    int sum = 22;
    Solution s1;
    vector<vector<int>> matrix = s1.pathSum(root, sum);
    cout << matrix.size() << endl;
    show2DVector(matrix);
    return 0;
}