#include <limits>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// inOrder
// time: O(n)
// space: O(1)
class Solution0 {
  public:
    vector<int> findMode(TreeNode *root) {
        vector<int> ans;
        int max_cnt = 0, cur_cnt = 0, ans_cnt = 0;
        TreeNode *pre = nullptr;
        inOrder(root, pre, ans, ans_cnt, max_cnt, cur_cnt);
        ans.resize(ans_cnt, 0);
        pre = nullptr;
        ans_cnt = 0;
        cur_cnt = 0;
        inOrder(root, pre, ans, ans_cnt, max_cnt, cur_cnt);
        return ans;
    }
  private:
    void inOrder(TreeNode* root, TreeNode *&pre, vector<int> &ans, int &ans_cnt, int &max_cnt, int &cur_cnt) {
        if (!root) return;
        inOrder(root->left, pre, ans, ans_cnt, max_cnt, cur_cnt);
        (pre && pre->val == root->val) ? cur_cnt++ : cur_cnt = 1;
        if (cur_cnt > max_cnt) {
            max_cnt = cur_cnt;
            ans_cnt = 1;
        } else if (cur_cnt == max_cnt) {
            if (ans.size())
                ans[ans_cnt] = root->val;
            ++ans_cnt;
        }
        pre = root; // 注意中序遍历的前继
        inOrder(root->right, pre, ans, ans_cnt, max_cnt, cur_cnt);
    }
};

// inOrder-Morris
// time: O(n)
// space: O(1)
class Solution {
  public:
    vector<int> findMode(TreeNode *root) {
        TreeNode *cur = root, *pre = nullptr;
        int count = 0, max_num = 0;
        vector<int> ans;
        while (cur) {
            if (cur->left) {    // 进入左子树找前驱
                TreeNode *preceesor = cur->left;
                while (preceesor->right && preceesor->right != cur)
                    preceesor = preceesor->right;
                if (preceesor->right == cur) {  // 发现前驱并比较, 进入右子树
                    // TODO
                    update(ans, pre, cur, count, max_num);
                    // end TODO
                    pre = cur;
                    preceesor->right = nullptr;
                    cur = cur->right;
                } else {    // 初始化前驱连接关系
                    preceesor->right = cur;
                    cur = cur->left;
                }
            } else {    // 左子树为空, 直接比较并进入右子树
                // TODO
                update(ans, pre, cur, count, max_num);
                // end TODO
                pre = cur;
                cur = cur->right;
            }
        }
        return ans;
    }
  private:
    void update(vector<int> &ans, TreeNode *pre, TreeNode *cur, int &count, int &max_num) {   // 众数更新
        count = (pre && pre->val == cur->val) ? count + 1 : 1;
        if (count > max_num) {
            max_num = count;
            ans.clear();
            ans.push_back(cur->val);
        } else if (count == max_num) {
            ans.push_back(cur->val);
        }
    }
};

int main() {
    Solution s;
    TreeNode* root = constructTree(vector<int> {1, INT_MIN, 3, INT_MIN, INT_MIN, 3});
    show1DVector(s.findMode(root));
    return 0;
}