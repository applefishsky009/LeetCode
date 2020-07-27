#include <algorithm>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// DFS
// time: O(n)
// space: O(h)
class Solution {
  public:
    int maxDepth(TreeNode *root) {
        return root ? max(maxDepth(root->left), maxDepth(root->right)) + 1 : 0;
    }  
};

int main() {
    Solution s;
    TreeNode *root = constructTree(vector<int> {3, 9, 20, INT_MIN, INT_MIN, 15, 7});
    cout << s.maxDepth(root) << endl;
    return 0;
}