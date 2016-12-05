#include <iostream>
#include <E:\RylModule\list.h>
using namespace std;

class Solution
{
  public:
    ListNode *deleteDuplicates(ListNode *head)
    {
		ListNode *l = new ListNode(-1);
		l->next = head;
		ListNode *temp = l;
		while (temp->next)
		{
			bool duplicated = false;
			while (temp->next->next && temp->next->next->val == temp->next->val)
			{ //有重复元素
				ListNode *pre = temp->next;
				temp->next = temp->next->next;
				delete pre;
				if (!duplicated)
					duplicated = true;
			}
			if (duplicated)
			{ //删除重复元素
				ListNode *pre = temp->next;
				temp->next = temp->next->next;
				delete pre;
				continue;
			}
			if (!duplicated)
				temp = temp->next; //没有重复元素
		}
		return l->next;
    }
};

//递归版本
class Solution1
{
  public:
    ListNode *deleteDuplicates(ListNode *head)
    {
		if (!head || !head->next)
			return head;
		ListNode *p = head->next;
		if (head->val == p->val)
		{
			while (p && head->val == p->val)
			{
				ListNode *tmp = p;
				p = p->next;
				delete tmp;
			}
			delete head;
			return deleteDuplicates(p);
		}
		else
		{
			head->next = deleteDuplicates(head->next);
			return head;
		}
    }
};

int main()
{
    ListNode *head = constructList(vector<int>() = {1, 1, 1, 2, 3});
    Solution s1;
    head = s1.deleteDuplicates(head);
	showList(head);
    return 0;
}