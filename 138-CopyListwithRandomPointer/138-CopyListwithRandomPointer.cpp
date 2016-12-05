#include <iostream>
using namespace std;

struct RandomListNode
{
    int label;
    RandomListNode *next, *random;
    RandomListNode(int x) : label(x), next(NULL), random(NULL) {}
};

//深复制带随机指针的链表
class Solution
{
  public:
    RandomListNode *copyRandomList(RandomListNode *head)
    {
        if (!head)
            return nullptr;
        //深复制结点
        RandomListNode *temp = head;
        while (temp)
        {
            RandomListNode *pre = temp->next;
            temp->next = new RandomListNode(temp->label);
            temp->next->next = pre;
            temp = pre;
        }
        //连接random指针
        temp = head;
        while (temp)
        { //temp可能为nullptr,temp不为空往前走，有随机指针则复制
            if (temp->random)
                temp->next->random = temp->random->next;
            temp = temp->next->next;
        }
        //断开指针
        temp = head;
        RandomListNode *const resultHead = head->next;
        RandomListNode *tempResult = resultHead;
        while (temp)
        {
            temp->next = tempResult->next;
            tempResult->next = temp->next == nullptr ? nullptr : temp->next->next;
            temp = temp->next;
            tempResult = tempResult->next;
        }
        return resultHead;
    }
};

int main()
{
    Solution s1;
    RandomListNode *head = new RandomListNode(1);
    head->random = head;
    head->next = new RandomListNode(2);
    head->next->next = new RandomListNode(3);
    head->next->next->random = head->next->next;
    RandomListNode *headResult = s1.copyRandomList(head);
    return 0;
}