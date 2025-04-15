#include <vector>
#include <array>
#include <iostream>
#include <algorithm>
using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    vector<double> averageOfLevels(TreeNode *root)
    {
        vector<double> avgs;
        vector<TreeNode *> level_node = {root};
        double level_avg;

        while (!level_node.empty())
        {
            vector<TreeNode *> next;
            double sum = 0;

            int size = level_node.size();
            while (!level_node.empty())
            {
                TreeNode *node = level_node.back();
                level_node.pop_back();

                if (node->left != nullptr)
                {
                    next.push_back(node->left);
                }

                if (node->right != nullptr)
                {
                    next.push_back(node->right);
                }
                sum += node->val;
            }
            avgs.push_back(sum / size);
            level_node = next;
        }
        return avgs;
    }
};