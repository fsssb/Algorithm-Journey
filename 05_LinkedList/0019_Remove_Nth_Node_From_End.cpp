/**
 * @file 019_Remove_Nth_Node_From_End.cpp
 * @brief 19. 删除链表的倒数第 N 个结点
 * @link https://leetcode.cn/problems/remove-nth-node-from-end-of-list/
 * 
 * @algorithm 双指针 (快慢指针) + 虚拟头节点 (Dummy Node)
 * 
 * @time_complexity O(L) - L 为链表长度，仅遍历一遍。
 * @space_complexity O(1) - 仅使用了常数个额外指针。
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // 1. 创建虚拟头节点 (栈分配，Cherno 推荐的高性能写法)
        // 作用：如果删除的是原链表的第一个节点，dummy 可以让我们像处理普通节点一样处理它
        ListNode dummy(0, head);
        ListNode* fast = &dummy;
        ListNode* slow = &dummy;

        // 2. 快指针先走 n + 1 步
        // 为什么要多走 1 步？
        // 因为我们要让 slow 停在被删除节点的前一个位置，这样才好执行删除操作。
        for (int i = 0; i <= n; i++) {
            fast = fast->next;
        }

        // 3. 两个指针同步移动，直到 fast 走到尽头
        while (fast != nullptr) {
            fast = fast->next;
            slow = slow->next;
        }

        // 4. 【核心时刻】：执行删除操作
        // 此时 slow->next 是我们要删除的那个节点
        ListNode* nodeToDelete = slow->next;
        slow->next = slow->next->next;

        // 5. 【工业级要求：手动管理内存】 (面试官最看重的一笔！)
        // 在 C++ 中，如果我们不 delete 被删掉的节点，那块堆内存就永远泄露了。
        delete nodeToDelete;
        nodeToDelete = nullptr;

        // 6. 返回真正头节点
        return dummy.next;
    }
};