#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
using namespace std;

/*
 Boyer-Moore Voting Algorithm.
 The algorithm works under the assumption that a majority element exists
(i.e., an element that appears more than n / 2 times).

Because the majority element appears more than half the time,
it cannot be "balanced out" completely and will end up as the candidate at the end.
*/
class SolutionOptimized
{
public:
    int majorityElement(vector<int> &nums)
    {
        int count = 0;
        int candidate = 0;

        for (int &num : nums)
        {
            if (count == 0)
            {
                candidate = num;
            }
            count += (num == candidate) ? 1 : -1;
        }

        return candidate;
    }
};

class Solution
{
public:
    int majorityElement(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int maxCount = 0;
        int valMajor;

        int count = 0;
        int val = nums.front();

        auto begin = nums.begin();
        auto end = nums.end();
        auto it = begin;

        for (; it != end; ++it)
        {
            if (*it != val && count > maxCount) // prev(end) is the last element
            {
                maxCount = count;
                valMajor = val;

                count = 0;
                val = *it;
            }
            ++count;
        }

        if (it == end && count > maxCount) // last element
        {
            maxCount = count;
            valMajor = val;
        }

        return valMajor;
    }
};