#include <vector>
#include <algorithm>

using namespace std;

// find the dual: difference array; using Kadane’s Algorithm to find Maximum subarray
class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        const size_t len = prices.size();
        int max_profit = 0;
        int current_profit = 0;

        for (size_t i = 0; i < len - 1; i++)
        {
            int diff = prices[i + 1] - prices[i];

            current_profit = max(diff, current_profit + diff);
            max_profit = max(current_profit, max_profit);
        }
        return (max_profit);
    }
};