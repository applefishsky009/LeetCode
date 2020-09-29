#include <queue>
#include <utility>
using namespace std;

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;
    Node() : val(0), left(NULL), right(NULL), next(NULL) {}
    Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
    Node(int _val, Node* _left, Node* _right, Node* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};


// 常数空间bfs
// time: O(n)
// space: O(1)
class Solution {
  public:
    Node *connect(Node *root) {
        if (!root) return root;
        Node *pre_root = root;
        while (pre_root) {
            Node *cur = nullptr; // 下一层的第一个结点
            Node *pre = nullptr; // 当前层的最前一个结点
            for (; pre_root; pre_root = pre_root->next) { // 当前层根据next遍历
                if (!cur)   // 下一层的第一个节点还没有找到, 继续找
                    cur = pre_root->left ? pre_root->left : pre_root->right; // cur为空，找下一层的最头结点
                if (pre_root->left) { // 衔接next，更新最前指针
                    if (pre)    // 
                        pre->next = pre_root->left; // 衔接下一层
                    pre = pre_root->left;   // 更新下一层的最前节点
                }
                if (pre_root->right) {
                    if (pre)
                        pre->next = pre_root->right;    // 衔接下一层
                    pre = pre_root->right;  // 更新下一层的最前节点
                }
            }
            pre_root = cur; // 下一层的第一个节点
        }
        return root;
    }
};

int main() {
    Solution s1;
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->right = new Node(7);
    s1.connect(root);

    return 0;
}