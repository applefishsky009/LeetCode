#include <set>
#include <chrono>
#include <random>
#include <iostream>
#include <algorithm>
#include <unordered_map>
// #include <D:/Github/RylModule/BST.h>
#include <D:/Github/RylModule/tree.h>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// BST五个对外接口-中序遍历,查找,插入,删除,创建;五个内部接口,迭代搜索,最大值,最小值,查找后继,子树替换
class BinarySearchTree {
  public:
    // 中序遍历BST树, 返回有序序列
    // time: O(n)
    // space: O(lg(n))
    void inorderTreeWalk(TreeNode *x, vector<int> &inorder) {
        if (!x) return;
        inorderTreeWalk(x->left, inorder);
        inorder.push_back(x->val);
        inorderTreeWalk(x->right, inorder);
    }
    // 在root中查找是否存在val未target的节点
    // time: O(lg(n))
    // space: O(lg(n))
    TreeNode* treeSearch(TreeNode *root, int target) {
        if (!root || root->val == target) 
            return root;
        return root->val > target ? treeSearch(root->left, target) : treeSearch(root->right, target);
    }
    // 在root中插入single节点
    // time: O(lg(n))
    // space: O(1)
    TreeNode *treeInsert(TreeNode *root, TreeNode *single) {
        TreeNode *parent = nullptr;
        TreeNode *child = root;
        while (child) {
            parent = child;
            child = child->val > single->val ? child->left : child->right;
        }
        single->parent = parent;    // 明确树结构定义中需不需要维护parent字段
        if (child)
            return single;
        else if (single->val < parent->val)
            parent->left = single;
        else
            parent->right = single;
        return root;
    }
    // 在BST中删除single节点
    // time: O(lgn)
    // space: O(1)
    TreeNode *treeDelete(TreeNode *root, TreeNode *single) {
        if (!single)
            return root;
        if (!single->left)  // 左子树为空, 直接用右子树替换
            transPlant(root, single, single->right);
        else if (!single->right)
            transPlant(root, single, single->left);
        else {  // 左右子树均不为空, 找后继
            TreeNode *y = treeSuccessor(single);
            if (y != single->right) {   // y不是右孩子, 构建y为右孩子的子树
                transPlant(root, y, y->right);  // 用y的右孩子替换y, 将y分离出来
                y->right = single->right;   // 将y构建在single的右子树根节点处
                y->right->parent = single;
            }
            transPlant(root, single, y);    // 用y替换single
            y->left = single->left;
            y->left->parent = y;
        }
        return nullptr;
    }
    // 随机构建二叉搜索树, 最坏理论性能O(lgn)
    // time: O(nlgn)
    // space: O(1)
    TreeNode *constructBSTTree(vector<int> &nums) {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(nums.begin(), nums.end(), default_random_engine(seed));
        TreeNode *root = nullptr;
        for (auto &x : nums)
            root = treeInsert(root, new TreeNode(x));
        return root;
    }
  private:
    // 迭代的方式查找root的BST中是否存在val为target的节点
    // time: O(lgn)
    // space: O(1)
    TreeNode *iterativeTreeSearch(TreeNode *root, int target) {
        while (root && root->val != target)
            root = root->val > target ? root->left : root->right;
        return root;
    }
    // 查找BST中的最小值
    // time: O(lgn)
    // space: O(1)
    TreeNode *treeMinimum(TreeNode *root) {
        if (!root) 
            return nullptr;
        while (root->left)
            root = root->left;
        return root;
    }
    // 查找BST中的最大值
    // time: O(lgn)
    // space: O(1)
    TreeNode *treeMaximum(TreeNode *root) {
        if (!root) 
            return nullptr;
        while (root->right)
            root = root->right;
        return root;
    }
    // 查找root节点的后继
    // time: O(lgh)
    // space: O(1)
    TreeNode *treeSuccessor(TreeNode *root) {
        if (!root)
            return nullptr;
        if (root->right)    // 右子树不为空, 寻找右子树的最小值
            return treeMinimum(root);
        TreeNode *&rootp = root->parent;
        while(rootp && rootp->right == root) {
            root = rootp;
            rootp = root->parent;
        }
        return rootp;
    }
    // 子树替换, root为BST树根, u,v是root的子树, 用子树v替换子树u, 斤改变父亲的连接关系
    // time: O()
    // space: O()
    void transPlant(TreeNode *root, TreeNode *u, TreeNode *v) {
        if (!u->parent) // u是根节点
            root = v;
        else if (u == u->parent->left)  // u是父节点的左孩子
            u->parent->left = v;
        else    // u是父节点的右孩子
            u->parent->right = v;
        if (v) // 更新父节点
            v->parent = u->parent;
    }
};

// nums[i] - t <= nums[j] <= nums[i] + t
// sort ordered_map
// time : O(n * log(k))
// space : O(k)
class Solution1 {
  public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        int i = 0;
        set<long> iset; // BST二叉搜索树
        for (i = 0; i < nums.size(); ++i) {
            auto pos = iset.lower_bound(long(nums[i]) - t); // 二分搜索
            if (pos != iset.end() && *pos <= long(nums[i]) + t)
                return true;
            iset.insert(nums[i]);
            if (iset.size() > k)
                iset.erase(nums[i - k]);
        }
        return false;
    }
};

// nums[i] - t <= nums[j] <= nums[i] + t
// sort ordered_map
// time : O(n * log(k))
// space : O(k)
class Solution {
  public:
    bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
        int i = 0;
        set<long> iset; // BST二叉搜索树
        for (i = 0; i < nums.size(); ++i) {
            auto pos = iset.lower_bound(long(nums[i]) - t); // 二分搜索
            if (pos != iset.end() && *pos <= long(nums[i]) + t)
                return true;
            iset.insert(nums[i]);
            if (iset.size() > k)
                iset.erase(nums[i - k]);
        }
        return false;
    }
};
 
int main() {
    Solution s;    
    vector<int> nums = {1, 2, 3, 1};
    cout << s.containsNearbyAlmostDuplicate(nums, 3, 0) << endl;
    return 0;
}