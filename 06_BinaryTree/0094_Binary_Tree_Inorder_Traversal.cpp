/**
 * @file 094_Binary_Tree_Inorder_Traversal.cpp
 * @brief 94. 二叉树的中序遍历
 * 
 * @algorithm 递归 (Recursion)
 * @time_complexity O(N) - 每个节点访问一次
 * @space_complexity O(H) - H 为树的高度。最坏 O(N)，最好 O(log N)
 */

#include <vector>

using namespace std;

// 题目提供的标准定义
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        vector<int> result;
        traversal(root, result);
        return result;
    }

private:
    // 【侯捷提示】：使用引用传递 vector，避免每一层递归都发生昂贵的内存拷贝
    void traversal(TreeNode* curr, vector<int>& res) {
        // 1. 终止条件（刹车）：当前节点为空，说明到底了，回溯
        if (curr == nullptr) return;

        // 2. 递归逻辑：左 -> 根 -> 右
        traversal(curr->left, res);  // 左
        res.push_back(curr->val);    // 根（处理当前节点）
        traversal(curr->right, res); // 右
    }
};