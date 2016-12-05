#include <iostream>
#include <E:\RylModule\list.h>
using namespace std;

//设快慢指针相遇时慢指针走了s步，环长为r，那么对快指针：2s = s+nr；即有关系s = nr；(注意相遇时慢指针一定没有走完链表一次)
//设链表长度为L,链表头到环结点的距离为x,环结点到快慢指针相遇结点的距离为a,那么s(x+a) = nr((n-1)*r+L-x)
//即有关系：x = (n-1)r+(L-x-a),L-x-a在链表上代表相遇结点到环结点的距离！
//注意数学分析，注意自己的测试用例
class Solution
{
  public:
    ListNode *detectCycle(ListNode *head)
    {
        ListNode *fast = head;
        ListNode *slow = head;
        ListNode *lastSlow = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (fast == slow)
            { //说明有环
                while (1)
                { //两个慢指针一定会相遇
                    if (slow == lastSlow)
                        return lastSlow; //只能先判断再前进
                    slow = slow->next;
                    lastSlow = lastSlow->next;
                }
            }
        }
        return nullptr;
    }
};

//别人的代码，基本一样
class Solution1
{
  public:
    ListNode *detectCycle(ListNode *head)
    {
        ListNode *slow = head, *fast = head;
        while (fast && fast->next)
        {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast)
            {
                ListNode *slow2 = head;
                while (slow2 != slow)
                {
                    slow2 = slow2->next;
                    slow = slow->next;
                }
                return slow2;
            }
        }
        return nullptr;
    }
};

int main()
{
    Solution s1;
    ListNode *head = constructList(vector<int> () = {1, 2, 3, 4}); 
    assert(head != nullptr);
    ListNode *pre = head;
    while(pre->next)
        pre = pre->next;
    pre->next = head;
    ListNode *circle = s1.detectCycle(head);
    cout << circle->val << endl;
    return 0;
}