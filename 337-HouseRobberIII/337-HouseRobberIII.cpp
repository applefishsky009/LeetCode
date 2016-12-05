#include <vector>
#include <iostream>
#include <unordered_map>
#include <E:\RylModule\tree.h>
using namespace std;

//简单递归，还是DP的思路，如果不选当前，从深度+1层开始打劫，如果选择当前，只能深度+2的层开始打劫'
//即当前状态与前两个状态相关：f[h] = max(f[h-1],val+f[h-2]);
//不必考虑h+2层的根节点到底选了没选，就算没有选，h+3也一定有一个选了，否则就选了根节点。
class Solution
{
  public:
    int rob(TreeNode *root)
    {
        unordered_map<TreeNode *, int> map;
        if (!root)
            return 0;
        int val = 0;
        if (root->left)
            val += rob(root->left->left) + rob(root->left->right);
        if (root->right)
            val += rob(root->right->left) + rob(root->right->right);
        return max(root->val + val, rob(root->left) + rob(root->right));
    }
};

//加了哈希表作缓存，注意需要二级接口，带缓存的递归，就是DP
class Solution1
{
  public:
    int rob(TreeNode *root)
    {
        unordered_map<TreeNode *, int> map;
        return rob(root, map);
    }

  private:
    int rob(TreeNode *root, unordered_map<TreeNode *, int> &map)
    {
        if (!root)
            return 0;
        if (map.count(root))
            return map[root];
        int val = 0;
        if (root->left)
            val += rob(root->left->left, map) + rob(root->left->right, map);
        if (root->right)
            val += rob(root->right->left, map) + rob(root->right->right, map);
        map[root] = max(root->val + val, rob(root->left, map) + rob(root->right, map));
        return map[root];
    }
};

//DP
class Solution2
{
  public:
    int rob(TreeNode *root)
    {
        vector<int> cache = robDP(root);
        return max(cache[0], cache[1]);
    }

  private:
    vector<int> robDP(TreeNode *root)
    { //返回值携带所有信息，一层DP，两个状态码
        if (!root)
            return vector<int>(2, 0);
        vector<int> left = robDP(root->left);
        vector<int> right = robDP(root->right);
        int notHasRoot = max(left[0], left[1]) + max(right[0], right[1]); //打劫h+1层
        int hasRoot = root->val + left[0] + right[0];                     //打劫h+2层意味着0+0的状态码组合，即可以转化为一层DP'
        return vector<int>{notHasRoot, hasRoot};
    }
};

int main()
{
    Solution2 s1;
    TreeNode *root = constructTree(vector<int> () = {3, 4, 5, 1, 3, -1, 1}); 
    cout << s1.rob(root) << endl;
    return 0;
}