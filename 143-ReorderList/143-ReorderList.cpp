#include <stack>
#include <iostream>
#include <E:\RylModule\list.h>
using namespace std;

//重点如何找到某一结点(尤其是尾部的)的前驱->记录路径->联想到栈，但是就地算法只能用O(1)的空间！！以下不符合题意'
class Solution
{
  public:
    void reorderList(ListNode *head)
    {
        stack<ListNode *> s;
        ListNode *cur = head;
        while (cur)
        {
            s.push(cur);
            cur = cur->next;
        }
        if (s.size() < 3)
            return;
        cur = head;
        ListNode *pre = s.top();
        s.pop();
        while (cur != pre && cur->next != pre)
        { //奇数或偶数个分别是重合或相邻，注意相邻不需要修改
            ListNode *tmp = cur->next;
            cur->next = pre;
            pre->next = tmp;
            s.top()->next = nullptr;
            cur = tmp;
            pre = s.top();
            s.pop();
        }
    }
};

// LeetCode, Reorder List
// 时间复杂度 O(n) 空间复杂度 O(1)
//这是就地算法，二分链表再合并'
class Solution1
{
  public:
    void reorderList(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return;
        ListNode *slow = head, *fast = head, *prev = nullptr;
        while (fast && fast->next)
        {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }
        prev->next = nullptr; // cut at middle
        slow = reverse(slow);
        // merge two lists
        ListNode *curr = head;
        while (curr->next)
        {
            ListNode *tmp = curr->next;
            curr->next = slow;
            slow = slow->next;
            curr->next->next = tmp;
            curr = tmp;
        }
        curr->next = slow;
    }
    ListNode *reverse(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
            return head;
        ListNode *prev = head;
        for (ListNode *curr = head->next, *next = curr->next; curr;
             prev = curr, curr = next, next = next ? next->next : nullptr)
        {
            curr->next = prev;
        }
        head->next = nullptr;
        return prev;
    }
};

int main()
{
    Solution1 s1;
    ListNode *head = constructList(vector<int> () = {1, 2, 3, 4, 5}); 
    s1.reorderList(head);
    showList(head);
    return 0;
}