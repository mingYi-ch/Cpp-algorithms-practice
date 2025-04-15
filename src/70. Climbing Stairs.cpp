#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
using namespace std;

/*
    think backwards: the last choice is either 1 step or 2 steps, the path of a tree to a leaf, O(2 ^ N)!! without memorize it
*/

class Solution
{

private:
    int subClimbStairs(int n, vector<int> &mem)
    {

        // reached the leaf
        if (n == 1)
        {
            return 1;
        }

        if (n == 2)
        {
            return 2;
        }

        if (mem[n] != -1)
        {
            return mem[n];
        }
        mem[n] = subClimbStairs(n - 1, mem) + subClimbStairs(n - 2, mem);
        return mem[n];
    }

public:
    int climbStairs(int n)
    {
        vector<int> mem(n + 1, -1); // n + 1 to include the n steps mem[n]
        return subClimbStairs(n, mem);
    }
};