#include <limits>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// 递归枚举 + 剪枝
// 去重中-对于重复数字 - 前选后不选, 前不选后选, 前选后选, 前不选后不选的前两种情况进行剪枝.保留1减2
// time: O(2^n*n)
// space: O(n)
class Solution0 {
  public:
    vector<vector<int>> findSubsequences(vector<int> &nums) {
        vector<int> tmp;
        vector<vector<int>> ans;
        dfs(0, INT_MIN, nums, tmp, ans);    // 当前位置(开)和前值
        return ans;
    }
  private:
    void dfs(int cur, int last, vector<int> &nums, vector<int> &tmp, vector<vector<int>> &ans) {
        if (cur == nums.size()) {
            if (tmp.size() > 1)
                ans.push_back(tmp);
            return;
        }
        if (nums[cur] >= last) {    // 加入cur继续搜索
            tmp.push_back(nums[cur]);
            dfs(cur + 1, nums[cur], nums, tmp, ans);
            tmp.pop_back();
        }
        if (nums[cur] != last)  // 跳过cur继续搜索, 如果重复的前者被选择了, 后者不被选择
            dfs(cur + 1, last, nums, tmp, ans); // 反正是跳过cur了, 不用判断递增
    }
};


// RKHASH
// time: O(n)
// space: O(1)
class RKHash {
  private:
    using LL = long long; // 定义别名
    static constexpr LL P = (1LL << 31) - 1;  // static所有类共用, constexpr编译时可计算, 字符后缀
    static constexpr LL BASE = 263;  // 不用写构造函数, 不支持自定义素数
  public:
	unordered_set<LL> hashValues;
    LL getHash(const vector<int> &nums) {
        LL hashValue = 0;
		for (int i = nums.size() - 1; i >= 0; --i) {
			hashValue = hashValue * BASE + nums[i] + 101;   // 101作为非负数偏移
			hashValue %= P;
		}
		return hashValue;
    }
    bool hasHash(LL hashValue) {
        return hashValues.find(hashValue) != hashValues.end();
    }
	void insertHash(const vector<int> &nums) {
		hashValues.insert(getHash(nums));
	}
    void insertHashValue(LL hashValue) {
		hashValues.insert(hashValue);
	}
};

// 二进制枚举 + 哈希
// time: O(2^n*n)
// space: O(2^n)
class Solution {
  public:
    vector<vector<int>> findSubsequences(vector<int> &nums) {
        int len = nums.size();
        vector<int> tmp;
        vector<vector<int>> ans;
        RKHash rkh;
        for (int i = 0; i < (1 << len); ++i) {  // 二进制掩膜的标准写法 右边界为(1 << len)
            findSubsequences(i, nums, tmp);
            int hashValue = rkh.getHash(tmp);
            if (check(tmp) && !rkh.hasHash(hashValue)) {
                ans.push_back(tmp);
                rkh.insertHashValue(hashValue);
            }
        }
        return ans;
    }
  private:
    void findSubsequences(int mask, vector<int> &nums, vector<int> &tmp) {
        tmp.clear();
        for (int i = 0; i < nums.size(); ++i) {
            if (mask & 1)
                tmp.push_back(nums[i]);
            mask >>= 1;
        }
    }
    bool check(vector<int> &tmp) {  // 判断是否单调不减
        for (int i = 1; i < tmp.size(); ++i)
            if (tmp[i] < tmp[i - 1])
                return false;
        return tmp.size() > 1;
    }
};

int main() {
    Solution s;
    vector<int> nums0 = {4, 6, 7, 7};
    vector<vector<int>> ans = s.findSubsequences(nums0);
    show2DVector(ans);
    return 0;
}
