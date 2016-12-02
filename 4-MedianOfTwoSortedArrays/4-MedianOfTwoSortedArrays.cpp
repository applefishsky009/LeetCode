#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

//线性搜索直到中间元素
class Solution
{
  public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
	{
		const int m = nums1.size();
		const int n = nums2.size();
		const int isOddOrEven = (m + n) % 2;
		vector<int>::iterator p = nums1.begin();
		vector<int>::iterator q = nums2.begin();
		int temp1 = 0;
		for (int i = 0; i < (m + n) / 2; ++i) //因为是有序数组，先走一半
		{
			int k1 = p == nums1.end() ? INT_MAX : *p;
			int k2 = q == nums2.end() ? INT_MAX : *q;
			if (k1 < k2)
			{
				temp1 = k1;
				p++;
			}
			else
			{
				temp1 = k2;
				q++;
			}
		}
		int next1 = p == nums1.end() ? INT_MAX : *p;
		int next2 = q == nums2.end() ? INT_MAX : *q;
		int temp2 = min(next1, next2);
		if (isOddOrEven != 0)
			return temp2; //奇数个，返回中位数(稍大的数字)
		else
			return ((double)temp1 + temp2) / 2; //偶数个，返回中间两个数的平均数
    }
};

//有序数组可以使用二分搜索
class Solution1
{
  public:
    double findMedianSortedArrays(const vector<int> &A, const vector<int> &B)
	{
		const int m = A.size();
		const int n = B.size();
		int total = m + n;
		if (total & 0x1) //判断奇数 WTF!!!
			return find_kth(A.begin(), m, B.begin(), n, total / 2 + 1);
		else //偶数
			return (find_kth(A.begin(), m, B.begin(), n, total / 2) + find_kth(A.begin(), m, B.begin(), n, total / 2 + 1)) / 2.0;
    }
  private:
    static int find_kth(std::vector<int>::const_iterator A, int m,
			std::vector<int>::const_iterator B, int n, int k)
	{
		//always assume that m is equal or smaller than n
		if (m > n)
			return find_kth(B, n, A, m, k); //m<=n
		if (m == 0)
			return *(B + k - 1); //小数组遍历完了，直接取大数组中的值
		if (k == 1)
			return min(*A, *B); //小数组中还有值，取第一个小元素
		//divide k into two parts
		int ia = min(k / 2, m), ib = k - ia; //保证两数组左侧个数和是k，
		//min(k/2，m)保证二分搜索时小数组不越界，这样小数组删完了可以直接取大数组，另外，大小数组个数和大于k
		if (*(A + ia - 1) < *(B + ib - 1))
			return find_kth(A + ia, m - ia, B, n, k - ia); //A的前ia个元素一定是小于第k个的，删掉ia个元素继续找
		else if (*(A + ia - 1) > *(B + ib - 1))
			return find_kth(A, m, B + ib, n - ib, k - ib); //B的前ib个元素一定是小于第k个的，删掉ib个元素继续找
		else						   //说明第k个就是A[ia-1]=B[ib-1]
			return A[ia - 1];
    }
};

int main()
{
    Solution1 s1;
    vector<int> nums1 = {};
    vector<int> nums2 = {8};
    cout << s1.findMedianSortedArrays(nums1, nums2) << endl;
    return 0;
}