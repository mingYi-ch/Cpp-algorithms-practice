// check all possible min_len: bad complexity O(n^2)
// sliding window, bug, to will go beyond the to
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution
{
private:
    void generateParenthesis_sub(vector<string> &comb, string indicators)
    {
        if (indicators.find('_') == string::npos)
        {
            comb.push_back(indicators);
        }
        else
        {
            for (size_t i = 0; i < indicators.size() - 1; i++)
            {

                if (indicators[i] == '_') // left (
                {
                    for (size_t j = i + 1; j < indicators.size(); j++)
                    {
                        if (indicators[j] == '_') // right (
                        {
                            string indicators_cp = indicators;
                            indicators_cp[i] = '(';
                            indicators_cp[j] = ')';
                            generateParenthesis_sub(comb, indicators_cp);
                        }
                    }
                }
            }
        }
    }

public:
    vector<string> generateParenthesis(int n)
    {
        string str = string(2 * n, '_');
        vector<string> res;

        generateParenthesis_sub(res, str);
        sort(res.begin(), res.end());
        auto last = unique(res.begin(), res.end());
        res.erase(last, res.end());
        return res;
    }
};