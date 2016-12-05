#include <iostream>
#include <E:\RylModule\list.h>
using namespace std;

//尾节点 头指针
class Solution
{
  public:
    ListNode *insertionSortList(ListNode *head)
    {
		if (!head)
			return nullptr;
		ListNode l(-1);
		l.next = head;
		ListNode *right = l.next; //尾节点
		ListNode *temp = nullptr;
		while (right->next)
		{ //一次插入
			if (right->next->val >= right->val)
			{ //接在尾巴
				right = right->next;
				continue;
			}
			ListNode *i = &l; //要插入位置的头节点
			while (i != right)
			{ //在第一个节点到尾节点中间插入
				if (i->next->val > right->next->val)
				{
					temp = right->next->next;
					right->next->next = i->next;
					i->next = right->next;
					right->next = temp;
					break;
				}
				else
					i = i->next;
			}
		}
		return l.next;
    }
};

int main()
{
    ListNode *head = constructList(vector<int> () = {6, 4, 2, 1, 3, 5}); 
    Solution s1;
    head = s1.insertionSortList(head);
	showList(head);
    return 0;
}