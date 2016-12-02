#include <iostream>
#include <E:\RylModule\list.h>
using namespace std;

class Solution
{
  public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
		ListNode l3(0);
		ListNode *temp = &l3;
		while (l1 != nullptr && l2 != nullptr)
		{
			if (l1->val < l2->val)
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
		temp->next = l1 == nullptr ? l2 : l1; //不用逐一修改结点，后边本来连接在一起
		return l3.next;
    }
};

//精简代码行
class Solution1
{
  public:
    ListNode *mergeTwoLists(ListNode *l1, ListNode *l2)
    {
		ListNode l3(0);
		ListNode *temp = &l3;
		while (l1 != nullptr && l2 != nullptr)
		{
			if (l1->val < l2->val)
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
		temp->next = l1 == nullptr ? l2 : l1;
		return l3.next;
    }
};

int main()
{
    Solution s1;
    ListNode *l1 = constructList(vector<int>() = {1, 3, 5, 7, 9});
    showList(l1);
    ListNode *l2 = constructList(vector<int>() = {2, 4, 6, 8, 10, 11});
    showList(l2);
    ListNode *l3 = s1.mergeTwoLists(l1, l2); //合并之后l1依然指向1，l2依然指向2
    showList(l3);
    return 0;
}