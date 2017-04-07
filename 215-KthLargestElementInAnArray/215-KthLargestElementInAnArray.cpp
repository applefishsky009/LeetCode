#include <vector>
#include <iostream>
#include <algorithm>
#include <E:\RylModule\vector.h>
using namespace std;

class Solution
{
  public:
    int findKthLargest(vector<int> &nums, int k)
    {
        int key = -1, low = 0, high = nums.size() - 1;
        while (low < high)
        {
            key = partition(nums, low, high);
            if (key > k - 1)
                high = key - 1;
            else
                low = key;
        }
        return nums[low];
    }

  private:
    int partition(vector<int> &nums, int low, int high)
    {
        int i = low - 1, j = low, pivkey = nums[high];
        for (; j < high; j++)
            if (nums[j] >= pivkey) //必须含有等于，否则可能收敛在low = high-1
                swap(nums[j], nums[++i]);
        swap(nums[++i], nums[high]);
        return i;
    }
};

class Solution1
{
  public:
    int findKthLargest(vector<int> &nums, int k)
    {
        build_max_heap(nums);
        for (int i = 0; i < k; i++)
        {
            swap(nums[0], nums[heap_size - 1]);
            heap_size--;
            max_heapify(nums, 0);
        }
        return nums[heap_size];
    }

  private:
    int heap_size;
    inline int left(int idx)
    {
        return (idx << 1) + 1;
    }
    inline int right(int idx)
    {
        return (idx << 1) + 2;
    }
    void max_heapify(vector<int> &nums, int idx)
    {
        int largest = idx;
        int l = left(idx), r = right(idx);
        if (l < heap_size && nums[l] > nums[largest])
            largest = l;
        if (r < heap_size && nums[r] > nums[largest])
            largest = r;
        if (largest != idx)
        {
            swap(nums[idx], nums[largest]);
            max_heapify(nums, largest);
        }
    }
    void build_max_heap(vector<int> &nums)
    {
        heap_size = nums.size();
        for (int i = (heap_size >> 1) - 1; i >= 0; i--)
            max_heapify(nums, i);
    }
};

int main()
{
    Solution1 s1;
    vector<int> nums = {99, 99};
    int k = 1;
    cout << s1.findKthLargest(nums, k) << endl;
    return 0;
}
