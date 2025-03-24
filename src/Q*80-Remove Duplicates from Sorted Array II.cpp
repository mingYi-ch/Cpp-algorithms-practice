#include <vector>
#include <algorithm>
#include <map>

using namespace std;

// in-place, nums is sorted, 1 <= nums.length <= 3 * 10^4
class Solution
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        uint16_t idx1 = 0;
        uint16_t idx2 = 1;
        uint16_t cnt = 0;

        while (idx2 < nums.size())
        {

            if (nums[idx1] == nums[idx2])
            {
                if (cnt < 1) // less than 2 appreance
                {
                    nums[++idx1] = nums[idx2++];
                    ++cnt;
                }
                else
                {
                    ++idx2;
                }
            }
            else
            {
                nums[++idx1] = nums[idx2++];
                cnt = 0;
            }
        }

        return idx1 + 1;
    }
};

// elegant top rank solution: Anonymous
class SolutionTop
{
public:
    int removeDuplicates(vector<int> &nums)
    {
        int i = 0; // one pointer
        for (auto ele : nums)
        {
            if (i == 0 || i == 1 || nums[i - 2] != ele)
            {
                nums[i] = ele;
                i++;
            }
        }
        return i;
    }
};