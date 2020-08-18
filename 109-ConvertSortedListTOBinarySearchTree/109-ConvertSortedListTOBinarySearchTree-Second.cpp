#include <vector>
#include <iostream>
#include <D:\Github\RylModule\list.h>
#include <D:\Github\RylModule\tree.h>
using namespace std;

// 超尾
// time: O(n)
// space: O(lgn)
class Solution0 {
  public:
    TreeNode* sortedListToBST(ListNode* head) {
        return sortedListToBST(head, nullptr);
    }
  private:
    TreeNode *sortedListToBST(ListNode *head, ListNode *tail) { // 传递头和超尾
        if (head == tail) return nullptr; 
        ListNode *fast = head, *slow = head;
        // while (fast != tail && fast && fast->next != tail && fast->next) {
        while (fast != tail && fast->next != tail) {    // tail才可能为空, 等效于 fast && fast->next
            fast = fast->next->next;
            slow = slow->next;
        }
        TreeNode *root = new TreeNode(slow->val);
        root->left = sortedListToBST(head, slow);
        root->right = sortedListToBST(slow->next, tail);
        return root;
    }
};

// 分治 + 中序遍历优化
// time: O(n)
// space: O(lgn)
class Solution {
  public:
    TreeNode* sortedListToBST(ListNode* head) {
        int ilength = getLength(head);
        return buildTree(head, 0, ilength - 1);
    }
  private:
    int getLength(ListNode *head) {
        int ilength = 0;
        for (; head; head = head->next) ++ilength;
        return ilength;
    }
    TreeNode *buildTree(ListNode *&head, int left, int right) { // 传递头和尾的闭区间
        if (left > right) return nullptr; 
        int mid = left + ((right - left) >> 1);
        TreeNode *root = new TreeNode();
        root->left = buildTree(head, left, mid - 1);    //运行完成后head已经指向mid的节点了
        root->val = head->val;
        head = head->next;  // 构建一个节点向前走一步
        root->right = buildTree(head, mid + 1, right);
        return root;
    }
};

int main() {
    Solution s1;
    ListNode *head = constructList(vector<int> () = {1, 2, 3, 4, 5}); 
    TreeNode *root = s1.sortedListToBST(head);
    showTree(root);
    return 0;
}