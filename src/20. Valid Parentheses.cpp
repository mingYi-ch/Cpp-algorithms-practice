#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
public:
    bool isValid(string s)
    {
        vector<char> brackets = {'(', '[', '{', ')', ']', '}'};

        unordered_map<char, char> brackets_map;
        for (size_t i = 0; i < 3; i++)
        {
            brackets_map[brackets[i]] = brackets[i + 3];
        }

        string s_cp;

        for (auto it = s.rbegin(); it != s.rend(); it++)
        {
            if (!s_cp.empty() && s_cp.back() == brackets_map[*it])
            {
                s_cp.pop_back();
            }
            else
            {
                s_cp += *it;
            }
        }
        return s_cp.size() == 0 ? true : false;
    }
};