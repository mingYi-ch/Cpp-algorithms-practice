#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
using namespace std;

// check all possible min_len: bad complexity O(n^2)
// sliding window, bug, to will go beyond the to
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        int min_len = INT_MAX;
        int sum = 0;
        auto from = nums.begin();
        auto to = from;

        while (to != nums.end())
        {
            sum += *to;

            while (sum >= target)
            {
                min_len = min(min_len, (int)distance(from, to) + 1); // from will only be larger than to by -1, then ++from catch up
                sum -= *from;
                ++from;
            }
            ++to;
        }

        return (min_len == INT_MAX) ? 0 : min_len;
    }
};

// Function to run test cases
void runTest(int target, vector<int> nums, int expected)
{
    Solution sol;
    int result = sol.minSubArrayLen(target, nums);
    cout << "Target: " << target << ", Array: {";
    for (size_t i = 0; i < nums.size(); ++i)
    {
        cout << nums[i] << (i == nums.size() - 1 ? "" : ", ");
    }
    cout << "}, Expected: " << expected << ", Got: " << result;

    if (result == expected)
        cout << " ✅ Passed\n";
    else
        cout << " ❌ Failed\n";
}

// Main function with test cases
int main()
{
    runTest(7, {2, 3, 1, 2, 4, 3}, 2);               // Expected: 2 (subarray {4,3})
    runTest(4, {1, 4, 4}, 1);                        // Expected: 1 (subarray {4})
    runTest(11, {1, 1, 1, 1, 1, 1, 1}, 0);           // Expected: 0 (no valid subarray)
    runTest(15, {5, 1, 3, 5, 10, 7, 4, 9, 2, 8}, 2); // Expected: 2 ({10,7})
    runTest(11, {1, 2, 3, 4, 5}, 3);                 // Expected: 3 (subarray {3,4,5})

    return 0;
}