#include <E:\RylModule\list.h>
using namespace std;

class Solution
{
  public:
    ListNode *reverseKGroup(ListNode *head, int k)
    {
		ListNode l(-1);
		l.next = head;
		ListNode *pre = &l; //头指针
		ListNode *cur = &l; //尾指针
		cur = isValid(pre, k);
		while (cur)
		{
			ListNode *nextPre = pre->next; //保存下一次逆置的头结点，不然转置一次就丢了
			reverse2Group(pre, cur);
			pre = nextPre;
			cur = isValid(pre, k);
		}
		return l.next;
    }

  private:
    //判断是否需要逆置
    ListNode *isValid(ListNode *l, int k)
    {
		int i = 0;
		while (i < k)
		{
			if (l->next)
			{
				l = l->next;
				++i;
			}
			else
				return nullptr;
		}
		return l;
    }
    //原地逆置单链表，注意初始化头节点要指向nullptr，保存两个结点用来恢复链表
    void reverse2Group(ListNode *pre, ListNode *cur)
    {
		ListNode *const preNext = pre->next;
		ListNode *const curNext = cur->next;
		ListNode *p = pre->next;
		pre->next = nullptr;
		while (p != curNext)
		{
			ListNode *q = p->next;
			p->next = pre->next;
			pre->next = p;
			p = q;
		}
		preNext->next = p;
    }
};

//另一种写法，基本一样，将pre->next作为参数传进去不用记录了
class Solution1
{
  public:
    ListNode *reverseKGroup(ListNode *head, int k)
    {
		if (head == nullptr || head->next == nullptr || k < 2)
			return head;
		ListNode dummy(-1);
		dummy.next = head;
		for (ListNode *prev = &dummy, *end = head; end; end = prev->next)
		{
			for (int i = 1; i < k && end; i++)
				end = end->next;
			if (end == nullptr)
				break;
			prev = reverse(prev, prev->next, end);
		}
		return dummy.next;
    }

  private:
    ListNode *reverse(ListNode *prev, ListNode *begin, ListNode *end)
    {
		ListNode *end_next = end->next; //依然有记录end_next
		for (ListNode *p = begin, *cur = p->next, *next = cur->next;
			cur != end_next;
			p = cur, cur = next, next = next ? next->next : nullptr)
		{
			cur->next = p;
		}
		begin->next = end_next;
		prev->next = end;
		return begin;
    }
};

int main()
{
    Solution1 s1;
    ListNode *head = constructList(vector<int>() = {1, 2, 3, 4, 5});
	showList(head);
    int k = 3;
    head = s1.reverseKGroup(head, k);
	showList(head);
    return 0;
}