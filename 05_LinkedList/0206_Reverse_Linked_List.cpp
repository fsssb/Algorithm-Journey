#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode* next;

    ListNode(int x) : val(x),next(nullptr){}
};

class Solution{
public:
    ListNode* reverseListNode(ListNode* head){
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while(curr){
            ListNode* tmp = curr->next;

            curr->next = prev;
            curr = tmp;
        }
        return prev;
    }
};

