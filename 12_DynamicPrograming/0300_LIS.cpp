/**
 * @file 0300_Longest_Increasing_Subsequence.cpp
 * @brief 300. 最长递增子序列
 * @link https://leetcode.cn/problems/longest-increasing-subsequence/
 *
 * @algorithm 动态规划 (O(N^2) 版本)
 * @time_complexity O(N^2) - 双重循环遍历，外层循环遍历每个元素，内层循环在当前元素之前寻找所有比它小的元素并更新。
 * @space_complexity O(N) - 需要使用一个大小为 N 的一维 dp 数组存储状态值。
 *
 * @note 核心思路：
 * 1. 定义 dp[i] 为以 nums[i] 结尾的最长递增子序列的长度。
 * 2. 任何一个元素自身都构成一个长度为 1 的递增子序列，故整个 dp 数组初始化为 1。
 * 3. 采用双重循环：外层 i 控制当前考察的终点元素，内层 j 遍历 0 <= j < i 的所有前驱元素。
 * 4. 只有当满足 nums[i] > nums[j] 的严格递增关系时，才通过 dp[i] = max(dp[i], dp[j] + 1) 进行更新。
 * 5. 在计算的过程中，利用全局变量 max_len 实时保存出现的最大的 dp[i]，最终将其返回。
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
        // 边界条件处理：若输入为空，直接返回长度 0
        if (nums.empty()) {
            return 0;
        }

        int n = nums.size();
        // 初始化 dp 数组，默认每个数字自身都是一个长度为 1 的子序列
        vector<int> dp(n, 1);
        int max_len = 1; // 记录全局最长递增子序列长度

        // 外层循环：遍历数组中的每一个数字，计算以其结尾的 LIS 长度
        for (int i = 0; i < n; ++i) {
            // 内层循环：寻找当前 i 之前的所有前驱数字 j
            for (int j = 0; j < i; ++j) {
                // 只有当当前数字大于前驱数字，才能构成递增关系
                if (nums[i] > nums[j]) {
                    // 与已有的 dp[i] 进行 PK，保留更长的方案
                    dp[i] = max(dp[i], dp[j] + 1);
                }
            }
            // 每次确定好 dp[i] 后，更新全局最大长度
            max_len = max(max_len, dp[i]);
        }

        return max_len;
    }
};

/*
    class Solution {
public:
    int lengthOfLIS(vector<int>& nums) {
       
        //tails[i] 表示在当前的长度 i + 1 下的尾部最小的数！
        vector<int> tails;

        for(int num : nums){
            auto it = lower_bound(tails.begin(),tails.end(),num);
            if(it == tails.end()){
                tails.push_back(num);
            }else{
                *it = num;
            }
        }
        return tails.size();
    }

      
};
*/