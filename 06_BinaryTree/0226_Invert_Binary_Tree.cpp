/**
 * @file 0226_Invert_Binary_Tree.cpp
 * @brief 226. 翻转二叉树
 * @link https://leetcode.cn/problems/invert-binary-tree/
 * 
 * @algorithm 递归 DFS (前序遍历) / 迭代 BFS
 * @time_complexity O(N) - 每个节点必须且仅访问一次
 * @space_complexity O(H) - H 为树的高度。最坏情况（退化成链表）为 O(N)，平均为 O(log N)
 * 
 * @note 核心思路：
 * 1. 翻转的物理本质：交换每个节点的 left 指针和 right 指针。
 * 2. 递归策略：先交换当前根节点的左右孩子，再递归地对左子树和右子树执行相同操作。
 * 3. 遍历顺序：本题使用前序（根左右）或后序（左右根）均可，但中序遍历会导致部分子树被翻转两次，逻辑失效。
 */

#include <algorithm> // std::swap
#include <queue>

using namespace std;

/**
 * Definition for a binary tree node.
 */
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    /**
     * @brief 递归解法 (DFS)
     * 侯捷视角：利用系统调用栈实现隐式回溯。
     */
    TreeNode* invertTree(TreeNode* root) {
        // 终止条件：触底（叶子节点的子节点）
        if (root == nullptr) return root;

        // 核心动作：交换左右指针（物理地址交换）
        // Cherno 视角：此处交换的是 8 字节的地址，而非搬运整个 TreeNode 对象
        swap(root->left, root->right);

        // 递归处理子树
        invertTree(root->left);
        invertTree(root->right);

        return root;
    }

    /**
     * @brief 迭代解法 (BFS)
     * 工业级建议：当树深度不可控时，使用此法防止 SIGSEGV (栈溢出)。
     */
    TreeNode* invertTree_Iterative(TreeNode* root) {
        if (!root) return nullptr;
        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();

            swap(node->left, node->right);

            if (node->left) q.push(node->left);
            if (node->right) q.push(node->right);
        }
        return root;
    }
};