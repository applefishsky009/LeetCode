#include <iostream>
#include <D:/Github/RylModule/list.h>
using namespace std;

// 逆置单链表
// time: O(n)
// space: O(n)
class Solution1 {
  public:
    bool isPalindrome(ListNode *head) {
        int len = 0, cnt = 0;
        ListNode *tail = new ListNode(0);
        ListNode *pre = tail, *src= head;
        while (head) {
            pre = tail->next;
            tail->next = new ListNode(head->val);
            tail->next->next = pre;
            head = head->next;
            len++;
        }
        tail = tail->next;
        while (cnt < (len >> 1)) {
            if (tail->val != src->val)  
                return false;
            cnt++;
            tail = tail->next;
            src = src->next;
        }
        return true;
    }
};

// 原地逆置一半单链表
// time: O(n)
// space: O(1)
class Solution2 {
  public:
    bool isPalindrome(ListNode *head) {
        int len = 0, cnt = 1;   // cnt超头
        ListNode *pre = head, *half = new ListNode(0);
        while (pre) {   // 计算链表长度
            pre = pre->next;
            len++;
        }
        pre = head;
        while (cnt < ((len + 1) >> 1)) {  // 计算超头, 对奇偶长度分情况讨论
            pre = pre->next;
            cnt++;
        }
        while (pre && pre->next) { // 原地逆置单链表, pre防止空链表
            ListNode *tmp = half->next;
            half->next = pre->next;
            pre->next = pre->next->next;
            half->next->next = tmp;
        }
        half = half->next;
        while (half) {
            if (half->val != head->val)
                return false;
            half = half->next;
            head = head->next;
        }
        return true;
    }
};

// 快慢指针 - 原地逆置一半单链表
// time: O(n)
// space: O(1)
class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if(!head || !head->next) return true;
        ListNode *fast = head, *slow = head, *pre = nullptr;
        while(fast && fast->next) {    //1、找到链表的中点，链表长度奇偶不影响
            slow = slow->next;
            fast = fast->next->next;
        }
        while(slow) {   //2、将slow之后链表进行断开且反转，最后翻转完成之后pre指向反转链表的头节点
            ListNode *p = slow->next;   // 剩余链表节点
            slow->next = pre;   // 头插
            pre = slow; // pre指向头
            slow = p;   // slow指向剩余链表节点
        }
        while(head && pre) {    //3、前后链表进行比较，注意若为奇数链表，后半部分回比前部分多1一个节点，然而我们只比较相同长度的节点值，巧妙地避开这点判断
            if(head->val != pre->val) return false;
            head = head->next;
            pre = pre->next;
        }
        return true;
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {1, 2};
    vector<int> nums1 = {1, 2, 2, 1};
    vector<int> nums2 = {1, 1, 2, 1};
    vector<int> nums3 = {1, 0, 1};
    ListNode *head0 = constructList(nums0);
    ListNode *head1 = constructList(nums1);
    ListNode *head2 = constructList(nums2);
    ListNode *head3 = constructList(nums3);
    // cout << s.isPalindrome(head0) << endl;  // 0
    cout << s.isPalindrome(head1) << endl;  // 1
    // cout << s.isPalindrome(head2) << endl;  // 0
    // cout << s.isPalindrome(nullptr) << endl;    // 1
    cout << s.isPalindrome(head3) << endl;  // 1
    return 0;
}