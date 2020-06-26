#include <map>
#include <random>
#include <vector>
#include <chrono>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <D:/Github/RylModule/tree.h>
using namespace std;

// BST 5个对外接口-中序遍历,查找,插入,删除,创建,5个内部接口-迭代搜索,最大值,最小值,查找后继,子树替换
class BinarySearchTree {
  public:
    // 中序遍历BST树x,返回序列是有序的
    void inorderTreeWalk(TreeNode *x, vector<int> &inorder) {
        if (!x) return;
        inorderTreeWalk(x->left, inorder);
        inorder.push_back(x->val);
        inorderTreeWalk(x->right, inorder);
    }
    // 在树root中查找是否存在val为target的节点
    TreeNode* treeSearch(TreeNode *root, int target) {
        if (!root || root->val == target) return root;
        if (target < root->val)
            return treeSearch(root->left, target);
        return treeSearch(root->right, target);
    }
    // 在root的BST中插入single节点
    TreeNode* treeInsert(TreeNode* root, TreeNode* single) {
        TreeNode *parent = nullptr;
        TreeNode *child = root;
        while (child) {    // 找到该插入的位置
            parent = child;
            if (single->val < child->val)
                child = child->left;
            else 
                child = child->right;
        }
        single->parent = parent;
        if (!parent)    // root为空
            root = single;
        else if (single->val < parent->val) // 插入
            parent->left = single;
        else 
            parent->right = single;
        return root;
    }
    // 在root的BST中删除single节点
    TreeNode* treeDelete(TreeNode* root, TreeNode* single) {
        if (!single) 
            return root;
        if (!single->left)  // 左子树为空, 直接用右子树替换
            transPlant(root, single, single->right);
        else if (!single->right)    // 右子树为空, 直接用左子树替换
            transPlant(root, single, single->left);
        else {  // 有两个孩子, z的后继y一定在右子树中
            TreeNode* y = treeMinimum(single->right);
            if (y != single->right) {   // 后继不是z的右孩子, 构造y为右孩子的子树
                transPlant(root, y, y->right); // 把y拿出来
                y->right = single->right;   // 把y插入子树根部
                y->right->parent = single;  // 维护parent
            }
            transPlant(root, single, y);    // 用y替换single
            y->left = single->left; // 维护左节点
            y->left->parent = y;    // 维护左节点parent
        }
        return root;
    }
    // 随机构建二叉搜索树, 最坏理论性能O(lgn)
    TreeNode* constructBSTTree(vector<int> &nums) {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(nums.begin(), nums.end(), default_random_engine(seed));
        TreeNode *root = nullptr;
        for (auto &x : nums)
            root = treeInsert(root, new TreeNode(x));
        return root;
    }
  private:
    // 以迭代的方式查找root的BST中是否存在val为target的节点
    TreeNode* iterativeTreeSearch(TreeNode *root, int target) {
        while (!root && root->val != target) {
            if (target < root->val)
                root = root->left;
            else
                root = root->right;
        }
        return root;
    }
    // 查找root的BST树中的最小值
    TreeNode* treeMinimum(TreeNode *root) {
        if (!root) return nullptr;   // 可以交给调用这个函数的条件判断
        while (root->left)
            root = root->left;
        return root;
    }
    // 查找root的BST树中的最大值
    TreeNode* treeMaximum(TreeNode *root) {
        if (!root) return nullptr;   // 可以交给调用这个函数的条件判断
        while (root->right)
            root = root->right;
        return root;
    }
    // 查找root节点的后继
    TreeNode* treeSuccessor(TreeNode *root) {
        if (!root) return nullptr;
        if (root->right)    // 右子树不为空,找右子树的最小值
            return treeMinimum(root->right);
        TreeNode *rootp = root->parent; // 右子树为空,向上回溯找第一个左父亲
        while(!rootp && rootp->right == root) {
            root = rootp;
            rootp = root->parent;
        }
        return rootp;
    }
    // root为BST树根, u,v是root的子树, 用子树v替换子树u, 仅改变父亲的连接关系
    void transPlant(TreeNode* root, TreeNode *u, TreeNode *v) {
        if (!u->parent) // u为根节点
            root = v;
        else if (u == u->parent->left)  // u是父节点的左孩子
            u->parent->left = v;
        else    // u是父节点的右孩子
            u->parent->right = v;
        if (v)  // 更新父节点
            v->parent = u->parent;
    }
};

// unorder_map 哈希表 散列表 空间O(n), 时间O(n)
class Solution1 {
  public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        unordered_map<int, int> umap;
        for (int i = 0; i < nums.size(); i++) {
            if (umap[nums[i]] != 0 && i + 1 - umap[nums[i]] <= k)
                return true;
            umap[nums[i]] = i + 1;
        }
        return false;
    }
};

// 红黑树,近似平衡的搜索二叉树 空间O(k), 时间O(n * lgn), 其实这里用set就可以了
class Solution {
  public:
    bool containsNearbyDuplicate(vector<int>& nums, int k) {
        map<int, int> imap;
        if (!k) return false;   // 防止搜索删除失败
        for (int i = 0; i < nums.size(); i++) {
            if (imap.count(nums[i]))    // map中为过去k个元素
                return true;
            if (imap.size() >= k)   // 平衡二叉树中删除元素
                imap.erase(imap.find(nums[i - k]));
            imap[nums[i]] = i;  // 插入
        }
        return false;
    }
};

int main() {
    // Solution s;
    // vector<int> nums0 = {1, 2, 3, 1};
    // vector<int> nums1 = {1, 0, 1, 1};
    // vector<int> nums2 = {1, 2, 3, 1, 2, 3};
    // vector<int> nums3 = {1, 2, 1};
    // cout << s.containsNearbyDuplicate(nums0, 3) << endl;
    // cout << s.containsNearbyDuplicate(nums1, 1) << endl;
    // cout << s.containsNearbyDuplicate(nums2, 2) << endl;
    // cout << s.containsNearbyDuplicate(nums3, 0) << endl;

    TreeNode *root = constructTree(vector<int>() = {4, 2, 7, 1, 3});
    BinarySearchTree bst;
    TreeNode *rootbst = bst.constructBSTTree(vector<int>() = {4, 2, 7, 1, 3});
    showTree(rootbst);
    bst.treeDelete(rootbst, rootbst->right);
    showTree(rootbst);
    vector<int> ans;
    bst.inorderTreeWalk(root, ans);
    show1DVector(ans);
    
    return 1;
}