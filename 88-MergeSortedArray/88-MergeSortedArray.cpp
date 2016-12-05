#include <vector>
#include <iostream>
#include <E:\RylModule\vector.h>
using namespace std;

//A by leetcode
class Solution
{
  public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
		int j = m - 1;
		int k = n - 1;
		int idex = j + k + 1;
		nums1.reserve(j + k + 2); //扩充容器大小
		nums1.resize(j + k + 2);  //补0初始化容器对象
		while (j >= 0 && k >= 0)  //nums1和nums2都有元素存在
			nums1[idex--] = nums1[j] > nums2[k] ? nums1[j--] : nums2[k--];
		while (k >= 0) //nums1中的元素用完了，将nums2中的元素拷贝过来
			nums1[idex--] = nums2[k--];
		//若nums2为空，在这里什么也不做（k=-1，nums1的对象原地保留）
    }
};

int main()
{
    vector<int> a = {1, 3, 5, 7, 9, 11, 13, 15, 17, 19};
    vector<int> b = {2, 4, 6, 8, 10, 12, 14, 16, 18, 20};
    Solution s1;
    s1.merge(a, a.size(), b, b.size());
    show1DVector(a);
    show1DVector(b);
    return 0;
}
