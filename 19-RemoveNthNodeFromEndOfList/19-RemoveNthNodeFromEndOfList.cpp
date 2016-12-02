#include <E:\RylModule\list.h>
using namespace std;

class Solution
{
  public:
    ListNode *removeNthFromEnd(ListNode *head, int n)
    {
		if (head == nullptr || n < 1)
			return nullptr;
		ListNode l(0);
		l.next = head;
		ListNode *p = &l;
		ListNode *q = &l;
		//第一个指针先走
		for (int i = 0; i < n; ++i)
		{
			if (p->next)
				p = p->next;
			else
				return nullptr;
		}
		//两个指针一起走
		while (p->next)
		{
			p = p->next;
			q = q->next;
		}
		//删除结点
		p = q->next;
		q->next = q->next->next;
		delete p;
		return l.next;
    }
};

int main()
{
    Solution s1;
    ListNode *head = constructList(vector<int>() = {1, 2, 3, 4, 5});
    int n = 3;
    showList(head);
    head = s1.removeNthFromEnd(head, n);
    showList(head);
    return 0;
}