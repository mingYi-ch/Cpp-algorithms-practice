/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <unordered_map>
#include <string>
#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        unordered_map<ListNode *, bool> cnt;
        ListNode *cur = head;

        cnt[head] = true;
        while (cur != NULL)
        {
            cur = cur->next;
            if (cnt[cur])
            {
                return true;
            }
            else
            {
                cnt[cur] = true;
            }
        }
        return false;
    }
};