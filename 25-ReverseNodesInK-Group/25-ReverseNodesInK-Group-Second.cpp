#include <D:\Github\RylModule\list.h>
using namespace std;

class Solution
{
  public:
    ListNode *reverseKGroup(ListNode *head, int k) {
		int count = 0;
		ListNode tail(0);
		ListNode *pre = head;
		ListNode *dst = &tail;	// 链表中常用的trick
		ListNode *tmp = nullptr;
		while(pre && pre->next)	{// head是当前链表段的头，pre是找尾，tmp用来记录下一个临时头部。
			pre = pre->next;
			count ++;
			if (count == k - 1) {
			  tmp = pre->next;
			  pre->next = nullptr;	//断链表
			  dst->next = reverseList(head);	// 原地逆置单链表
			  dst = head;	// 目标链表指向尾部
			  head = tmp;	// 为下一次处理做准备
			  pre = tmp;
			  count = 0;
			}
		}
		dst->next = head;	// 最后的链表不够k个，直接连接
		return (&tail)->next;
    }
  private:
    ListNode *reverseList(ListNode *head) {
		ListNode *dst_list = nullptr;
		ListNode *tmp = nullptr;
		while(head != nullptr) {
			tmp = head;
			head = head->next;
			tmp->next = dst_list;
			dst_list = tmp;
		}
		return dst_list;
	}
};

int main()
{
    Solution s1;
    ListNode *head = constructList(vector<int>() = {1, 2, 3, 4, 5});
	showList(head);
    int k = 1;
    head = s1.reverseKGroup(head, k);
    // head = s1.reverseList(head);
	showList(head);
    return 0;
}