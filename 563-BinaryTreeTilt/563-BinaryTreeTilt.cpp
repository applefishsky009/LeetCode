#include <vector>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// DFS
// time: O(n)
// space: O(n)
class Solution {
  public:
    int findTilt(TreeNode *root) {
        int tilt = 0;   // 全局变量保存坡度
        traverse(root, tilt);
        return tilt;
    }
  private:
    int traverse(TreeNode *root, int &tilt) {   // 函数返回值保存子树和
        if (!root) return 0;
        int left = traverse(root->left, tilt);
        int right = traverse(root->right, tilt);
        tilt += abs(left - right);
        return left + right + root->val;
    }
};

int main() {
    Solution s;
    // TreeNode *root = constructTree(vector<int>() = {1, 2, 3});
    TreeNode *root = constructTree(vector<int>() = {4, 2, 9, 3, 5, INT_MIN, 7});
    cout << s.findTilt(root) << endl;
    return 0;
}
