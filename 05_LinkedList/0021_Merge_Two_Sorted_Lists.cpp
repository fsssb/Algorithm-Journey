/**
 * @file 021_Merge_Two_Sorted_Lists.cpp
 * @brief 21. 合并两个有序链表
 * @link https://leetcode.cn/problems/merge-two-sorted-lists/
 * 
 * @algorithm 迭代法 + 虚拟头节点 (Dummy Node)
 * 
 * @time_complexity O(N + M) - N, M 分别为两个链表的长度。
 * @space_complexity O(1) - 仅使用了常数个指针，原地修改结构。
 * 
 * @note 核心战术：
 * 1. 建立 dummy 节点：在栈上分配，自动回收内存。
 * 2. 尾插法：用一个 tail 指针时刻指向新链表的末尾。
 * 3. 链表特有的收尾：如果其中一个链表先走完，不需要遍历剩下的，直接把指针连过去即可。
 */
struct ListNode{
    int val;
    ListNode* next;

    ListNode(int x) : val(x),next(nullptr){}

};

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode dummy(0);  //虚拟头节点
        ListNode* tail = &dummy;  //用tail去处理后面的链表，避免dummy被修改，最后没法返回完整的链表

        while(list1 && list2)
        {
            if(list1->val <= list2->val)
            {
                tail->next = list1;
                list1 = list1->next;
            }
            else
            {
                tail->next = list2;
                list2 = list2->next;
            }
            tail = tail->next;
        }

        tail->next = list1? list1:list2;

        return dummy.next;
    }
};