#include <vector>
#include <iostream>
using namespace std;

// 快慢指针,假设环长L,从起点到环入口是步数a,从环入口继续走b步达到相遇位置,从相遇位置继续走c步回到环入口
// 则b+c=L,那么2(a + b) = a + b + KL,即,a = KL - b = (K - 1)L + c,相遇点一定是环起点
// 龟兔赛跑算法
class Solution1 {
  public:
    int findDuplicate(vector<int> nums) {
        int slow = 0, fast = 0;
        do {
            slow = nums[slow];
            fast = nums[nums[fast]];
        } while(slow != fast);
        slow = 0;
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[fast];
        }
        return slow;
    }
};

// 二进制统计, 如果target第i位为1,那么每次替换后只会使x不变或增大,如果为0,只会使x不变或减小,
// 始终满足x > y时target第i位为1,否则为0,因此我们只要按位还原这个重复的数即可.
class Solution2 {
public:
    int findDuplicate(vector<int>& nums) {
        int n = nums.size(), ans = 0, bit_max = 31;
        int x = 0, y = 0, bit = 0, i = 0;
        while (!((n - 1) >> bit_max))   // 确定最高为位数
            bit_max -= 1;
        for (bit = 0; bit <= bit_max; ++bit) {
            x = 0, y = 0;
            for (i = 0; i < n; ++i) {
                if (nums[i] & (1 << bit))   // 位与,取数组数字bit位
                    x += 1;
                if (i >= 1 && (i & (1 << bit))) // 位与,取idx的bit位
                    y += 1;
            }
            if (x > y)
                ans |= 1 << bit;
        }
        return ans;
    }
};

// 定义cnt[i]表示nums[]数组中小于等于i的数有多少个,假设我们重复的数是target,
//那么[1,target−1]里的所有数满足cnt[i] <= i,[target,n] 里的所有数满足cnt[i] > i,具有单调性。
class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        int i = 0, mid = 0, n = nums.size();
        int l = 1, r = n - 1, ans = -1, cnt = 0;
        while (l <= r) {    // 二分查找cnt变化点
            mid = (l + r) >> 1; // 二分查找mid计算,这样表述时, l = l + 1, l <= r
            cnt = 0;
            for (i = 0; i < n; ++i)
                cnt += (nums[i] <= mid);
            if (cnt <= mid)
                l = mid + 1;
            else {
                r = mid - 1;
                ans = mid;
            }
        }
        return ans;
    }
};

int main() {
    Solution s;
    // vector<int> nums = {1, 3, 4, 2, 2};
    // vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 3};
    vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1};
    cout << s.findDuplicate(nums) << endl;
    return 1;
}