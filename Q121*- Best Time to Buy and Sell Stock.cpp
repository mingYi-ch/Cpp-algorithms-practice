#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        size_t len = prices.size();
        int max_profit = 0;
        for (size_t i = 0; i < len; i++)
        {
            for (size_t j = i + 1; j < len; j++)
            {
                int profit = prices[j] - prices[i];
                if (profit > max_profit)
                {
                    max_profit = profit;
                }
            }
        }
        return (max_profit);
    }
};