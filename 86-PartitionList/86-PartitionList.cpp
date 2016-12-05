#include <iostream>
#include <E:\RylModule\list.h>
using namespace std;

class Solution
{
  public:
    ListNode *partition(ListNode *head, int x)
    {
		ListNode *temp = new ListNode(-1);
		temp->next = head;
		const ListNode *protectFromMemLeak = temp;
		ListNode *left = new ListNode(-1);
		const ListNode *head_left = left;
		ListNode *right = new ListNode(-1);
		const ListNode *head_right = right;
		while (temp->next)
		{
			if (temp->next->val < x)
			{
				left->next = temp->next;
				left = left->next;
			}
			else
			{
				right->next = temp->next;
				right = right->next;
			}
			temp = temp->next;
		}
		left->next = head_right->next;
		right->next = nullptr; //注意一定要置空，不然容易成为循环链表。
		ListNode *cur = head_left->next;
		delete head_left;
		delete head_right;
		delete protectFromMemLeak;
		return cur;
    }
};

int main()
{
    Solution s1;
    ListNode *head = constructList(vector<int>() = {2, 1});
    int x = 2;
    head = s1.partition(head, x);
	showList(head);
    return 0;
}