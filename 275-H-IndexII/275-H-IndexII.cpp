#include <vector>
#include <iostream>
using namespace std;

// h = [1, N]
// BS
// time: O(lgn)
// space: O(1)
class Solution {
  public:
    int hIndex(vector<int> &citations) {
        int ilen = citations.size();
        int start = 0, end = ilen - 1;
        while (start <= end) {
            int mid = start + ((end - start) >> 1);
            if (citations[mid] == ilen - mid) { // 如果mid不是最大的h,假如存在一个h'>h是h指数，剩余论文数一定小于等于h对应的论文，和h定义冲突。
                return ilen - mid;
            } else if(citations[mid] > ilen - mid) {    // 引用大于剩余论文数量，在左区间查找。
                end = mid - 1;
            } else {
                start = mid + 1;    // 引用小于剩余论文数量，在右区间查找。但注意这里start也可能是h指数。
            }
        }
        return ilen - start; // 如果没有找到刚好的h，h指数必然是[start, ilen - 1]区间。
    }
};

int main() {
    Solution s;
    vector<int> citations = {0, 1, 3, 5, 6};    // 3
    // vector<int> citations = {1, 2, 100};    // 2
    // vector<int> citations = {100};  // 1
    cout << s.hIndex(citations) << endl;
    return 0;
}