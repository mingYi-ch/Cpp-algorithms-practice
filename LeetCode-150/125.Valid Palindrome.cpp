#include <string>
using namespace std;

class Solution
{
public:
    bool isPalindrome(string s)
    {
        // erase non alnum, from end TODO: can be optimized, no erasing, only checking
        for (int i = s.length() - 1; i >= 0; i--)
        {
            if (!isalnum(s[i]))
            {
                s.erase(i, 1);
            }
        }

        int pt1 = 0;
        int pt2 = s.length() - 1;

        // when length == 0 , pt1 == pt2 doesn't work
        while (pt1 < pt2)
        {
            if (tolower(s[pt1++]) != tolower(s[pt2--]))
            {
                return (false);
            }
        }
        return true;
    }
};