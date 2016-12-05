#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
using namespace std;

//会超时，因为用unordered_map[key]来判断是否有key，会执行插入操作，val是构造函数的默认值;
class Solution
{
  public:
    int longestConsecutive(vector<int> &nums)
    {
		unordered_map<int, bool> map;
		for (int i = 0; i < nums.size(); ++i)
			map[nums[i]] = true;
		int len = 0;
		for (int i = 0; i < nums.size(); ++i)
		{
			int low = 0;
			int high = 0;
			if (map[nums[i]])
			{
				low = nums[i];
				high = nums[i];
				map[nums[i]] = false;
				while (map[high + 1])
				{
					high++;
					map[nums[i] + 1] = false;
				}
				while (map[low - 1])
				{
					low--;
					map[nums[i] - 1] = false;
				}
				len = max(len, high - low + 1);
			}
		}
		return len;
    }
};

//hash map根据key删除元素很方便
class Solution1
{
  public:
    int longestConsecutive(vector<int> &nums)
    {
		unordered_map<int, bool> map;
		for (int i = 0; i < nums.size(); ++i)
			map[nums[i]] = true;
		int len = 0;
		for (int i = 0; i < nums.size(); ++i)
		{
			int low = 0;
			int high = 0;
			if (map.find(nums[i]) != map.end())
			{
				low = nums[i];
				high = nums[i];
				map.erase(low);
				while (map.find(high + 1) != map.end())
				{
					high++;
					map.erase(high);
				}
				while (map.find(low - 1) != map.end())
				{
					low--;
					map.erase(low);
				}
				len = max(len, high - low + 1);
			}
		}
		return len;
    }
};

//暴露两端的聚类
class Solution2
{
  public:
    int longestConsecutive(vector<int> &nums)
    {
		unordered_map<int, int> map;
		int size = nums.size();
		int l = 1;
		for (int i = 0; i < size; i++)
		{
			if (map.find(nums[i]) != map.end())
				continue;
			map[nums[i]] = 1;
			if (map.find(nums[i] - 1) != map.end())
				l = max(l, mergeCluster(map, nums[i] - 1, nums[i]));
			if (map.find(nums[i] + 1) != map.end())
				l = max(l, mergeCluster(map, nums[i], nums[i] + 1));
		}
		return size == 0 ? 0 : l;
    }

  private:
    int mergeCluster(unordered_map<int, int> &map, int left, int right)
    {
		int upper = right + map[right] - 1;
		int lower = left - map[left] + 1;
		int length = upper - lower + 1;
		map[upper] = length;
		map[lower] = length;
		return length;
    }
};

int main()
{
    vector<int> nums = {200, 100, 1, 2, 3, 4};
    Solution s1;
    int longestC = s1.longestConsecutive(nums);
    cout << longestC << endl;
    return 0;
}