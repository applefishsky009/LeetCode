#include <vector>
#include <iostream>
#include <unordered_map>
#include <utility>
// #include <D:\Github\RylModule\tree.h>
using namespace std;

// 官方解法-自己代码的简洁版本\
//http://www.cplusplus.com/reference/unordered_map/unordered_map/operator[]/  unordered_map的trick
//https://stackoverflow.com/questions/40098080/stdmapoperator   trick的说明
//https://en.cppreference.com/w/cpp/language/value_initialization   trick说明的来源
class Solution {
  public:
    int subarraySum(vector<int>& nums, int k) {
      int i = 0, count = 0, cur_sum = 0;
      unordered_map<int, int> sub_k;
      sub_k[0] = 1;
      for (auto &x : nums) {
        cur_sum += x;        // 当前和
        if (sub_k.find(cur_sum - k) != sub_k.end()) count += sub_k[cur_sum - k]; // 计算目标次数
        sub_k[cur_sum] ++;        // 维护map
      }
      return count;
    }
};

// 自己写的解法，几个问题：边界处理；make_pair替换为构造函数；map的插入。
class Solution1
{
  public:
    int subarraySum(vector<int>& nums, int k)
    {
      int i = 0;
      int count = 0;
      int pre_sum = 0;
      int cur_sum = 0;
      unordered_map<int, int> sub_k;
      unordered_map<int, int>::const_iterator got;

      sub_k.insert(pair<int, int>(0, 1));
      for (i = 0; i < nums.size(); i++)
      {
        // 当前和
        cur_sum = nums[i] + pre_sum;
        // 计算目标次数
        got = sub_k.find(cur_sum - k);
        if (got != sub_k.end())
        {
          count += sub_k[cur_sum - k];
        }
        // 维护map
        got = sub_k.find(cur_sum);
        if (got == sub_k.end())
        {
          sub_k.insert(pair<int, int>(cur_sum, 1));
        }else
        {
          sub_k[cur_sum] += 1;
        }
        pre_sum = cur_sum;
      }
      return count;
    }
};

int main()
{
    Solution s;
    // vector<int> nums = {1, 1, 1}; // 2 - 2
    // vector<int> nums = {1, 2, 3}; // 3 - 2
    // vector<int> nums = {-1, -1, 1}; //0 - 1
    // vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 1, 23, 21, 3, 1, 2, 1, 1, 1, 1, 1, 12, 2, 3, 2, 3, 2, 2}; // 1-8
    vector<int> nums = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0}; // 0-55
    cout << s.subarraySum(nums, 0) << endl;

    unordered_map<int, int> sub_k;
    cout << sub_k[6] << endl;
    return 0;
}