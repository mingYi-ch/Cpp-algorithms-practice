#include <vector>
#include <algorithm>
using namespace std;

/*
Definition for a binary tree node.
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
 */

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}      // constructer, Initializer List
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {} // overloaded
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution
{
public:
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        vector<vector<int>> res;

        if (root != nullptr)
        {
            vector<TreeNode *> now = {root};
            do
            {
                // define nested list
                vector<TreeNode *> next;
                vector<int> temp;

                for (const auto &node : now)
                {
                    if (node != nullptr)
                        temp.push_back(node->val);

                    if (node->left != nullptr)
                        next.push_back(node->left);

                    if (node->right != nullptr)
                        next.push_back(node->right);
                }

                res.push_back(temp);
                now = next;

            } while (now.size() != 0);
        }
        return (res);
    }
};