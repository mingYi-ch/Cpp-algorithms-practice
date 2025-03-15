
#include <vector>
using namespace std;

class Solution
{
public:
    int removeElement(vector<int> &nums, int val)
    {
        size_t len = size(nums);
        size_t cnt = 0;
        for (size_t i = 0; i < len; i++)
        {
            if (nums[i] != val)
            {
                // put value to the head
                nums[cnt++] = nums[i];
            }
        }
        return (cnt);
    }
};