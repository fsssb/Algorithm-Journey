/**
 * @file 0064_Minimum_Path_Sum.cpp
 * @brief 64. 最小路径和
 * @link https://leetcode.cn/problems/minimum-path-sum/
 *
 * @algorithm 动态规划 (一维滚动数组空间优化)
 * @time_complexity O(m * n) - 需要遍历整个网格一次，其中 m 为行数，n 为列数。
 * @space_complexity O(n) - 仅需维护一个长度为 n 的一维状态数组。
 *
 * @note 核心思路：
 * 1. dp 含义：dp[j] 表示从起点 (0, 0) 到当前处理行第 j 列的最小路径和。
 * 2. 转移方程：
 *    - 对于当前行的第 0 列 (j = 0)：只能由上方滚下，故 dp[0] = dp[0] + grid[i][0]。
 *    - 对于当前行的其余列 (j > 0)：可由上方 (未更新的旧 dp[j]) 或左方 (已更新的新 dp[j-1]) 转移过来。
 *      方程为：dp[j] = min(dp[j], dp[j-1]) + grid[i][j]。
 * 3. 初始化：
 *    - 起点 dp[0] = grid[0][0]。
 *    - 第 0 行的其余位置通过自左向右累加初始化：dp[j] = dp[j-1] + grid[0][j]。
 * 4. 遍历顺序：外层从上到下（行 i 从 1 到 m-1），内层从左到右（列 j 从 1 到 n-1）。
 * 5. 返回值：一维数组的末尾元素 dp[n-1]。
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int minPathSum(vector<vector<int>>& grid) {
        // 边界安全防御
        if (grid.empty() || grid[0].empty()) {
            return 0;
        }

        // 使用 static_cast 规避无符号整型带来的潜在减法溢出或比较问题
        int m = static_cast<int>(grid.size());
        int n = static_cast<int>(grid[0].size());

        // 一维 dp 数组，空间优化至 O(n)
        vector<int> dp(n, 0);

        // 3. 初始化起点与第 0 行
        dp[0] = grid[0][0];
        for (int j = 1; j < n; ++j) {
            dp[j] = dp[j - 1] + grid[0][j];
        }

        // 4. 遍历顺序：外层行，内层列
        for (int i = 1; i < m; ++i) {
            // 每行的第 0 列只能从上方转移而来
            dp[0] += grid[i][0];
            for (int j = 1; j < n; ++j) {
                // 2. 转移方程：
                // 左边的 dp[j-1] 在当前轮次已更新，代表 dp[i][j-1]
                // 此时的 dp[j] 尚未被当前行更新，仍保留着上一行的值，代表 dp[i-1][j]
                dp[j] = min(dp[j], dp[j - 1]) + grid[i][j];
            }
        }

        // 5. 返回右下角终点值
        return dp[n - 1];
    }
};

