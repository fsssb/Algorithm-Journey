/**
 * @file 0078_Subsets.cpp
 * @brief 78. 子集
 * @link https://leetcode.cn/problems/subsets/
 * 
 * @algorithm 回溯 (Backtracking)
 * @time_complexity O(n * 2^n) - 总共有 2^n 个子集，每个子集拷贝到结果集需要 O(n)
 * @space_complexity O(n) - 递归栈深度和临时路径 path 的开销
 * 
 * @note 核心思路：
 * 1. 决策树模型：子集问题与全排列不同，它是在集合中“取”元素。
 * 2. 收集时机：在全排列中我们只在叶子节点收集结果；在子集问题中，【决策树的每一个节点】都是一个合法的子集。
 * 3. 避免重复（组合问题）：使用 startIndex 确保每一层搜索只能从当前元素的【后面】选择，防止出现 [1,2] 和 [2,1] 这种重复组合。
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path;
        
        backtracking(nums, 0, path, result);
        return result;
    }

private:
    /**
     * @brief 回溯核心逻辑
     * @param startIndex 控制搜索起点，确保不回头取元素，实现组合逻辑
     */
    void backtracking(const vector<int>& nums, int startIndex, 
                      vector<int>& path, vector<vector<int>>& result) {
        
        // 1. 收集结果：每一个节点都是一个子集
        // 物理动作：将当前的 path 拷贝一份存入 result
        result.push_back(path);

        // 2. 终止条件：如果起点已经越界，说明没元素可取了
        // 实际上 for 循环的条件自然涵盖了这一步，可以省略显式的 return
        if (startIndex >= nums.size()) {
            return;
        }

        // 3. 遍历选择列表
        for (int i = startIndex; i < nums.size(); ++i) {
            // 修改现场
            path.push_back(nums[i]);

            // 递归：从 i + 1 开始，保证元素不被重复利用
            backtracking(nums, i + 1, path, result);

            // 恢复现场 (Backtrack)
            path.pop_back();
        }
    }
};

