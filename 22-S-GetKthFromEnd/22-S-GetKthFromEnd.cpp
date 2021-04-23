#include <vector>
#include <iostream>
#include "D:/GitHub/RylModule/list.h"
using namespace std;

// TP
// time: O(n)
// space: O(1)
class Solution {
  public:
    ListNode* getKthFromEnd(ListNode* head, int k) {
        ListNode *slow = head;
        ListNode *fast = head;
        while (k > 0) {
            if (fast)
                fast = fast->next;
            else
                return nullptr;
            --k;
        }
        while (fast) {
            fast = fast->next;
            slow = slow->next;
        }
        return slow;
    }
};

int main() {
    ListNode *p = constructList(vector<int> () = {1, 2, 3, 4, 5});
    Solution s;
    cout << s.getKthFromEnd(p, 1)->val << endl;
    cout << s.getKthFromEnd(p, 2)->val << endl;
    cout << s.getKthFromEnd(p, 3)->val << endl;
    cout << s.getKthFromEnd(p, 4)->val << endl;
    cout << s.getKthFromEnd(p, 5)->val << endl;
    return 0;
}