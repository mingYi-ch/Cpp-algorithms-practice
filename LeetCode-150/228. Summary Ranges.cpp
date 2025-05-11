#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<string> summaryRanges(vector<int> &nums)
    {
        vector<string> ranges;
        size_t left = 0, right = 0;
        string interval;
        while (left < nums.size())
        {
            while (right + 1 < nums.size() && nums[right] + 1 == nums[right + 1])
            {
                ++right;
            }

            if (left == right)
            {
                interval = to_string(nums[left]);
            }
            else
            {

                interval = to_string(nums[left]) + "->" + to_string(nums[right]);
            }

            ranges.push_back(interval);
            ++right;
            left = right;
        }
        return ranges;
    }
};