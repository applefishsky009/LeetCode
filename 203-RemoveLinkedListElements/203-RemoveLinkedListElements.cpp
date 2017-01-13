#include <E:\RylModule\list.h>
using namespace std;

class Solution
{
  public:
    ListNode *removeElements(ListNode *head, int val)
    {
        ListNode l(-1);
        l.next = head;
        ListNode *cur = &l;
        ListNode *del = nullptr;
        while (cur->next)
        {
            if (cur->next->val == val)
            {
                del = cur->next;
                cur->next = del->next;
                delete del;
            }
            else
                cur = cur->next;
        }
        return l.next;
    }
};

class Solution1
{
  public:
    ListNode *removeElements(ListNode *head, int val)
    {
        if (!head)
            return nullptr;
        head->next = removeElements(head->next, val);
        return head->val == val ? head->next : head;
    }
};

int main()
{
    Solution1 s1;
    ListNode *head = constructList(vector<int>() = {1, 2, 6, 3, 4, 5, 6});
    showList(head);
    head = s1.removeElements(head, 6);
    showList(head);
    return 0;
}