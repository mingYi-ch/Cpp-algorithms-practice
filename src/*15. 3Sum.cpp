#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
using namespace std;

class Solution
{
public:
    vector<vector<int>> threeSum(vector<int> &nums)
    {
        sort(nums.begin(), nums.end());
        int *pt1 = nums.data();
        int *pt2 = nums.data() + 1;
        int *pt3 = nums.data() + 2;

        int *end = nums.data() + nums.size();

        vector<vector<int>> res;
        int sum = -1;
        // sum is the the smallest here
        while (pt1 < end - 2)
        {
            sum = *pt1 + *pt2 + *pt3;
            if (sum >= 0)
            {
                if (sum == 0)
                {
                    res.push_back({*pt1, *pt2, *pt3});
                }
                return res;
            }

            while (pt2 < end - 1 && pt3 < end)
            {
                if (*pt3 == -4 && *pt1 == -5)
                {
                    cout << "pt1 == -5" << endl;
                }

                sum = *pt1 + *pt2 + *pt3;
                if (sum >= 0 || pt3 == end - 1)
                {
                    if (sum == 0)
                    {
                        res.push_back({*pt1, *pt2, *pt3});
                    }

                    ++pt2;
                    while (pt2 < end - 1 && *pt2 == *(pt2 - 1))
                        ++pt2;
                    pt3 = pt2 + 1;
                }
                else
                {
                    ++pt3;
                    while (pt3 < end && *pt3 == *(pt3 - 1))
                        ++pt3;
                    if (pt3 == end)
                    {
                        ++pt2;
                        while (pt2 < end - 1 && *pt2 == *(pt2 - 1))
                            ++pt2;
                        pt3 = pt2 + 1;
                    }
                }
            }

            // check new combinations
            ++pt1;
            while (pt1 < end - 2 && *pt1 == *(pt1 - 1))
                ++pt1;
            pt2 = pt1 + 1;
            pt3 = pt2 + 1;
        }

        return res;
    }
};

void testThreeSum()
{
    // Test case: [2, -3, 0, -2, -5, -5, -4, 1, 2, -2, 2, 0, 2, -4, 5, 5, -10]
    vector<int> testCase = {2, -3, 0, -2, -5, -5, -4, 1, 2, -2, 2, 0, 2, -4, 5, 5, -10};
    // testCase = {0, 0, 0, 0};
    // Create a Solution object and get the result.
    Solution sol;
    vector<vector<int>> result = sol.threeSum(testCase);

    // Print the sorted input for clarity.
    vector<int> sortedTestCase = testCase;
    sort(sortedTestCase.begin(), sortedTestCase.end());
    cout << "Sorted input: ";
    for (int num : sortedTestCase)
        cout << num << " ";
    cout << "\n\n";

    // Print the results.
    cout << "ThreeSum results for the test case:" << endl;
    for (const auto &triplet : result)
    {
        cout << "[";
        for (size_t i = 0; i < triplet.size(); ++i)
        {
            cout << triplet[i] << (i < triplet.size() - 1 ? ", " : "");
        }
        cout << "]" << endl;
    }
}

int main()
{
    testThreeSum();
    return 0;
}
