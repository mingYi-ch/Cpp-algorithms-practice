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

/*
Floyd's Cycle-Finding Algorithm:
 (x1 + 2t) mod n , (x2 + t) mod n, when they are equal slow and fast will meet;
 ((x1 + 2t) - (x2 + t) ) mod n
*/

class Solution
{
public:
    bool hasCycle(ListNode *head)
    {
        if (head == nullptr || head->next == nullptr)
        {
            return false;
        }

        ListNode *slow = head;
        ListNode *fast = head->next->next;

        while (slow != fast)
        {
            if (fast == nullptr || slow == nullptr || fast->next == nullptr)
            {
                return false;
            }
            else
            {
                slow = slow->next;
                fast = fast->next->next;
            }
        }
        return true;
    }
};