
#include <queue>
#include <D:\Github\RylModule\tree.h>
using namespace std;

// 递归法
class Solution1 {
  public:
    bool isSymmetric(TreeNode* root) {
        // if (!root)
        //     return true;
        // return isSame(root->left, root->right);
        return isSame(root, root);
    }
  private:
    bool isSame(TreeNode* left, TreeNode* right) {  
        if (!left && !right)    // 均为空指针，对称
            return true;    
        if (left && right && left->val == right->val)   // 均不为空指针，递归判断
            return isSame(left->left, right->right) && isSame(left->right, right->left);
        return false;
    }
};

// 迭代法-将递归改写为迭代常常需要引入队列
class Solution2 {
  public:
    bool isSymmetric(TreeNode* root) {
        TreeNode* left = nullptr; 
        TreeNode *right = nullptr;
        queue<TreeNode*> q;
        if (!root)
            return true;
        q.push(root->left);q.push(root->right);
        while(!q.empty()) {
            left = q.front();q.pop();
            right = q.front();q.pop();
            if (!left && !right)
                continue;
            if (((!left) ^ (!right)) || (left->val != right->val))
                return false;
            q.push(left->left);q.push(right->right);
            q.push(left->right);q.push(right->left);
        }
        return true;
    }
};

// 根节点合并-相当于创建一个虚拟头节点，左右子树都是root
class Solution {
  public:
    bool isSymmetric(TreeNode* root) {
        return isSame(root, root);
    }
  private:
    bool isSame(TreeNode* left, TreeNode* right) {  
        queue<TreeNode*> q;
        q.push(left);q.push(right);
        while(!q.empty()) {
            left = q.front();q.pop();
            right = q.front();q.pop();
            if (!left && !right)
                continue;
            if (((!left) ^ (!right)) || (left->val != right->val))
                return false;
            q.push(left->left);q.push(right->right);
            q.push(left->right);q.push(right->left);
        }
        return true;
    }
};

int main() {
    Solution s;
    // TreeNode* root = constructTree(vector<int> () = {1, 2, 2, 3, 4, 4, 3});
    TreeNode* root = constructTree(vector<int> () = {1, 2, 2, -1, 3, -1, 3});
    cout << s.isSymmetric(root) << endl;
    return 1;
}