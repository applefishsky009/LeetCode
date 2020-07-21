#include <vector>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

class Solution {
  public:
    vector<TreeNode *> generateTrees(int n) {
        if (n == 0) return vector<TreeNode *>();
        return generateTrees(1, n + 1);
    }
  private:
    vector<TreeNode *> generateTrees(int start, int end) {
        if (start == end)
            return vector<TreeNode *> {nullptr};
        vector<TreeNode *> ans;
        for (int i = start; i < end; ++i) {
            vector<TreeNode *> left = generateTrees(start, i);
            vector<TreeNode *> right = generateTrees(i + 1, end);
            for (auto j : left) {
                for (auto k : right) {
                    TreeNode *tmp = new TreeNode(i);
                    tmp->left = j;
                    tmp->right = k;
                    ans.push_back(tmp);
                }
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    vector<TreeNode *> ans = s.generateTrees(3);
    for (auto &x : ans)
        showTree(x);
    return 0;
}

