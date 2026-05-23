/**
 * @file 0279_Perfect_Squares.cpp
 * @brief 279. 完全平方数
 * @link https://leetcode.cn/problems/perfect-squares/
 *
 * @algorithm 动态规划
 * @time_complexity O(N * sqrt(N)) - 外层循环遍历到 N，内层循环对每个数字 i 尝试所有可能的完全平方数，最多运行 sqrt(i) 次。累加近似为 O(N * sqrt(N))。
 * @space_complexity O(N) - 需要使用一个大小为 N + 1 的一维 dp 数组。
 *
 * @note 核心思路（DP 五步说明）：
 * 1. dp 数组含义：dp[i] 表示和为 i 的最少完全平方数个数。
 * 2. 状态转移方程：dp[i] = min(dp[i], dp[i - j * j] + 1)，其中 1 <= j * j <= i。
 * 3. 初始化：dp[0] = 0。其他 dp[i] 初始化为最坏情况下的值 i（即全部由 1 组成：i = 1 + 1 + ... + 1），安全不溢出。
 * 4. 遍历顺序：外层 i 从 1 到 n，内层 j 只要满足 j * j <= i 就一直向后遍历。
 * 5. 返回值：最终返回 dp[n]。
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numSquares(int n) {
        // 创建 dp 数组，大小为 n + 1，保存每个数字的最优解
        vector<int> dp(n + 1);
        
        // 初始化：组成 0 的最少完全平方数个数是 0
        dp[0] = 0;

        // 外层循环：顺次计算每一个数字 i 对应的 dp 值
        for (int i = 1; i <= n; ++i) {
            // 最坏情况初始化：任何数 i 最多可由 i 个 1 的平方组成（例如：3 = 1^2 + 1^2 + 1^2）
            // 这种初始化比直接设为 INT_MAX 更安全，能够完美避免后面 +1 时的整数溢出问题
            dp[i] = i;
            
            // 内层循环：尝试减去每一个比 i 小的完全平方数 j * j
            for (int j = 1; j * j <= i; ++j) {
                // 进行状态转移，选择最少的完全平方数方案
                dp[i] = min(dp[i], dp[i - j * j] + 1);
            }
        }

        // 返回组成 n 的最少完全平方数个数
        return dp[n];
    }
};