#include <cmath>
#include <iostream>
#include <unordered_set>
// #include <D:/Github/RylModule/tree.h>
#include <D:/Github/RylModule/list.h>
using namespace std;

// 使用缓冲区记录已存列表
class Solution1 {
  public:
    ListNode* removeDuplicateNodes(ListNode* head) {
        if (!head) return nullptr;
        unordered_set<int> iset;
        ListNode *ans = head;
        do {
            iset.insert(head->val);
            while (head->next && iset.count(head->next->val))
                head->next = head->next->next;
            head = head->next;
        } while (head);
        return ans;
    }
};

// 不使用缓冲区
class Solution {
  public:
    ListNode* removeDuplicateNodes(ListNode* head) {
        if (!head) return nullptr;
        ListNode *ans = head;       
        do {
            while (head->next && isDuplicated(ans, head->next, head->next->val))
                head->next = head->next->next;
            head = head->next;
        } while (head);
        return ans;
    }
  private:
    bool isDuplicated(ListNode* duplicated, ListNode* head, int val) {
        while(duplicated && duplicated != head) {
            if (duplicated->val == val)
                return true;
            duplicated = duplicated->next;
        }
        return false;            
    }
};

int main() {
    Solution s;
    ListNode *head0 = constructList(vector<int> () = {1, 2, 3, 3, 2, 1});
    ListNode *head1 = constructList(vector<int> () = {1, 1, 1, 1, 2});
    showList(s.removeDuplicateNodes(head0));
    showList(s.removeDuplicateNodes(head1));
    return 1;
}