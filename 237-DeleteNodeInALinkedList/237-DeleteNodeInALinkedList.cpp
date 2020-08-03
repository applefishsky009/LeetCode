#include <iostream>
#include <D:/Github/RylModule/list.h>
using namespace std;

// 和下一个节点交换
// time: O(1)
// space: O(1)
class Solution {
  public:
    void deleteNode(ListNode *node) {
        node->val = node->next->val;
        node->next = node->next->next;
    }  
};

int main() {
    Solution s;
    vector<int> nums = {4, 5, 1, 9};
    ListNode *head = constructList(nums);
    s.deleteNode(head->next);
    return 0;
}
