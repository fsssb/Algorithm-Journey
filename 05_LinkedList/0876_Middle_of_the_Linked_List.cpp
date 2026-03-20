/**
 * @file 876_Middle_of_the_Linked_List.cpp
 * @brief 876. 链表的中间结点
 * @link https://leetcode.cn/problems/middle-of-the-linked-list/
 * 
 * @algorithm 快慢指针 (Two Pointers / Fast & Slow Pointers)
 * 
 * @time_complexity O(N) 
 *      - 快指针走完整个链表，慢指针走一半。总共遍历一遍。
 * @space_complexity O(1)
 *      - 仅使用了两个指针变量。
 * 
 * @note 核心思路 (套圈法)：
 * 1. 设定两个指针 slow 和 fast，初始都指向 head。
 * 2. 规则：slow 每次走 1 步，fast 每次走 2 步。
 * 3. 结果：由于 fast 的速度是 slow 的两倍，当 fast 走到终点时，slow 正好在路程的一半位置。
 * 
 * @note 边界控制 (面试官最关心的点)：
 * - 奇数长度 (1-2-3-4-5)：fast 最终停在 5，slow 停在 3。
 * - 偶数长度 (1-2-3-4-5-6)：fast 最终停在 nullptr，slow 停在 4。
 *   题目要求：如果有两个中间结点，返回第二个。快慢指针天然符合这个要求。
 */
struct ListNode
{
    int val;
    ListNode* next;

    ListNode(int x) : val(x),next(nullptr){}
};

class Solution{

public:
    ListNode* middleNode(ListNode* head)
    {
        //边界防御
        if(head == nullptr || head->next == nullptr) return head;

        ListNode* fast = head;
        ListNode* slow = head;
        
        while(fast != nullptr && fast->next != nullptr)
        {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }
};