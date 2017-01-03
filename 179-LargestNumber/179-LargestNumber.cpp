#include <string>
#include <vector>
#include <cassert>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

class Solution
{
  public:
    string largestNumber(vector<int> &nums)
    {
        assert(!nums.empty());
        vector<string> result;
        for_each(nums.begin(), nums.end(), [&result](const int &x) { result.push_back(to_string(x)); });
        sort(result.begin(), result.end(), [](const string &a, const string &b) { return a + b > b + a; });
        string res;
        for_each(result.begin(), result.end(), [&res](const string &x) { res += x; });
        return res[0] == '0' ? "0" : res; //"00"?
    }
};

int main()
{
    Solution s1;
    vector<int> nums = {3, 30, 34, 5, 9};
    cout << s1.largestNumber(nums) << endl;
    return 0;
}