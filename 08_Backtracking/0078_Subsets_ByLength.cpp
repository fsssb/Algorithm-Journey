/**
 * @file 0078_Subsets_ByLength.cpp
 * @brief 78. 子集 (按长度分层实现版)
 * 
 * @algorithm 组合搜索 + 分层递归
 * @note 核心逻辑：
 * 1. 外层循环控制子集的长度 k (从 0 到 n)。
 * 2. 内层回溯函数专门负责寻找长度【严格等于 k】的组合。
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> subsets(vector<int>& nums) {
        vector<vector<int>> result;
        vector<int> path;
        int n = nums.size();

        // 提前预分配 2^n 个空间，防止 vector 频繁扩容搬家 (Cherno 强烈推荐)
        result.reserve(1 << n);

        // 你的思路：依次找出长度为 0, 1, 2...n 的子集
        for (int k = 0; k <= n; ++k) {
            backtracking(nums, 0, k, path, result);
        }

        return result;
    }

private:
    /**
     * @brief 寻找固定长度 k 的组合
     * @param targetLen 目标长度 k
     */
    void backtracking(const vector<int>& nums, int startIndex, int targetLen,
                      vector<int>& path, vector<vector<int>>& result) {
        
        // 1. 终止条件：当前路径长度达到目标 k
        if (path.size() == targetLen) {
            result.push_back(path);
            return;
        }

        // 2. 遍历选择列表
        // 【关键剪枝】：如果剩余元素不足以凑齐目标长度，直接停止循环
        // 剩余可选：n - i, 还需要：targetLen - path.size()
        for (int i = startIndex; i <= (int)nums.size() - (targetLen - (int)path.size()); ++i) {
            path.push_back(nums[i]);
            
            // 递归：寻找下一个元素
            backtracking(nums, i + 1, targetLen, path, result);
            
            // 回溯
            path.pop_back();
        }
    }
};

