#include <vector>
#include <iostream>
using namespace std;

//自底向上的迭代贪心，自顶向下省略。
class Solution
{
  public:
    bool canJump(vector<int> &nums)
    {
		int reach = 0;
		for (int i = 0; i < nums.size() - 1; i++)			     //注意最后一步就别跳了
			if (reach >= i)						     //能不能跳到当前步？
				reach = (i + nums.at(i)) > reach ? (i + nums.at(i)) : reach; //更新最优解
		return reach >= nums.size() - 1;
    }
};

int main()
{
    vector<int> numIn = {0, 2, 3};
    Solution s;
    bool isJump = s.canJump(numIn);
    cout << isJump << endl;
    return 0;
}