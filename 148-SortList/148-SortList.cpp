#include <climits>
#include <iostream>
#include <E:\RylModule\list.h>
using namespace std;

//链表的归并排序，重点在于找中间指针并断开连接
class Solution
{
  public:
    ListNode *sortList(ListNode *head)
    {
		//递归出口
		if (head == nullptr || head->next == nullptr)
			return head;
		//找中间指针,两个指针，快指针走两步，慢指针走一步
		ListNode *fast = head;
		ListNode *slow = head;
		while (fast->next && fast->next->next)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		fast = slow;
		slow = slow->next;
		fast->next = nullptr;
		//归并排序
		head = sortList(head);
		slow = sortList(slow);
		return mergeList(head, slow);
    }

  private:
    //合并有序链表，头指针很重要
    ListNode *mergeList(ListNode *head, ListNode *slow)
    {
		ListNode l(-1);
		ListNode *cur = &l;
		while (head || slow)
		{
			int temp1 = head ? head->val : INT_MAX;
			int temp2 = slow ? slow->val : INT_MAX;
			if (temp1 < temp2)
			{
				cur->next = head;
				head = head->next;
			}
			else
			{
				cur->next = slow;
				slow = slow->next;
			}
			cur = cur->next;
		}
		cur->next = nullptr;
		return l.next;
    }
};

int main()
{
    Solution s1;
    ListNode *head = constructList(vector<int> () = {3, 1, 5, 2, 66}); 
    head = s1.sortList(head);
	showList(head);
    return 0;
}