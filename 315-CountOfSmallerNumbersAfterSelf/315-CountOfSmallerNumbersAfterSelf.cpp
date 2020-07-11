#include <vector>
#include <iostream>
#include <algorithm>
#include <D:/Github/RylModule/vector.h>
using namespace std;

// 树状数组 binary indexed tree
class BITree {
  public:
    BITree (int length) {   // 初始化, 因为树状数组的0不能参与下标, 传入的length一定要比数组大
        bitree.resize(length, 0);
    }
    void update(int pos) {  // 单点更新, 从孩子到父亲, 也是构建函数
        while(pos < bitree.size()) {
            bitree[pos]++;
            pos += lowBit(pos); // 父亲位置
        }
    }
    int query(int pos) {    // 区间查询, 从父亲到孩子
        int ret = 0;
        while (pos > 0) {
            ret += bitree[pos];
            pos -= lowBit(pos); // 孩子位置
        }
        return ret;
    }
  private:
    vector<int> bitree;
    int lowBit(int x) { // 取出x的最低位1以及后边的0,后边0的个数表示这个位置管理的数据个数
        return x & (-x);
    }
};

class Solution {
  public:
    vector<int> countSmaller(vector<int>& nums) {
        int len = nums.size();
        vector<int> unique_nums;
        vector<int> ans;
        discretization(nums, unique_nums);
        BITree bitree(len + 5); // reserve
        for (int i = len - 1; i >= 0; --i) {
            int id = getId(unique_nums, nums[i]);
            ans.push_back(bitree.query(id - 1));    // 区间查询 - 查找已有的小于该id的数量 - 自顶而下, 找孩子
            bitree.update(id);  // 单点更新, 自下而上, 找父亲
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
  private:
    void discretization(vector<int>& nums, vector<int> &unique_nums) {  // 有序, 离散化映射
        unique_nums.assign(nums.begin(), nums.end());
        sort(unique_nums.begin(), unique_nums.end());
        unique_nums.erase(unique(unique_nums.begin(), unique_nums.end()), unique_nums.end());   // unique不改变数组，返回超尾
    }
    int getId(vector<int>& unique_nums, int x) {    // 二分查找
        // return lower_bound(unique_nums.begin(), unique_nums.end(), x) - unique_nums.begin() + 1;    // 查找x的下标, +1是因为树状数组第0个元素不参加计算
        return upper_bound(unique_nums.begin(), unique_nums.end(), x) - unique_nums.begin(); // 大于x的第一个数
    }
};

int main() {
    Solution s;
    vector<int> nums = {5, 2, 6, 1};
    show1DVector(s.countSmaller(nums));
    return 0;
}