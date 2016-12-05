#include <iostream>
#include <E:\RylModule\list.h>
using namespace std;

//一定要注意，这道题k是从后往前数第k个。。。审题错误浪费好久
//如下解法，单链表变循环链表，O(2n-k) k<=n;
//另外，如何得到第K个节点？可以使用两个指针分别计数出发，O(n)复杂度
class Solution
{
  public:
    ListNode *rotateRight(ListNode *head, int k)
    {
		if (head == nullptr || k == 0)
			return head; //链表要有入口判断
		int len = 1;
		ListNode *p = head;
		while (p->next)
		{ //求链表长度
			len++;
			p = p->next;
		}
		k = len - k % len;
		p->next = head; //首尾相接
		for (int step = 0; step < k; step++)
			p = p->next; //接着往后跑
		head = p->next;    //新的头节点
		p->next = nullptr; //新的尾节点
		return head;
    }
};

int main()
{
    Solution s1;
    ListNode *head = constructList(vector<int>() = {1, 2, 3, 4, 5});
    int k = 1;
    head = s1.rotateRight(head, k);
	showList(head);
    return 0;
}
