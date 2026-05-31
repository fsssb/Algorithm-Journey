/**
 * @file 0148_Sort_List.cpp
 * @brief 148. 排序链表
 * @link https://leetcode.cn/problems/sort-list/
 *
 * @algorithm 归并排序 (Merge Sort - Top Down)
 * @time_complexity O(N log N)
 * @space_complexity O(log N) - 递归调用栈空间
 *
 * @note 核心思路：
 * 1. 递归终止条件：当链表为空或仅含一个节点时，已然有序，直接返回。
 * 2. 分治 (Divide)：利用快慢双指针（slow 走 1 步，fast 走 2 步）定位中点。
 *    引入 prev 指针紧跟 slow，在中点前半程的末尾执行 prev->next = nullptr 断开，平分成左右子链表。
 * 3. 递归排序 (Sort)：分别对左右两半部分递归调用排序。
 * 4. 合并 (Merge)：运用哨兵节点 (Dummy Node) 技巧将两个排好序的单链表融合成一个。
 *
 * 进阶提示：自顶向下的递归会产生 O(log N) 的调用栈开销。若追求极致的常数级 O(1) 空间，
 * 则需要采用自底向上（Bottom-up）的迭代法。但自顶向下的写法逻辑最为精简、面试通过率极高。
 */

#include <bits/stdc++.h>
using namespace std;

// LeetCode 内置单链表节点定义
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* sortList(ListNode* head) {
        // 边界条件：空链表或单节点，直接返回
        if (!head || !head->next) {
            return head;
        }

        ListNode* prev = nullptr;
        ListNode* slow = head;
        ListNode* fast = head;

        // 快慢指针移动：fast 到尾部时，slow 正好到中点
        while (fast && fast->next) {
            prev = slow;
            slow = slow->next;
            fast = fast->next->next;
        }

        // 在中点的前驱节点处一刀切断，分成两个独立链表
        prev->next = nullptr;
        

        // 分治：递归对左右两边各自进行排序
        ListNode* left = sortList(head);
        ListNode* right = sortList(slow);

        // 合并：将两个有序子链表进行有序交融
        return merge(left, right);
    }

private:
    // 辅助函数：合并两个有序单链表（哨兵节点法）
    ListNode* merge(ListNode* list1, ListNode* list2) {
        // 使用局部栈变量 dummy 避免动态内存分配开销，保障内存安全
        ListNode dummy(0);
        ListNode* curr = &dummy;

        while (list1 && list2) {
            if (list1->val < list2->val) {
                curr->next = list1;
                list1 = list1->next;
            } else {
                curr->next = list2;
                list2 = list2->next;
            }
            curr = curr->next;
        }

        // 拼接仍有剩余的非空单链表
        curr->next = list1 ? list1 : list2;

        return dummy.next;
    }
};