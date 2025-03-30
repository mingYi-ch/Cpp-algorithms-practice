#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// use a bit more space
class SolutionMap
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        map<int, int> counts;
        for (const int &num : nums)
        {
            counts[num] = 1; // time complexity O(1), by hash map
        }

        size_t idx = 0;
        for (const auto &pairs : counts)
        {
            nums[idx] = pairs.first;
            ++idx;
        }
        return counts.size();
    }
};

// in-place, nums is sorted, 1 <= nums.length <= 3 * 10^4
class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        uint16_t idx1 = 0;
        uint16_t idx2 = 1;

        while (idx2 < nums.size())
        {
            if (nums[idx1] != nums[idx2])
                nums[++idx1] = nums[idx2++];
            else
                idx2++;
        }

        return idx1 + 1;
    }
};