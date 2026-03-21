/**
 * @file 024_Swap_Nodes_in_Pairs.cpp
 * @brief 24. 两两交换链表中的节点
 * @link https://leetcode.cn/problems/swap-nodes-in-pairs/
 * 
 * @algorithm 迭代法 + 虚拟头节点 (Dummy Node)
 * 
 * @time_complexity O(N) - 只遍历一遍链表。
 * @space_complexity O(1) - 原地交换。
 * 
 * @note 核心战术：
 * 1. 为什么需要 prev？因为交换 3 和 4 时，你必须让 2 的 next 指向 4。
 * 2. 为什么需要 dummy？因为你要交换 1 和 2，你必须有一个虚拟的 0 节点，让 0 的 next 指向 2。
 * 3. 交换步骤 (假设 prev -> node1 -> node2 -> next_pair)：
 *    a) prev->next = node2;  (0 连 2)
 *    b) node1->next = node2->next; (1 连 3)
 *    c) node2->next = node1; (2 连 1)
 *    d) prev 向后移动两步，准备下一轮。
 */

//  Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};
 

class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode dummy(0);
        dummy.next = head;   //将链表挂载

        ListNode* prev = &dummy;

        while(prev->next && prev->next->next)
        {
            ListNode* node1 = prev->next;
            ListNode* node2 = prev->next->next;

            //开始交换
            prev->next = node2;
            node1->next = node2->next;
            node2->next = node1; //注意交换的先后顺序。保证节点不会两头空！

            //平移节点！
            prev = node1;
        }

        return dummy.next; 
    }
};

