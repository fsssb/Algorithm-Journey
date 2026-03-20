/**
 * @file 234_Palindrome_Linked_List.cpp
 * @brief 234. 回文链表
 * @link https://leetcode.cn/problems/palindrome-linked-list/
 * 
 * @algorithm 快慢指针 + 链表反转 (The O(1) Space King)
 * 
 * @time_complexity O(N) 
 * @space_complexity O(1) - 不开辟额外空间，原地拆解合并。
 * 
 * @note 核心战术：
 * 1. 找中点：用快慢指针，快的一下走两步，慢的一下走一步。当快指针到头，慢指针正好在中点。
 * 2. 局部翻转：把链表的【后半段】直接反转（复用 206 题的代码逻辑）。
 * 3. 对比：从头节点和反转后的后半段头节点开始比对，数值全等即为回文。
 * 4. 恢复原状（可选但专业）：面试官很看重你是否会把别人的数据结构弄乱，对比完最好再转回来。
 */
struct ListNode{
    int val;
    ListNode* next;

    ListNode(int x): val(x),next(nullptr){}
};

class Solution {
public:
    bool isPalindrome(ListNode* head) {
        if (head == nullptr || head->next == nullptr) return true;

        // 1. 寻找前半部分链表的尾节点 (快慢指针)
        ListNode* firstHalfEnd = endOfFirstHalf(head);
        
        // 2. 反转后半部分链表 (复用 206 题逻辑)
        ListNode* secondHalfStart = reverseList(firstHalfEnd->next);

        // 3. 判断是否回文
        ListNode* p1 = head;
        ListNode* p2 = secondHalfStart;
        bool result = true;
        while (result && p2 != nullptr) {
            if (p1->val != p2->val) result = false;
            p1 = p1->next;
            p2 = p2->next;
        }        

        // 4. 还原链表 (体现工程素养：不要留下副作用)
        firstHalfEnd->next = reverseList(secondHalfStart);
        
        return result;
    }

private:
    // 辅助函数：快慢指针找中点
    ListNode* endOfFirstHalf(ListNode* head) {
        ListNode* fast = head;
        ListNode* slow = head;
        // 快指针走两步，慢指针走一步
        while (fast->next != nullptr && fast->next->next != nullptr) {
            fast = fast->next->next;
            slow = slow->next;
        }
        return slow;
    }

    // 辅助函数：反转链表 (206 题逻辑)
    ListNode* reverseList(ListNode* head) {
        ListNode* prev = nullptr;
        ListNode* curr = head;
        while (curr != nullptr) {
            ListNode* nextTemp = curr->next;
            curr->next = prev;
            prev = curr;
            curr = nextTemp;
        }
        return prev;
    }
};