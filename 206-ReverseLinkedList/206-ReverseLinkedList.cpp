#include <vector>
#include <iostream>
#include <E:\RylModule\list.h>
using namespace std;

class Solution
{
  public:
    ListNode *reverseList(ListNode *head)
    {
        ListNode l(-1);
        ListNode *pre = l.next;
        ListNode *q = nullptr;
        while (head)
        {
            q = l.next;
            l.next = head;
            head = head->next;
            l.next->next = q;
        }
        return l.next;
    }
};

int main()
{
    Solution s1;
    ListNode *head = constructList(vector<int>() = {1, 2, 3, 4, 5});
    showList(head);
    head = s1.reverseList(head);
    showList(head);
    return 0;
}
