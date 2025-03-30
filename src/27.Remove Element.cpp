
#include <vector>
using namespace std;

class Solution
{
public:
    int removeElement(vector<int> &nums, int val)
    {
        size_t cnt = 0;
        for (const int &elem : nums)
        {
            if (elem != val)
            {
                // put value to the head
                nums[cnt++] = elem;
            }
        }
        return cnt;
    }
};