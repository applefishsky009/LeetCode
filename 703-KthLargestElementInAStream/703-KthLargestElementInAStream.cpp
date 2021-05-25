#include <queue>
#include <vector>
#include <iostream>
using namespace std;

// Heap Design
// time: O(nlgk) + O(lgk)
// space: O(k)
class KthLargest {
  public:
    KthLargest(int k, vector<int> &nums) {
        this->k = k;
        for (auto num : nums) {
            add(num);
        }
    }

    int add(int val) {
        ipriq.push(val);
        if (ipriq.size() > k) {
            ipriq.pop();
        }
        return ipriq.top();
    }
  private:
    int k;
    priority_queue<int, vector<int>, greater<int>> ipriq;
};

int main() {
    KthLargest *kthLargest = new KthLargest(3, vector<int>() = {4, 5, 8, 2});
    cout << kthLargest->add(3) << endl; // 4
    cout << kthLargest->add(5) << endl; // 5
    cout << kthLargest->add(10) << endl;    // 5
    cout << kthLargest->add(9) << endl; // 8
    cout << kthLargest->add(4) << endl; // 8
    return 0;
}