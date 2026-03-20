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
    ListNode* reverseListNode(ListNode* head)
    {
        ListNode* prev = nullptr;
        ListNode* curr = head;

        while(curr)
        {
            //先存下一个节点，避免丢失
            ListNode* temp = curr->next;
            //调转指向
            curr->next = prev;
            //整体平移
            prev = curr;
            curr = temp;
        }
        return prev;
    }
};

//时间复杂度：O（N）
//空间复杂度：O（1）