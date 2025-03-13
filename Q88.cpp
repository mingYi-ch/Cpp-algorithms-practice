#include <vector>
#include <iostream>

using namespace std;

// TODO: try insert from end to save space without copy
class Solution
{
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
        if (m == 0)
        {
            nums1 = nums2;
        }
        else if (n == 0)
        {
            ;
        }
        else
        {
            vector<int> nums1_copy = nums1;
            size_t j = 0;
            for (size_t i = 0; i < m; i++)
            {
                while (j < n && nums1_copy[i] >= nums2[j])
                {
                    nums1.pop_back();
                    nums1.insert(nums1.begin() + j + i, nums2[j]);
                    ++j;
                }

                // the end of nums1
                if (i == m - 1 && j != n)
                {
                    nums1.resize(m + j);                                       // j elem inserted
                    nums1.insert(nums1.end(), nums2.begin() + j, nums2.end()); // Append elements from nums2[j:n]
                }
            }
        }
    }
};

void printVector(const vector<int> &vec)
{
    for (int num : vec)
    {
        cout << num << " ";
    }
    cout << endl;
}

int main()
{
    Solution solution;

    // Test Case 1
    vector<int> nums1 = {1, 2, 3, 0, 0, 0};
    vector<int> nums2 = {2, 5, 6};
    int m = 3, n = 3;

    cout << "Before merge:" << endl;
    printVector(nums1);

    solution.merge(nums1, m, nums2, n);

    cout << "After merge:" << endl;
    printVector(nums1); // Expected: 1 2 2 3 5 6

    // Test Case 2: nums1 is empty
    vector<int> nums3 = {2, 0};
    vector<int> nums4 = {1};
    m = 1, n = 1;

    cout << "\nBefore merge:" << endl;
    printVector(nums3);

    solution.merge(nums3, m, nums4, n);

    cout << "After merge:" << endl;
    printVector(nums3); // Expected: 1

    // Test Case 3: nums2 is empty
    vector<int> nums5 = {1, 2, 3};
    vector<int> nums6 = {};
    m = 3, n = 0;

    cout << "\nBefore merge:" << endl;
    printVector(nums5);

    solution.merge(nums5, m, nums6, n);

    cout << "After merge:" << endl;
    printVector(nums5); // Expected: 1 2 3

    return 0;
}
