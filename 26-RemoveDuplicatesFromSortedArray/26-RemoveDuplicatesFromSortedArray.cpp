#include <vector>
#include <iostream>
using namespace std;

// A by leetcode
class Solution
{
  public:
    int removeDuplicates(vector<int> &nums)
    {
		if (nums.empty())
			return 0;
		int index = 0;
		vector<int>::iterator p = nums.begin();
		while (index < nums.size() - 1)
		{
			if (nums[index] == nums[index + 1])
				p = nums.erase(p);
			else
			{
				p++;
				index++;
			}
		}
		return index + 1;
    }
};

int main()
{
    Solution s1;
    vector<int> initVector = {1, 2, 2, 2, 3, 3, 4, 5, 6, 6};
    cout << s1.removeDuplicates(initVector) << endl;
    return 0;
}