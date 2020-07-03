#include <vector>
#include <chrono>
#include <random>
#include <cstdlib>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// BST
class Solution {
  public:
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        return constructBST(nums, 0, nums.size() - 1);
    }
  private:
    TreeNode* constructBST(vector<int>& nums, int start, int end) {
        if (start > end)
            return nullptr;
        // int mid = (start + end) >> 1;
        // int mid = (start + end + 1) >> 1;
        // int mid = (start + end + rand() % 2) >> 1;
        int mid = (start + end + distribution(0, 1)) >> 1;
        TreeNode *root = new TreeNode(nums[mid]);
        root->left = constructBST(nums, start, mid - 1);
        root->right = constructBST(nums, mid + 1, end);
        return root;
    }
    int distribution(int start, int end) {
        int dice_roll = 0;
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        default_random_engine generator(seed);
        uniform_int_distribution<int> distribution(start, end);
        dice_roll = distribution(generator);
        return dice_roll;
    }
};

int main() {
    Solution s;
    vector<int> nums = {-10, -3, 0, 5, 9};
    // vector<int> nums = {};
    showTree(s.sortedArrayToBST(nums));
    return 0;
}
