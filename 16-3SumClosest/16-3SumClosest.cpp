#include <vector>
#include <climits>
#include <iostream>
#include <algorithm>
using namespace std;

//超时(O(n^3))，参考之前写的3Sum，没意识到夹逼的精髓是两侧逼近
class Solution
{
  public:
    int threeSumClosest(vector<int> &nums, int target)
    {
		if (nums.size() < 3)
			return 0;
		sort(nums.begin(), nums.end());
		auto p = nums.begin();
		auto q = nums.end();
		--q;
		long long result = LLONG_MAX - INT_MAX; //防溢出
		while (p != q - 1)
		{
			while (q != p + 1)
			{
				auto s = p + 1;
				while (s != q)
				{
					if (abs(*p + *s + *q - target) < abs(result - target))
						result = *p + *s + *q;
					while (s != q - 1 && *(s + 1) == *s)
						++s;
					if (s == q - 1)
						break;
					++s;
				}
				while (q != p + 1 && *(q - 1) == *q)
					--q;
				if (q == p + 1)
					break;
				--q;
			}
			q = nums.end();
			--q;
			while (p != q - 1 && *(p + 1) == *p)
				++p;
			if (p == q - 1)
				break;
			++p;
		}
		return result;
    }
};

//注意迭代器方法的用法
class Solution1
{
  public:
    int threeSumClosest(vector<int> &nums, int target)
    {
		int result = 0;
		int min_gap = INT_MAX;
		sort(nums.begin(), nums.end());
		for (auto a = nums.begin(); a != prev(nums.end(), 2); ++a)
		{ //对a遍历
			auto b = next(a);
			auto c = prev(nums.end());
			while (b < c)
			{ //两侧夹逼
				const int sum = *a + *b + *c;
				const int gap = abs(sum - target);
				if (gap < min_gap)
				{
					result = sum;
					min_gap = gap;
				}
				//夹逼
				if (sum < target)
					++b;
				else
					--c;
			}
		}
		return result;
    }
};

int main()
{
    Solution1 s1;
    vector<int> nums{-1, 2, 1, -4};
    int target = 1;
    cout << s1.threeSumClosest(nums, target) << endl;
    return 0;
}