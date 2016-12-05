#include <iostream>
#include <E:\RylModule\list.h>
using namespace std;

class Solution
{
  public:
    ListNode *reverseBetween(ListNode *head, int m, int n)
    {
		if (n == m)
			return head;
		ListNode *l = new ListNode(-1);
		ListNode *protectFromLeakNode = l; 
		l->next = head;
		ListNode *const begin = l; //保存头节点
		for (int index = 1; index < m; ++index)
			l = l->next;
		ListNode *const noReverseRight = l;    //保存不转置的尾节点
		ListNode *const reverseLeft = l->next; //保存转置之后的尾节点
		ListNode *p = l->next, *q = nullptr;
		for (int index = m; index <= n; ++index)
		{
			q = p;
			p = p->next;
			q->next = l;
			l = q;
		}
		noReverseRight->next = l;
		reverseLeft->next = p; //p指向转置之后的第一个不需要转置的头节点
		ListNode *cur = begin->next;
		delete protectFromLeakNode;
		return cur;
    }
};

int main()
{
    Solution s1;
    ListNode *head = constructList(vector<int>() = {1, 2, 3, 4, 5});
    int m = 3;
    int n = 4;
    head = s1.reverseBetween(head, m, n);
    showList(head);
    return 0;
}