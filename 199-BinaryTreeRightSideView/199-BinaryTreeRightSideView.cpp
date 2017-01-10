#include <queue>
#include <utility>
#include <iostream>
#include <E:\RylModule\tree.h>
using namespace std;

class Solution
{
  public:
    vector<int> rightSideView(TreeNode *root)
    {
        if (!root)
            return vector<int>() = {};
        vector<int> ans;
        queue<pair<TreeNode *, int>> q;
        q.push(make_pair(root, 1));
        int curStep;
        TreeNode *curNode;
        while (!q.empty()) //notion how the last val push_back to vector.
        {
            curNode = q.front().first;
            curStep = q.front().second;
            if (curNode->left)
                q.push(make_pair(curNode->left, curStep + 1));
            if (curNode->right)
                q.push(make_pair(curNode->right, curStep + 1));
            q.pop();
            if (!q.empty() && q.front().second != curStep)
                ans.push_back(curNode->val);
        }
        ans.push_back(curNode->val);
        return ans;
    }
};

int main()
{
    Solution s1;
    vector<int> tree = {1, -1, 3, -1, -1, 2, 5, -1, -1, -1, -1, -1, -1, 4}; //1,3,4,6
    TreeNode *root = constructTree(tree);
    showTree(root);
    vector<int> ans = s1.rightSideView(root);
    show1DVector(ans);
    return 0;
}