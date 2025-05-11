#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

class Solution
{
public:
    bool canConstruct(string ransomNote, string magazine)
    {
        // unordered_map<char, int> map_ransom = stringToHash(ransomNote);
        unordered_map<char, int> map_magazine = stringToHash(magazine);
        for (const char &c : ransomNote)
        {
            if (map_magazine[c] == 0)
            {
                return false;
            }
            map_magazine[c]--;
        }
        return true;
    }

private:
    unordered_map<char, int> stringToHash(string &target)
    {
        unordered_map<char, int> map;
        for (const char &c : target)
        {
            map[c] += 1; // If key exists, increment; if not, key is auto-initialized to 0 and then incremented
        }
        return map;
    }
};

int main()
{
    Solution solution;
    cout << boolalpha; // Print "true"/"false" instead of 1/0

    // Test cases
    cout << "Test 1: " << solution.canConstruct("aaaaaaa", "") << endl;   // false
    cout << "Test 2: " << solution.canConstruct("aa", "ab") << endl;      // false
    cout << "Test 3: " << solution.canConstruct("aa", "aab") << endl;     // true
    cout << "Test 4: " << solution.canConstruct("hello", "lloh") << endl; // true

    return 0;
}
