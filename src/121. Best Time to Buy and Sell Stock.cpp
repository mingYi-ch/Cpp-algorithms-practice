#include <vector>
#include <algorithm>

using namespace std;

/*
    consider the diff array, pick the positive; can sell and buy on the same day!
*/
class Solution
{

public:
    int maxProfit(vector<int> &prices)
    {
        int max_profit = 0;
        for (size_t i = 0; i < prices.size() - 1; i++)
        {
            if (prices[i + 1] > prices[i])
                max_profit += prices[i + 1] - prices[i];
        }

        return max_profit;
    }
};