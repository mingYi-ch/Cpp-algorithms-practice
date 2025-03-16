#include <string>
using namespace std;

class Solution
{
public:
    bool isSubsequence(string s, string t)
    {
        size_t pt1 = 0;
        size_t pt2 = 0;

        size_t len_s = s.size();
        size_t len_t = t.size();

        while (pt1 < len_s && pt2 < len_t)
        {
            if (s[pt1] == t[pt2])
            {
                ++pt1;
            }
            ++pt2;
        }
        if (pt1 == len_s)
        {
            return (true);
        }
        return (false);
    }
};