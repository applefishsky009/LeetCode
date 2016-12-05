#include <cassert>
#include <iostream>
#include <E:\RylModule\list.h>
using namespace std;

//在环中，假设快指针落后于慢指针k个位置，每次追一个位置，因此k次之后就能相遇(注意每次相对来说前进一步，因此一定可以相遇)
class Solution
{
  public:
    bool hasCycle(ListNode *head)
    {
        if (!head || !head->next)
            return false;
        ListNode *slow = head;       //慢指针后出发
        ListNode *fast = head->next; //快指针先走一步
        while (fast != slow)
        {
            if (!slow->next || !fast->next || !fast->next->next)
                return false;
            fast = fast->next->next;
            slow = slow->next;
        }
        return true; //fast == slow
    }
};

//别人的代码，一点点优化，即如果没有环，快指针永远在前边，因此秩序判断快指针会不会遇到空指针即可
class Solution1
{
  public:
    bool hasCycle(ListNode *head)
    {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
                return true;
        }
        return false;
    }
};

int main()
{
    Solution s1;
    ListNode *head = constructList(vector<int> () = {1, 2, 3, 4});
    ListNode *pre = head;
    assert(pre != nullptr);
    while(pre->next)
        pre = pre->next;
    pre->next = head;
    cout << s1.hasCycle(head) << endl;
    return 0;
}