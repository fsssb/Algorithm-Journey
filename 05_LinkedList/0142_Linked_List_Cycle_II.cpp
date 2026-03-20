/**
 * @file 142_Linked_List_Cycle_II.cpp
 * @brief 142. 环形链表 II
 * @link https://leetcode.cn/problems/linked-list-cycle-ii/
 * 
 * @algorithm 快慢指针 + 几何推导 (Floyd's Cycle-Finding Algorithm)
 * 
 * @time_complexity O(N) 
 *      - 第一阶段快慢指针相遇最多遍历 N 次。
 *      - 第二阶段寻找入口最多遍历 N 次。
 * @space_complexity O(1)
 *      - 仅使用了两个临时指针变量。
 * 
 * @note 核心思路：
 * 1. 阶段一：fast 走 2，slow 走 1。若相遇，证明有环，且此时 slow 走了 L+X。
 * 2. 阶段二：保持 slow 在相遇点，将 fast 放回 head。两人以速度 1 同步前进。
 * 3. 结果：由公式 L = (n-1)C + (C-X) 可知，两人必在环入口处相遇。
 */
#include <unordered_set>
using namespace std;
struct ListNode{

    int val;
    ListNode* next;

    ListNode(int x) : val(x),next(nullptr){}
};

class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        if (!head || !head->next) return nullptr;

        ListNode* fast = head;
        ListNode* slow = head;

        // 1. 判环：快慢指针套圈
        while (fast && fast->next) {
            fast = fast->next->next;
            slow = slow->next;
            if (fast == slow) break; // 发现相遇点
        }

        // 核心检查：是因为循环到头了，还是因为撞上了？
        if (!fast || !fast->next) return nullptr;

        // 2. 找入口：双指针同速前进
        fast = head; // 快指针回起点
        while (fast != slow) {
            fast = fast->next;
            slow = slow->next;
        }

        return fast; // 此时 fast == slow，即入口点
    }
};

//采用哈希表直接记录
class Solution_1 {
public:
    ListNode *detectCycle(ListNode *head) {
        unordered_set<ListNode*> visited;
        while (head != nullptr) {
            if (visited.count(head)) {
                return head;
            }
            visited.insert(head);
            head = head->next;
        }
        return nullptr;
    }
};

