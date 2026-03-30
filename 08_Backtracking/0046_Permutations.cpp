/**
 * @file 0046_Permutations.cpp
 * @brief 46. 全排列
 * @link https://leetcode.cn/problems/permutations/
 * 
 * @algorithm 回溯 (Backtracking)
 * @time_complexity O(n * n!) - n 个元素全排列有 n! 种，每种解拷贝需要 O(n)
 * @space_complexity O(n) - 递归栈深度和 path 存储开销
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> permute(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path;
        // used 数组：记录哪些元素已被放入路径，避免重复选择
        vector<bool> used(nums.size(), false);
        
        backtracking(nums, used, path, result);
        return result;
    }

private:
    void backtracking(const vector<int>& nums, vector<bool>& used, 
                      vector<int>& path, vector<vector<int>>& result) {
        // 1. 终止条件：路径长度等于数组长度，说明找到一个解
        if (path.size() == nums.size()) {
            // 发生一次深拷贝，将 path 内容转移至结果集
            result.push_back(path);
            return;
        }

        // 2. 遍历选择列表
        for (int i = 0; i < nums.size(); ++i) {
            // 如果该元素已被使用，跳过（本层剪枝）
            if (used[i]) continue;

            // --- 关键：修改现场 ---
            used[i] = true;
            path.push_back(nums[i]);

            // --- 递归：深入下一层 ---
            backtracking(nums, used, path, result);

            // --- 核心：恢复现场 (回溯) ---
            // 撤销刚才的操作，让当前循环能尝试 nums[i+1]
            path.pop_back();
            used[i] = false;
        }
    }
};