// check all possible min_len: bad complexity O(n^2)
// sliding window, bug, to will go beyond the to
#include <vector>
#include <iterator>
#include <iostream>
#include <algorithm>
using namespace std;

// complexity problem O(C(n)*n^2)?
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

// complexity problem O(C(n)*n, backtracking algo, decision tree, DFS
class Solution
{
private:
    void backtrack(vector<string> &res, string &cur, size_t open, size_t close, size_t n)
    {
        // base case, copy cur to a list
        if (cur.size() == 2 * n)
        {
            res.push_back(cur);
        }

        if (open < n)
        {
            cur.push_back('(');
            backtrack(res, cur, open + 1, close, n);
            cur.pop_back();
        }

        if (close < open)
        {
            cur.push_back(')');
            backtrack(res, cur, open, close + 1, n);
            cur.pop_back();
        }
    }

public:
    vector<string> generateParenthesis(int n)
    {
        vector<string> res;
        size_t open = 0;
        size_t close = 0;

        string cur;
        backtrack(res, cur, open, close, n);
        return res;
    }
};