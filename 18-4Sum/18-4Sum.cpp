#include <vector>
#include <iterator>
#include <algorithm>
#include <unordered_map>
#include <E:\RylModule\vector.h>
using namespace std;

//自己写的，注意减枝条件和在循环开始去掉相同解,O(n^3)，测试中表现良好
class Solution
{
  public:
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
		vector<vector<int>> result;
		if (nums.size() < 4)
			return result;
		sort(nums.begin(), nums.end());
		for (auto p = nums.begin(); p != prev(nums.end(), 3); ++p)
		{ //此处不能剪枝，因为负数
			if (p != nums.begin() && *p == *(p - 1))
				continue; //去掉相同解
			auto q = nums.end();
			--q;
			for (; q != next(p, 2); --q)
			{ //此处不能剪枝，因为负数
				if (q != prev(nums.end(), 1) && *q == *(q + 1))
					continue; //去掉相同解
				auto s = p + 1;
				auto t = q - 1;
				while (s != t)
				{
					if (target - *p - *q < 2 * *s || target - *p - *q > 2 * *t)
						break; //剪枝
					if (s - 1 != p && *s == *(s - 1))
					{
						++s;
						continue;
					};
					if (t + 1 != q && *t == *(t + 1))
					{
						--t;
						continue;
					}; //去掉相同解
					if (target == *p + *s + *t + *q)
					{
						result.push_back({*p, *s, *t, *q});
						++s;
						continue; //可能还有其他解
					}
					if (target - *p - *q - *t > *s)
					{
						++s;
						continue;
					}
					if (target - *p - *q - *s < *t)
					{
						--t;
						continue;
					}
				}
			}
		}
		return result;
    }
};

//测试超时，但是O(n^2)
class Solution1
{
  public:
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
		vector<vector<int>> result;
		if (nums.size() < 4)
			return result;
		sort(nums.begin(), nums.end());
		unordered_multimap<int, pair<int, int>> cache;
		for (int i = 0; i + 1 < nums.size(); ++i)
			for (int j = i + 1; j < nums.size(); ++j)
				cache.insert(make_pair(nums[i] + nums[j], make_pair(i, j)));
		for (auto i = cache.begin(); i != cache.end(); ++i)
		{
			int x = target - i->first;
			auto range = cache.equal_range(x);
			for (auto j = range.first; j != range.second; ++j)
			{
				auto a = i->second.first;
				auto b = i->second.second;
				auto c = j->second.first;
				auto d = j->second.second;
				if (a != c && a != d && b != c && b != d)
				{
					vector<int> vec = {nums[a], nums[b], nums[c], nums[d]};
					sort(vec.begin(), vec.end());
					result.push_back(vec);
				}
			}
		}
		sort(result.begin(), result.end());
		result.erase(unique(result.begin(), result.end()), result.end());
		return result;
    }
};

//测试中很差，平均O（n^2）
class Solution2
{
  public:
    vector<vector<int>> fourSum(vector<int> &nums, int target)
    {
		vector<vector<int>> result;
		if (nums.size() < 4)
			return result;
		sort(nums.begin(), nums.end());
		unordered_map<int, vector<pair<int, int>>> cache;
		for (size_t a = 0; a < nums.size(); ++a)
			for (size_t b = a + 1; b < nums.size(); ++b)
				cache[nums[a] + nums[b]].push_back(pair<int, int>(a, b));
		for (int c = 0; c < nums.size(); ++c)
		{
			for (size_t d = c + 1; d < nums.size(); ++d)
			{
				const int key = target - nums[c] - nums[d];
				if (cache.find(key) == cache.end())
					continue;
				const auto &vec = cache[key];
				for (size_t k = 0; k < vec.size(); ++k)
				{
					if (c <= vec[k].second)
						continue;
					result.push_back({nums[vec[k].first], nums[vec[k].second], nums[c], nums[d]});
				}
			}
		}
		sort(result.begin(), result.end());
		result.erase(unique(result.begin(), result.end()), result.end());
		return result;
    }
};

int main()
{
    Solution2 s1;
    vector<int> num{1, 1, 0, -1, 0, -2, 2, 2};
    int target = 0;
    vector<vector<int>> result = s1.fourSum(num, target);
    show2DVector(result);
    return 0;
}