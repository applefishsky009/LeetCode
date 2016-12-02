#include <vector>
#include <climits>
#include <iostream>
#include <E:\RylModule\list.h>
using namespace std;

class Solution
{
  public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
		if (lists.size() == 0)
			return nullptr;
		ListNode *p = lists[0];
		for (int i = 1; i < lists.size(); ++i)
			p = mergeTwoLists(p, lists[i]);
		return p;
    }

  private:
    // Merge Two Sorted Lists
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
		ListNode head(-1);
		ListNode *temp = &head;
		while (l1 || l2)
		{
			if (l1)
			{
				if (l1->val <= (l2 ? l2->val : INT_MAX))
				{
					temp->next = l1;
					temp = temp->next;
					l1 = l1->next;
				}
				else
				{
					temp->next = l2;
					temp = temp->next;
					l2 = l2->next;
				}
			}
			else if (l2)
			{
				temp->next = l2;
				temp = temp->next;
				l2 = l2->next;
			}
		}
		return head.next;
    }
};

class Solution1
{
  public:
    ListNode *mergeKLists(vector<ListNode *> &lists)
    {
		if (lists.size() == 0)
			return nullptr;
		ListNode *p = lists[0];
		for (int i = 1; i < lists.size(); i++)
			p = mergeTwoLists(p, lists[i]);
		return p;
    }

  private:
    // Merge Two Sorted Lists
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
		ListNode head(-1);
		for (ListNode *p = &head; l1 != nullptr || l2 != nullptr; p = p->next)
		{
			int val1 = l1 == nullptr ? INT_MAX : l1->val;
			int val2 = l2 == nullptr ? INT_MAX : l2->val;
			if (val1 <= val2)
			{
				p->next = l1;
				l1 = l1->next;
			}
			else
			{
				p->next = l2;
				l2 = l2->next;
			}
		}
		return head.next;
    }
};

int main()
{
    Solution s1;
    vector<ListNode *> lists(3, nullptr);
    lists[0] = constructList(vector<int>() = {1, 4, 7});
    showList(lists[0]);
    lists[1] = constructList(vector<int>() = {3, 8, 9});
    showList(lists[1]);
    lists[2] = constructList(vector<int>() = {2, 5, 6});
    showList(lists[2]);
    ListNode *result = s1.mergeKLists(lists);
    showList(result);
    return 0;
}