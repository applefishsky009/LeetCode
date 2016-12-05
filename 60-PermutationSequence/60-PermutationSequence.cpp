#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <E:\RylModule\list.h>
using namespace std;

class Solution
{
  public:
    string getPermutation(int n, int k)
    {
        if (n == 0)
            return "";
        //链表模拟哈希表
        ListNode *head = new ListNode(1);
        ListNode *tmp = head;
        for (int i = 1; i < n; ++i)
        {
            tmp->next = new ListNode(i + 1);
            tmp = tmp->next;
        }
        //cout << "链表：" << endl;
        //tmp = head;
        //while (tmp){
        //    cout << tmp->val << endl;
        //    tmp = tmp->next;
        //}
        //数组模拟哈希表缓存(n-1)！
        vector<int> factorial(n, 1);
        for (int i = 1; i < n; ++i)
            factorial[i] = factorial[i - 1] * i;
        //cout << "阶乘表格：" << endl;
        //for (int i = 0;i < n;++i) cout << factorial[i] << endl;

        //逐位计算
        string result;
        int locate = k;
        for (int i = n; i > 0; --i)
        {
            int index = (locate - 1) / factorial[i - 1] + 1;
            //locate -= (locate-1)/factorial[i-1]*factorial[i-1];
            locate = (locate - 1) % factorial[i - 1] + 1; //康托编码
            int target = findTarget(head, index);
            head = deleteListNode(head, target);
            result.push_back(target + '0');
        }
        return result;
    }

  private:
    int findTarget(ListNode *head, int index)
    {
        int i = 1;
        while (i != index)
        {
            head = head->next;
            ++i;
        }
        return head->val;
    }
    ListNode *deleteListNode(ListNode *head, int target)
    {
        ListNode *cur = new ListNode(0);
        cur->next = head;
        ListNode *pre = cur;
        while (pre->next)
        {
            if (pre->next->val == target)
            {
                ListNode *tmp = pre->next;
                pre->next = pre->next->next;
                delete tmp;
            }
            else
                pre = pre->next;
        }
        return cur->next;
    }
};

// LeetCode, Permutation Sequence
// 康托编码 时间复杂度O(n) 空间复杂度 O(1)，我的思路和这个一致，只不过用了缓存和哈希
class Solution1
{
  public:
    string getPermutation(int n, int k)
    {
        string s(n, '0');
        string result;
        for (int i = 0; i < n; ++i)
            s[i] += i + 1;
        return kth_permutation(s, k);
    }

  private:
    int factorial(int n)
    {
        int result = 1;
        for (int i = 1; i <= n; ++i)
            result *= i;
        return result;
    }
    // seq已排好序，是第一个排列
    template <typename Sequence>
    Sequence kth_permutation(const Sequence &seq, int k)
    {
        const int n = seq.size();
        Sequence S(seq);
        Sequence result;
        int base = factorial(n - 1);
        --k; //康托编码从0开始
        for (int i = n - 1; i > 0; k %= base, base /= i, --i)
        {
            auto a = next(S.begin(), k / base);
            result.push_back(*a);
            S.erase(a);
        }
        result.push_back(S[0]); //最后一个
        return result;
    }
};

// LeetCode, Permutation Sequence
// 使用 next_permutation(),TLE,超时
class Solution2
{
  public:
    string getPermutation(int n, int k)
    {
        string s(n, '0');
        for (int i = 0; i < n; ++i)
            s[i] += i + 1;
        for (int i = 0; i < k - 1; ++i)
            next_permutation(s.begin(), s.end());
        return s;
    }

  private:
    template <typename BidiIt>
    bool next_permutation(BidiIt first, BidiIt last)
    {
        // Get a reversed range to simplify reversed traversal.
        const auto rfirst = reverse_iterator<BidiIt>(last);
        const auto rlast = reverse_iterator<BidiIt>(first);
        // Begin from the second last element to the first element.
        auto pivot = next(rfirst);
        // Find `pivot`, which is the first element that is no less than its
        // successor. `Prev` is used since `pivort` is a `reversed_iterator`.
        while (pivot != rlast && *pivot >= *prev(pivot))
            ++pivot;
        // No such elemenet found, current sequence is already the largest
        // permutation, then rearrange to the first permutation and return false.
        if (pivot == rlast)
        {
            reverse(rfirst, rlast);
            return false;
        }
        // Scan from right to left, find the first element that is greater than `pivot`.
        auto change = find_if(rfirst, pivot, bind1st(less<int>(), *pivot));
        swap(*change, *pivot);
        reverse(rfirst, pivot);
        return true;
    }
};

int main()
{
    Solution2 s1;
    int n = 4;
    int k = 3;
    string result = s1.getPermutation(n, k);
    cout << result << endl;

    for (int k = 1; k <= 24; ++k)
    {
        result = s1.getPermutation(n, k);
        cout << result << endl;
        result.clear();
    }
    return 0;
}