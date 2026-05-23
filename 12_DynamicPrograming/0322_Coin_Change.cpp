/**
 * @file 0322_Coin_Change.cpp
 * @brief 322. 零钱兑换
 * @link https://leetcode.cn/problems/coin-change/
 *
 * @algorithm 动态规划
 * @time_complexity O(N * M) - N 为 amount，M 为 coins 数组的长度。外层循环执行 N 次，内层循环执行 M 次。
 * @space_complexity O(N) - 需要使用一个大小为 amount + 1 的一维 dp 数组。
 *
 * @note 核心思路（DP 五步说明）：
 * 1. dp 数组含义：dp[i] 表示凑齐金额 i 所需的最少硬币个数。
 * 2. 状态转移方程：dp[i] = min(dp[i], dp[i - coin] + 1)，其中 coin 属于 coins 且 i >= coin。
 * 3. 初始化：将整个 dp 数组默认初始化为 amount + 1（代表无穷大，既不溢出又可以被 min 更新），但 dp[0] 显式设为 0。
 * 4. 遍历顺序：外层 i 从 1 到 amount 顺序遍历，内层遍历硬币面额 coins。
 * 5. 返回值：若 dp[amount] > amount 则说明没有任何组合能够凑出，返回 -1；否则返回 dp[amount]。
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int coinChange(vector<int>& coins, int amount) {
        // 创建 dp 数组并默认全部填充为 amount + 1（作为防溢出的无穷大值）
        vector<int> dp(amount + 1, amount + 1);
        
        // 显式初始化：凑齐 0 元需要 0 枚硬币
        dp[0] = 0;

        // 外层循环：从金额 1 开始，顺次推算到目标金额 amount
        for (int i = 1; i <= amount; ++i) {
            // 内层循环：尝试使用每一枚可用的硬币
            for (int coin : coins) {
                // 安全加固：当前要凑的金额 i 必须能够放得下这枚硬币（防止数组负数越界）
                if (i >= coin) {
                    // 进行状态转移
                    dp[i] = min(dp[i], dp[i - coin] + 1);
                }
            }
        }

        // 判断最终的目标金额 dp[amount] 是否还等于初始化的无穷大
        // 如果大于 amount，说明完全无法凑出，返回 -1；否则返回对应最少个数
        return dp[amount] > amount ? -1 : dp[amount];
    }
};