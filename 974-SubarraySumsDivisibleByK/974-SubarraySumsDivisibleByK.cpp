#include <cmath>
#include <vector>
#include <iostream>
#include <unordered_map>
using namespace std;

class Solution {
  public:
    int subarraysDivByK(vector<int>& A, int K) {
        int cnt = 0, sum = 0;
        unordered_map<int, int> rem_k = {{0, 1}};
        for (auto &x : A) { 
            sum += x;
            cnt += rem_k[(sum % K + K) % K] ++;   // 合并

            // rem = (sum % K + K) % K; // 余数可以为负数, 注意 C++ 取模的特殊性，当被除数为负数时取模结果为负数，需要纠正
            // cnt += rem_k[rem] ++;   // 合并

            // rem = (sum % K + K) % K; // 余数可以为负数, 注意 C++ 取模的特殊性，当被除数为负数时取模结果为负数，需要纠正
            // cnt += rem_k[rem];
            // rem_k[rem] ++;

            // rem = sum % K; // 余数可以为负数, 注意 C++ 取模的特殊性，当被除数为负数时取模结果为负数，需要纠正
            // if (rem > 0)
            //     cnt += (rem_k[rem] + rem_k[rem - K]);
            // else if (rem < 0)
            //     cnt += (rem_k[rem] + rem_k[K + rem]);
            // else 
            //     cnt += rem_k[rem];
            // rem_k[rem] ++;
        }
        return cnt;
    }
};

int main() {
    Solution s;
    // vector<int> A = {4, 5, 0, -2, -3, 1};
    // int K = 5;
    // vector<int> A = {5};
    // int K = 5;
    // vector<int> A = {5, 5};
    // int K = 5;
    vector<int> A = {-1, 2, 9};
    int K = 2;
    // vector<int> A = {2, -2, 2, -4};
    // int K = 6;
    cout << s.subarraysDivByK(A, K) << endl;
    return 1;
}