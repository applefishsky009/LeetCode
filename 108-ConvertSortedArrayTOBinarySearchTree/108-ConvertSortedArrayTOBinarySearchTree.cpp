#include <vector>
#include <iostream>
#include <E:\RylModule\tree.h>
using namespace std;

//前开后闭，二分查找传递超尾
class Solution
{
  public:
    TreeNode *sortedArrayToBST(vector<int> &nums)
    {
        return sortedArrayToBST(nums, 0, nums.size());
    }

  private:
    TreeNode *sortedArrayToBST(vector<int> &nums, int low, int high)
    {
        if (low == high)
            return nullptr;
        int mid = low + (high - low) / 2;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = sortedArrayToBST(nums, low, mid);
        root->right = sortedArrayToBST(nums, mid + 1, high);
        return root;
    }
};

int main()
{
    Solution s1;
    vector<int> nums = {1, 2, 3, 4, 5, 6};
    TreeNode *root = s1.sortedArrayToBST(nums);
    showTree(root);
    return 0;
}