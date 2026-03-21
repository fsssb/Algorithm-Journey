/**
 * @file 138_Copy_List_with_Random_Pointer.cpp
 * @brief 138. 随机链表的复制
 * @link https://leetcode.cn/problems/copy-list-with-random-pointer/
 * 
 * @algorithm 节点分裂法 / 交织法 (Node Splitting / Interweaving)
 * 
 * @time_complexity O(N) - 遍历链表三次。
 * @space_complexity O(1) - 除了返回所需的新链表节点，不使用额外的哈希表空间。
 */

// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = nullptr;
        random = nullptr;
    }
};

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if (head == nullptr) return nullptr;

        // ==========================================
        // 阶段 1：克隆节点并交织挂载
        // 原链表：A -> B -> C
        // 现链表：A -> A' -> B -> B' -> C -> C'
        // ==========================================
        Node* curr = head;
        while (curr != nullptr) {
            Node* clone = new Node(curr->val);
            clone->next = curr->next;
            curr->next = clone;
            curr = clone->next; // 移动到下一个原节点
        }

        // ==========================================
        // 阶段 2：处理克隆节点的 random 指针
        // ==========================================
        curr = head;
        while (curr != nullptr) {
            Node* clone = curr->next;
            // 如果原节点的 random 不为空，克隆节点的 random 就是原节点 random 的 next
            if (curr->random != nullptr) {
                clone->random = curr->random->next;
            }
            curr = clone->next; // 跨过克隆节点，移动到下一个原节点
        }

        // ==========================================
        // 阶段 3：物理拆分（极其关键：必须恢复原链表！）
        // ==========================================
        curr = head;
        Node* cloneHead = head->next;
        Node* cloneCurr = cloneHead;

        while (curr != nullptr) {
            // 恢复原链表
            curr->next = curr->next->next;
            
            // 链接新链表
            if (cloneCurr->next != nullptr) {
                cloneCurr->next = cloneCurr->next->next;
            }

            // 同步后移
            curr = curr->next;
            cloneCurr = cloneCurr->next;
        }

        return cloneHead;
    }
};


