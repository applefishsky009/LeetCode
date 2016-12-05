
#include <queue>
#include <utility>
using namespace std;

struct TreeLinkNode
{
    int val;
    TreeLinkNode *left, *right, *next;
    TreeLinkNode(int x) : val(x), left(nullptr), right(nullptr), next(nullptr) {}
};

//BFS，但不是常数空间！
class Solution
{
  public:
    void connect(TreeLinkNode *root)
    {
        if (!root)
            return;
        queue<pair<TreeLinkNode *, int>> q;
        q.push(make_pair(root, 1));
        while (!q.empty())
        {
            pair<TreeLinkNode *, int> temp = q.front();
            if (temp.first->left)
                q.push(make_pair(temp.first->left, temp.second + 1));
            if (temp.first->right)
                q.push(make_pair(temp.first->right, temp.second + 1));
            q.pop();
            if (!q.empty() && temp.second == q.front().second)
                temp.first->next = q.front().first;
        }
    }
};

//常数空间，类似于滚动数组的 DP 思路
class Solution1
{
  public:
    void connect(TreeLinkNode *root)
    {
        if (!root)
            return;
        while (root)
        {
            TreeLinkNode *cur = nullptr; //下一层的第一个结点
            TreeLinkNode *pre = nullptr; //当前层的最前一个结点
            for (; root; root = root->next)
            { //当前层根据next遍历
                if (!cur)
                    cur = root->left ? root->left : root->right; //cur为空，找下一个的最头结点
                if (root->left)
                { //衔接next，更新最前指针
                    if (pre)
                        pre->next = root->left;
                    pre = root->left;
                }
                if (root->right)
                {
                    if (pre)
                        pre->next = root->right;
                    pre = root->right;
                }
            }
            root = cur;
        }
        return;
    }
};

int main()
{
    Solution1 s1;
    TreeLinkNode *root = new TreeLinkNode(1);
    root->left = new TreeLinkNode(2);
    root->right = new TreeLinkNode(3);
    root->left->left = new TreeLinkNode(4);
    root->left->right = new TreeLinkNode(5);
    root->right->right = new TreeLinkNode(7);
    s1.connect(root);
    return 0;
}