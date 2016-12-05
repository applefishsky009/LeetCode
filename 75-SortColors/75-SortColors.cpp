#include <vector>
#include <E:\RylModule\vector.h>
using namespace std;

class Solution
{
  public:
    void sortColors(vector<int> &nums)
    {
		int low = 0;
		int high = nums.size() - 1;
		while (nums[low] == 0)
			++low;
		while (nums[high] == 2)
			--high;
		int pre = low;
		while (pre <= high)
		{ //	high是未归位的，因此要<=
			if (nums[pre] == 1)
				++pre;
			else if (nums[pre] == 0)
			{
				nums[pre] = nums[low];
				nums[low] = 0;
				while (nums[low] == 0)
					++low;
				if (pre <= low)
					pre = low + 1; //更新pre，保证pre在low之前
			}
			else if (nums[pre] == 2)
			{
				nums[pre] = nums[high];
				nums[high] = 2;
				while (nums[high] == 2)
					--high;
			}
		}
    }
};

//for循环的两个指针
class Solution1
{
  public:
    void sortColors(vector<int> &A)
    {
		int red = 0, blue = A.size() - 1;
		for (int i = 0; i < blue + 1;)
		{
			if (A[i] == 0)
				swap(A[i++], A[red++]); //更新i，因为知道换回i的一定是1
			else if (A[i] == 2)
				swap(A[i], A[blue--]); //不更新i，因为不知道换回i的是什么
			else
				i++;
		}
    }
};

int main()
{
    vector<int> nums{2, 0};
    Solution s1;
    s1.sortColors(nums);
	show1DVector(nums);
    return 0;
}