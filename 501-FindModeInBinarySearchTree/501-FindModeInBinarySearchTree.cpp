#include <limits>
#include <iostream>
#include <D:/Github/RylModule/tree.h>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// inOrder
// time: O(n)
// space: O(1)
class Solution1 {
  public:
    vector<int> findMode(TreeNode *root) {
        vector<int> ans = {};
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
        (pre && pre->val == root->val) ? cur_cnt++ : cur_cnt = 1;   // 上一个节点不为空且和当前节点值相同, +1否则重新计数
        if (cur_cnt > max_cnt) {    // 更新众数
            max_cnt = cur_cnt;
            ans_cnt = 1;
        } else if (cur_cnt == max_cnt) {    // 找到第二个众数
            if (ans.size())     // 复用控制
                ans[ans_cnt] = root->val;
            ans_cnt++;
        }
        pre = root; // 上一个节点
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
            if (!cur->left) {   // 左子树为空时, 直接比较, 然后进入右子树
                update (ans, pre, cur, count, max_num); // 众数更新
                pre = cur;
                cur = cur->right;
            } else {    // 进入左子树, 找到cur的前驱节点, (1)cur的左子节点没有右子节点,那么左子节点就是前驱(2)cur的左子节点有右子节点,一路向右下走到底就是cur的前驱
                TreeNode *preceesor = cur->left;
                while (preceesor->right && preceesor->right != cur)
                    preceesor = preceesor->right;
                if (preceesor->right == cur) {    // 前驱已经指向自己了, 直接比较然后进入右子树
                    update (ans, pre, cur, count, max_num); // 众数更新
                    pre = cur;
                    cur = cur->right;
                    preceesor->right = nullptr; // 树恢复原状
                } else {    // 前驱还没有指向自己, 让前驱指向自己, 进入左子树
                    preceesor->right = cur;
                    cur = cur->left;
                }
            }
        }
        return ans;
    }
  private:
    void update(vector<int> &ans, TreeNode *pre, TreeNode *cur, int &count, int &max_num) {   // 众数更新
        count = pre && pre->val == cur->val ? count + 1: 1; // 众数更新
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