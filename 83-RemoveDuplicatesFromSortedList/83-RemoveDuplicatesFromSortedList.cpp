#include <iostream>
#include <iostream>
#include <E:\RylModule\list.h>
using namespace std;

class Solution
{
  public:
    ListNode *deleteDuplicates(ListNode *head)
    {
		ListNode *temp = head;
		ListNode *dtemp = nullptr;
		while (temp)
		{
			if (temp->next)
			{ //有下一个判断是否需要删除
				if (temp->next->val == temp->val)
				{ //删除
					dtemp = temp->next;
					temp->next = dtemp->next;
					delete dtemp;
				}
				else
					temp = temp->next; //不删除
			}
			else
				break; //到达链表尾，跳出循环
		}
		return head;
    }
};

int main()
{
    Solution s1;
    ListNode *head = constructList(vector<int>() = {1, 1, 2, 3, 3});
    head = s1.deleteDuplicates(head);
	showList(head);
    return 0;
}