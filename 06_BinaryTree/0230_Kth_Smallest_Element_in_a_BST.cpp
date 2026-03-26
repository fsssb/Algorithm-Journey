/**
 * @file 0230_Kth_Smallest_Element_in_a_BST.cpp
 * @brief 230. 二叉搜索树中第K小的元素
 * @link https://leetcode.cn/problems/kth-smallest-element-in-a-bst/
 * 
 * @algorithm 中序遍历 (In-order Traversal)
 * @time_complexity O(H + k) 
 *      - H 是树的高度。我们需要先钻到最左侧叶子节点（O(H)），然后遍历 k 个节点。
 *      - 最坏情况下（k=N 且树退化为链表）为 O(N)。
 * @space_complexity O(H) 
 *      - 递归栈或手动维护的栈空间，取决于树的高度。
 * 
 * @note 核心思路：
 * 1. BST 的物理特性：中序遍历（左-根-右）的结果是一个严格递增的序列。
 * 2. 任务转化：寻找第 k 小的元素，本质上就是寻找中序遍历序列中的第 k 个节点。
 * 3. 优化策略：不需要遍历整棵树。一旦计数器达到 k，立即触发“提前返回（Early Return）”，停止所有递归动作。
 */

#include <stack>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    /**
     * @brief 迭代解法 (推荐：逻辑控制更精准)
     * Cherno 视角：手动管理栈可以更方便地实现 break，且对内存监控更友好。
     */
    int kthSmallest(TreeNode* root, int k) {
        stack<TreeNode*> st;
        TreeNode* curr = root;

        while (curr != nullptr || !st.empty()) {
            // 1. 一路向左钻到底，压入路径上的所有根节点
            while (curr != nullptr) {
                st.push(curr);
                curr = curr->left;
            }

            // 2. 触底回溯：弹出当前最小的节点
            curr = st.top();
            st.pop();
            
            // 3. 计数逻辑
            if (--k == 0) {
                return curr->val; // 找到第 k 个，直接返回
            }

            // 4. 转向右子树
            curr = curr->right;
        }
        return -1; // 理论上不会走到这里
    }
};