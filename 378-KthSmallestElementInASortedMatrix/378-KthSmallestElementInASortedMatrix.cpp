#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <functional>
using namespace std;

// 二维数组的原地最小堆
// time: min(O(klogn), O(n^2))
// space: O(1)
class Solution1 {
  public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        heapSize = n * n;
        if (n == 1) return matrix[0][0];
        buildMinHeap(matrix, n);    // O(n^2)
        for (int i = n * n - 1; i > n * n - 1 - k; i--) {   // O(2klogn)
            swap(matrix[0][0], matrix[i / n][i % n]);
            --heapSize;
            minHeapify(matrix, n, 0);
        }
        return matrix[(n * n - k) / n][(n * n - k) % n];
    }
  private:
    int heapSize;
    void buildMinHeap(vector<vector<int>>& matrix, int n) { // O(n^2logn^2)->O(n^2)
        for (int i = (n * n >> 1) - 1; i >= 0; i--)
            minHeapify(matrix, n, i);
    }
    void minHeapify(vector<vector<int>>& matrix, int n, int idx) {  // O(2logn)
        int i = idx / n, j = idx % n;
        int smallest_i = i, smallest_j = j;
        int l = left(idx), r = right(idx);
        int l_i = l / n, l_j = l % n, r_i = r / n, r_j = r % n;
        if (l < heapSize && matrix[l_i][l_j] < matrix[smallest_i][smallest_j]) {
            smallest_i = l_i;
            smallest_j = l_j;
        }
        if (r < heapSize && matrix[r_i][r_j] < matrix[smallest_i][smallest_j]) {
            smallest_i = r_i;
            smallest_j = r_j;
        }
        if (smallest_i != i || smallest_j != j) {
            swap(matrix[i][j], matrix[smallest_i][smallest_j]);
            minHeapify(matrix, n, smallest_i * n + smallest_j);
        }

    }
    int left(int i) {return (i << 1) + 1;};
    int right(int i) {return (i << 1) + 2;};
};

// 归并排序 - n个有序数组排序的归并排序,堆大小为n
// time: min(O(klogn), O(n))
// space: O(n)
class Solution2 {
  public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int n = matrix.size();
        priority_queue<point, vector<point>, greater<point>> iq;   // 通过vector数据结构构建
        for (int i = 0; i < n; i++) // n个有序数组合并, 最小堆大小为n, 最小元素出队列, 对应列表的下一个值入队列, O(n)
            iq.emplace(matrix[i][0], i, 0);
        
        for (int i = 0; i < k - 1; i++) {   // O(klogn)
            point now = iq.top();   // 最小元素出队列, 如果所在有序组有next, 入队列
            iq.pop();
            if(now.y != n - 1)
                iq.emplace(matrix[now.x][now.y + 1], now.x, now.y + 1);
        }
        return iq.top().val;    // 弹出了k - 1个最小元素, top即是第k个最小元素
    }
  private:
    struct point {
        int val;
        int x;
        int y;
        point(int val, int x, int y) : val(val), x(x), y(y) {};
        bool operator> (const point& a) const {return this->val > a.val;};  // 最小堆,大于时需要调整
    };
};

// 二分查找-找值而不是下标
// time: O(nlog(r - l))
// space: O(1)
class Solution {
  public:
    int kthSmallest(vector<vector<int>>& matrix, int k) {
        int len = matrix.size(), left = matrix[0][0], right = matrix[len - 1][len - 1];
        while (left < right) {
            int mid = left + ((right - left) >> 1);
            if (check(matrix, mid, k, len)) // 检查小于等于mid数量是否大于等于k, mid可能是目标, 因此上界不能向下更新
                right = mid;    // 上界不能向下更新, 且无法针对mid进行剪枝, 因为val是发散的, 必须left和right收敛才能返回
            else
                left = mid + 1;
        }   
        return left;
    }
  private:
    bool check(vector<vector<int>>& matrix, int mid, int k, int n){
        int i = n - 1, j = 0, num = 0;
        while (i >= 0 && j < n) {
            if (matrix[i][j] <= mid) {
                num += i + 1;
                j++;
            }else
                i--;
        }
        return num >= k;
    }
};

int main() {
    Solution s;
    vector<vector<int>> nums0 = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    vector<vector<int>> nums1 = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    vector<vector<int>> nums2 = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    vector<vector<int>> nums3 = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    vector<vector<int>> nums4 = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    vector<vector<int>> nums5 = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    vector<vector<int>> nums6 = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    vector<vector<int>> nums7 = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    vector<vector<int>> nums8 = {{1, 5, 9}, {10, 11, 13}, {12, 13, 15}};
    cout << s.kthSmallest(nums0, 1) << endl;
    cout << s.kthSmallest(nums1, 2) << endl;
    cout << s.kthSmallest(nums2, 3) << endl;
    cout << s.kthSmallest(nums3, 4) << endl;
    cout << s.kthSmallest(nums4, 5) << endl;
    cout << s.kthSmallest(nums5, 6) << endl;
    cout << s.kthSmallest(nums6, 7) << endl;
    cout << s.kthSmallest(nums7, 8) << endl;
    cout << s.kthSmallest(nums8, 9) << endl;
    return 1;
};