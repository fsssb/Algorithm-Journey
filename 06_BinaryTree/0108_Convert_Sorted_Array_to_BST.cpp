/**
 * @file 0108_Convert_Sorted_Array_to_BST.cpp
 * @brief 108. 将有序数组转换为二叉搜索树
 * @link https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/
 * 
 * @algorithm 递归分治 (Divide and Conquer)
 * @time_complexity O(N) - 每个数组元素都被访问并构造为一个节点
 * @space_complexity O(log N) - 递归栈深度。由于生成的树是平衡的，高度严格控制在 log N
 * 
 * @note 核心思路：
 * 1. 平衡的关键：要构造高度平衡的 BST，根节点必须是数组的“中间元素”。
 * 2. 分治策略：
 *    - 取数组中点作为根节点。
 *    - 中点左侧子数组递归构造左子树。
 *    - 中点右侧子数组递归构造右子树。
 * 3. 边界控制：使用左闭右闭区间 [left, right]，当 left > right 时递归终止。
 */

#include <vector>

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
    TreeNode* sortedArrayToBST(vector<int>& nums) {
        // 显式调用辅助递归函数，传递下标区间而非子数组
        return buildBST(nums, 0, nums.size() - 1);
    }

private:
    /**
     * @brief 核心构建逻辑
     * Cherno 视角：通过下标传递避免了昂贵的 vector 拷贝（Slicing）开销。
     */
    TreeNode* buildBST(const vector<int>& nums, int left, int right) {
        // 1. 终止条件：区间无效
        if (left > right) return nullptr;

        // 2. 寻找中点
        // 技巧：(left + right) / 2 在极大数据量下可能溢出，left + (right - left) / 2 更稳健
        int mid = left + (right - left) / 2;

        // 3. 创建根节点（堆内存分配）
        // 侯捷提示：此处触发 operator new，分配 24/32 字节空间并执行构造函数
        TreeNode* root = new TreeNode(nums[mid]);

        // 4. 递归构建左右子树
        root->left = buildBST(nums, left, mid - 1);
        root->right = buildBST(nums, mid + 1, right);

        return root;
    }
};