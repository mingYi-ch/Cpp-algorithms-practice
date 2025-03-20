#include <vector>
#include <algorithm>

using namespace std;

/*
greedy algo:1. optimal solution includes the greedy choices;
            2. optimal substructure
proof by induction
*/
class Solution
{
private:
    int subMaxProfit(vector<int> &prices, const int start, const int end)
    {
        if (start >= end)
            return (0);

        const size_t len = prices.size();
        int max_profit = 0;
        int current_profit = 0;

        // start and end idx of optimal subarray
        int pt1 = start;
        int pt2 = start;

        int pt1_current = start;
        int pt2_current = start;

        for (size_t i = start; i < end; i++) // i + 1 constraints
        {
            int diff = prices[i + 1] - prices[i];

            current_profit = max(diff, current_profit + diff);
            if (diff > current_profit + diff)
            {
                current_profit = diff;
                pt1_current = i;
                pt2_current = i + 1;
            }
            else
            {
                current_profit = diff + current_profit;
                pt2_current = i + 1;
            }

            max_profit = max(current_profit, max_profit);
            if (max_profit < current_profit)
            {
                pt1 = pt1_current;
                pt2 = pt2_current;
            }
        }
        return (max_profit + subMaxProfit(prices, start, pt1 - 1) + subMaxProfit(prices, pt2 + 1, end));
    }

public:
    int maxProfit(vector<int> &prices)
    {
        return (prices, 0, prices.size() - 1);
    }
};