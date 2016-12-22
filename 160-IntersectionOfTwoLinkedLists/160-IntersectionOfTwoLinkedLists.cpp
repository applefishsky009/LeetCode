#include <E:\RylModule\list.h>
using namespace std;

// If the two linked lists have no intersection at all, return null.
// The linked lists must retain their original structure after the function returns.
// You may assume there are no cycles anywhere in the entire linked structure.
// Your code should preferably run in O(n) time and use only O(1) memory.
class Solution
{
  public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB)
    {
        int lenA = calListLen(headA);
        int lenB = calListLen(headB);
        lenA > lenB ? stepPre(&headA, lenA - lenB) : stepPre(&headB, lenB - lenA);
        while (headA && headB && headA != headB)
        {
            headA = headA->next;
            headB = headB->next;
        }
        return headA == nullptr ? nullptr : headA;
    }

  private:
    int calListLen(ListNode *head)
    {
        if (!head)
            return 0;
        int len = 1;
        while (head->next)
        {
            len++;
            head = head->next;
        }
        return len;
    }
    void stepPre(ListNode **head, int step)
    {
        while (step--)
            (*head) = (*head)->next;
        return;
    }
};

int main()
{
    ListNode *headA = constructList(vector<int>() = {2, 4, 6, 7, 8});
    ListNode *headB = constructList(vector<int>() = {1, 3, 5});
    headB->next->next->next = headA->next->next;
    showList(headA);
    showList(headB);
    Solution s1;
    ListNode *result = s1.getIntersectionNode(headA, headB);
    cout << result->val << endl;
    showList(headA);
    showList(headB);
    return 0;
}