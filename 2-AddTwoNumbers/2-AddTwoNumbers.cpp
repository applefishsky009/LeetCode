#include <vector>
#include <iostream>
#include <E:\RylModule\list.h>
using namespace std;

class Solution
{
  public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
	{
		ListNode dummy(-1);
		int carry = 0;
		ListNode *prev = &dummy;
		for (ListNode *pa = l1, *pb = l2;
			pa != nullptr || pb != nullptr;
	     	pa = pa == nullptr ? nullptr : pa->next,
		    pb = pb == nullptr ? nullptr : pb->next,
		    prev = prev->next)
		{
	    	const int ai = pa == nullptr ? 0 : pa->val;
			const int bi = pb == nullptr ? 0 : pb->val;
			const int value = (ai + bi + carry) % 10;
			carry = (ai + bi + carry) / 10;
			prev->next = new ListNode(value);
		}
		if (carry > 0)
			prev->next = new ListNode(carry);
		return dummy.next;
    }
};

int main()
{
    ListNode *l1 = constructList(vector<int>() = {2, 4, 3});
    ListNode *l2 = constructList(vector<int>() = {5, 6, 4});
    Solution s1;
    ListNode *l3 = s1.addTwoNumbers(l1, l2);
    showList(l1);
    showList(l2);
    showList(l3);
    return 0;
}