#include <vector>
#include <iostream>
#include <D:\Github\RylModule\list.h>
using namespace std;

// 模拟 - 注意是逆序存储的
// time: O(max(m, n))
// space: O(1)
class Solution0 {
  public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
		// ListNode *ll1 = reverseList(l1);
		// ListNode *ll2 = reverseList(l2);
		ListNode *ll1 = l1, *ll2 = l2;
		ListNode *dummy = new ListNode(0), *pre = dummy;
		int l = 0, r = 0, carry = 0, cur = 0;
		while (ll1 || ll2 || carry) {
			l = ll1 ? ll1->val : 0;
			ll1 ? ll1 = ll1->next : 0;
			r = ll2 ? ll2->val : 0;
			ll2 ? ll2 = ll2->next : 0;
			cur = (l + r + carry) % 10;
			carry = (l + r + carry) / 10;
			ListNode *tmp = new ListNode(cur);
			pre->next = tmp;
			pre = pre->next;
		}
		return dummy->next;
		// return reverseList(dummy->next);
    }
  private:
	ListNode *reverseList(ListNode *l) {
		ListNode dummy(0), *p = nullptr;
		while (l) {
			p = dummy.next;
			dummy.next = l;
			l = l->next;
			dummy.next->next = p;			
		}
		return dummy.next;
	}
};

// 模拟 - 注意是逆序存储的
// time: O(max(m, n))
// space: O(1)
class Solution {
  public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
		ListNode *head = nullptr, *tail = nullptr;
		int carry = 0;
		while (l1 || l2) {
			int n1 = l1 ? l1->val : 0;
			int n2 = l2 ? l2->val : 0;
			int sum = n1 + n2 + carry;
			if (!head) {
				head = tail = new ListNode(sum % 10);
			} else {
				tail->next = new ListNode(sum % 10);
				tail = tail->next;
			}
			carry = sum / 10;
			if (l1) l1 = l1->next;
			if (l2) l2 = l2->next;
		}
		if (carry > 0) tail->next = new ListNode(carry);
		return head;
    }
};

int main() {
    ListNode *l1 = constructList(vector<int>() = {2, 4, 3});
    ListNode *l2 = constructList(vector<int>() = {5, 6, 4});
    Solution s1;
    ListNode *l3 = s1.addTwoNumbers(l1, l2);
    showList(l1);
    showList(l2);
    showList(l3);
    return 0;
}