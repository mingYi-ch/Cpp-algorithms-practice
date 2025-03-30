#include <vector>
#include <iostream>

using namespace std;

// 3 pointers
class SolutionGPT
{
public:
    void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
    {
        // Start from the end of both arrays
        int16_t idx1 = m - 1;          // Pointer for nums1
        int16_t idx2 = n - 1;          // Pointer for nums2
        int16_t idxMerged = m + n - 1; // Pointer for the last element in nums1 (merged array)

        // Merge the two arrays starting from the end
        while (idx1 >= 0 && idx2 >= 0)
        {
            if (nums1[idx1] > nums2[idx2])
            {
                nums1[idxMerged--] = nums1[idx1--];
            }
            else
            {
                nums1[idxMerged--] = nums2[idx2--];
            }
        }

        // If there are remaining elements in nums2, copy them over
        while (idx2 >= 0)
        {
            nums1[idxMerged--] = nums2[idx2--];
        }

        // No need to do anything for nums1 since it is already in place
    }
};

// 2 pointers
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
            int idx2 = n - 1; // end of vector nums2
            for (int idx1 = m - 1; idx1 >= 0; idx1--)
            {
                while (idx2 >= 0 && nums1[idx1] <= nums2[idx2])
                {
                    nums1.pop_back();
                    nums1.insert(nums1.begin() + idx1 + 1, nums2[idx2]);
                    --idx2;
                }

                // the start of nums1
                if (idx1 == 0 && idx2 >= 0)
                {
                    nums1.resize(m + n - idx2 - 1);                                       // remove ending 0s
                    nums1.insert(nums1.begin(), nums2.begin(), nums2.begin() + idx2 + 1); // idx2 + 1 is the count to be inserted
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
