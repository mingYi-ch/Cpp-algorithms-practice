#include <vector>
#include <numeric>
#include <iostream>
using namespace std;

// check all possible min_len: bad complexity
class Solution
{
public:
    int minSubArrayLen(int target, vector<int> &nums)
    {
        size_t min_len = 1;
        auto start = nums.begin();
        auto end = start + min_len;

        while (min_len < nums.size())
        {
            int sum = accumulate(start, end, 0);
            if (sum >= target)
                return min_len;

            while (end != nums.end())
            {
                ++start;
                ++end;
                sum = sum - *(start - 1) + *(end - 1);
                if (sum >= target)
                    return min_len;
            }
            ++min_len;
        }
        return 0;
    }
};

int main()
{
    Solution sol; // Create an instance of the Solution class

    // Test case 1: Basic test case
    vector<int> nums1 = {2, 3, 1, 2, 4, 3};
    int target1 = 7;
    int expected1 = 2; // The shortest subarray is [2, 4, 3] or [4,3]
    int result1 = sol.minSubArrayLen(target1, nums1);
    assert(result1 == expected1);
    cout << "Test Case 1 Passed:  Output = " << result1 << endl;

    // Test case 2: Target is larger than the sum of all elements
    vector<int> nums2 = {1, 2, 3, 4, 5};
    int target2 = 20;
    int expected2 = 0; // No subarray sums to 20
    int result2 = sol.minSubArrayLen(target2, nums2);
    assert(result2 == expected2);
    cout << "Test Case 2 Passed:  Output = " << result2 << endl;

    // Test case 3: Single element array
    vector<int> nums3 = {5};
    int target3 = 5;
    int expected3 = 1;
    int result3 = sol.minSubArrayLen(target3, nums3);
    assert(result3 == expected3);
    cout << "Test Case 3 Passed:  Output = " << result3 << endl;

    // Test case 4: Single element array where target is not met
    vector<int> nums4 = {5};
    int target4 = 6;
    int expected4 = 0;
    int result4 = sol.minSubArrayLen(target4, nums4);
    assert(result4 == expected4);
    cout << "Test Case 4 Passed:  Output = " << result4 << endl;

    // Test case 5: Array with zeros
    vector<int> nums5 = {2, 3, 0, 0, 4, 3};
    int target5 = 7;
    int expected5 = 2; // The shortest subarray is [4, 3]
    int result5 = sol.minSubArrayLen(target5, nums5);
    assert(result5 == expected5);
    cout << "Test Case 5 Passed: Output = " << result5 << endl;

    cout << "All test cases passed!" << endl;

    return 0;
}
