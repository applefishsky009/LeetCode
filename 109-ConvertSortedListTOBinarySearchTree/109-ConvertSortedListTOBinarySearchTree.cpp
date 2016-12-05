#include <vector>
#include <iostream>
#include <E:\RylModule\list.h>
#include <E:\RylModule\tree.h>
using namespace std;

//仿STL的思路传递头部和超尾
class Solution
{
  public:
    TreeNode *sortedListToBST(ListNode *head)
    {
        return sortedListToBST(head, nullptr);
    }

  private:
    TreeNode *sortedListToBST(ListNode *head, ListNode *tail)
    {
        if (head == tail)
            return nullptr;
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast->next != tail && fast->next->next != tail)
        {
            fast = fast->next;
            fast = fast->next;
            slow = slow->next;
        }
        if (fast->next != tail)
            slow = slow->next; //注意二分时是 (0+s.size())/2即偏右的作为中心，因此不平衡需要向前走
        TreeNode *tmp = new TreeNode(slow->val);
        tmp->left = sortedListToBST(head, slow);
        tmp->right = sortedListToBST(slow->next, tail);
        return tmp;
    }
};

int main()
{
    Solution s1;
    ListNode *head = constructList(vector<int> () = {1, 2, 3, 4, 5}); 
    TreeNode *root = s1.sortedListToBST(head);
    showTree(root);
    return 0;
}