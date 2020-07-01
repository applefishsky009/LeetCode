#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_set>
using namespace std;

// dp[i][j] = A[i] == A[j] ? dp[i - 1][j - 1] + 1 : 0
// time: O(n*m)
// space: O(n*m)
class Solution1 {
  public:
    int findLength(vector<int>& A, vector<int>& B) {
        int i = 0, j = 0, m = A.size(), n = B.size(), ans = 0;
        if (!m || !n) return 0;
        vector<vector<int>> dp(m, vector<int>(n, 0));
        for (i = 0; i < m; i++) dp[i][0] = (A[i] == B[0]);
        for (j = 0; j < n; j++) dp[0][j] = (A[0] == B[j]);
        for (i = 1; i < m; i++) {
            for (j = 1; j < n; j++) {
                dp[i][j] = (A[i] == B[j] ? dp[i - 1][j - 1] + 1 : 0);
                ans = max(ans, dp[i][j]);
            }
        }
        return ans;
    }
};

// slide window - A和B相向而行擦肩而过
// time: O((n+m)*min(n,m))
// space: O(1)
class Solution2 {
  public:
    int findLength(vector<int>& A, vector<int>& B) {
        int n = A.size(), m = B.size();
        int ret = 0;
        for (int i = 0; i < n; i++) {
            int len = min(m, n - i);
            int maxlen = maxLength(A, B, i, 0, len);
            ret = max(ret, maxlen);
        }
        for (int i = 0; i < m; i++) {
            int len = min(n, m - i);
            int maxlen = maxLength(A, B, 0, i, len);
            ret = max(ret, maxlen);
        }
        return ret;
    }
  private:
    int maxLength(vector<int>& A, vector<int>& B, int addA, int addB, int len) {
        int ret = 0, k = 0;
        for (int i = 0; i < len; i++) {
            if (A[addA + i] == B[addB + i])
                k++;
            else
                k = 0;
            ret = max(ret, k);
        }
        return ret;
    }
};

// Hash + BS
// time: O((n+m)*log(min(n,m)))
// space: O(n)
class Solution {
  public:
    int findLength(vector<int>& A, vector<int>& B) {
        int left = 1, right = min(A.size(), B.size()) + 1;
        while (left < right) {
            int mid = (left + right) >> 1;
            if (check(A, B, mid))
                left = mid + 1;
            else 
                right = mid;
        }
        return left - 1;
    }
  private:
    const int mod = 1000000009;
    const int base = 103;
    // 使用快速幂计算 x^n%mod 的值
    long long qPow(long long x, long long n) {
        long long ret = 1;
        while (n) {
            if (n & 1) ret = ret * x % mod; // 奇数
            x = x * x % mod;
            n >>= 1;
        }
        return ret;
    }
    bool check(vector<int>& A, vector<int>& B, int len) {
        long long hashA = 0;
        for (int i = 0; i < len; i++)
            hashA = (hashA * base + A[i]) % mod;
        unordered_set<long long> bucketA;
        bucketA.insert(hashA);
        long long mult = qPow(base, len - 1);
        for (int i = len; i < A.size(); i++) {
            hashA = ((hashA - A[i - len] * mult % mod + mod) % mod * base + A[i]) % mod;
            bucketA.insert(hashA);
        }
        long long hashB = 0;
        for (int i = 0; i < len; i++) 
            hashB = (hashB * base + B[i]) % mod;
        if (bucketA.count(hashB))
            return true;
        for (int i = len; i < B.size(); i++) {
            hashB = ((hashB - B[i - len] * mult % mod + mod) % mod * base + B[i]) % mod;
            if (bucketA.count(hashB))
                return true;
        }
        return false;
    }
};

int main() {
    Solution s;
    vector<int> A = {1, 2, 3, 2, 1};
    vector<int> B = {3, 2, 1, 4, 7};
    cout << s.findLength(A, B) << endl;
    return 1;
}