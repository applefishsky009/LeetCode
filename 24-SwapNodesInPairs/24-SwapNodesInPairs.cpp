#include <E:\RylModule\list.h>
using namespace std;

class Solution
{
  public:
    ListNode *swapPairs(ListNode *head)
    {
		ListNode l(-1);
		l.next = head;
		ListNode *nextHead = &l;
		while (nextHead->next && nextHead->next->next)
		{
			ListNode *preHead = nextHead;
			nextHead = nextHead->next;
			preHead->next = nextHead->next;
			nextHead->next = nextHead->next->next;
			preHead->next->next = nextHead;
		}
		return l.next;
    }
};

//狸猫换太子，题目不允许
class Solution1
{
  public:
    ListNode *swapPairs(ListNode *head)
    {
		ListNode l(-1);
		l.next = head;
		ListNode *temp = &l;
		while (temp->next && temp->next->next)
		{
			int tempVal = temp->next->val;
			temp->next->val = temp->next->next->val;
			temp->next->next->val = tempVal;
			temp = temp->next->next;
		}
		return l.next;
    }
};

int main()
{
    ListNode *head = constructList(vector<int>() = {1, 2, 3, 4, 5});
    showList(head);
    Solution s1;
    head = s1.swapPairs(head);
    showList(head);
    return 0;
}