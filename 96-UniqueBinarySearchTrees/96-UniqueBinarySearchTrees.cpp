#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

//二叉搜索树的中序序列时有序的，因此可以尝试用不同的前序序列重建二叉树，'但是可以想到超时了
class Solution
{
  public:
    int numTrees(int n)
    {
        vector<int> inOrder(n, 0);
        for (int i = 0; i < n; ++i)
            inOrder[i] = i + 1;
        vector<int> preOrder(inOrder);
        for (int i = 0; i < preOrder.size(); ++i)
            cout << inOrder[i] << endl;
        int sum = 1;
        while (next_permutation(preOrder.begin(), preOrder.end()))
            if (isBST(preOrder, 0, preOrder.size(), inOrder, 0, inOrder.size()))
                ++sum;
        return sum;
    }

  private:
    bool isBST(const vector<int> &preOrder, int preStart, int preEnd, const vector<int> &inOrder, int inStart, int inEnd)
    {
        if (preStart == preEnd)
            return true;
        int num = 0;
        int index = inStart;
        while (inOrder[index] != preOrder[preStart])
        {
            ++num;
            ++index;
        }
        if (!isSuitable(preOrder, preStart, preEnd, num))
            return false;
        if (isBST(preOrder, preStart + 1, preStart + num + 1, inOrder, inStart, index) &&
            isBST(preOrder, preStart + num + 1, preEnd, inOrder, index + 1, inEnd))
            return true;
        return false;
    }
    bool isSuitable(const vector<int> &preOrder, int preStart, int preEnd, int num)
    {
        for (int i = preStart + 1; i < preStart + num + 1; ++i)
            if (preOrder[preStart] < preOrder[i])
                return false;
        for (int i = preStart + num + 1; i < preEnd; ++i)
            if (preOrder[preStart] > preOrder[i])
                return false;
        return true;
    }
};

//DP问题，f[i]为[1,i]能产生的Unique Binary Search Tree的数目，f[0]=1;f[1]=1;
//f[i]就是f[k]与f[i-k-1]的组合问题(k < i),累计所有的k就得要结果
class Solution1
{
  public:
    int numTrees(int n)
    {
        vector<int> f(n + 1, 0);
        f[0] = 1;
        f[1] = 1; //初始状态
        for (int i = 2; i <= n; ++i)
            for (int j = 0; j < i; ++j)      //累计
                f[i] += f[j] * f[i - j - 1]; //递推
        return f[n];
    }
};

int main()
{
    Solution1 s1;
    int n = 3;
    cout << s1.numTrees(n) << endl;
    return 0;
}