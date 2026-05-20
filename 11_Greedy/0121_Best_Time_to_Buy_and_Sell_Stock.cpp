/**
 * @file 0121_Best_Time_to_Buy_and_Sell_Stock.cpp
 * @brief 121. 买卖股票的最佳时机
 * @link https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/
 * 
 * @algorithm Greedy / One-pass State Machine
 * @time_complexity O(N)  - 仅需一次线性扫描
 * @space_complexity O(1) - 仅使用两个寄存器变量
 * 
 * @note 核心思路：
 * 1. 初始化 min_price 为系统最大值，max_profit 为 0。
 * 2. 遍历价格数组，更新遇到的最低价格。
 * 3. 计算当前价格与最低价格的差值，并更新全局最大利润。
 */

#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maxProfit(vector<int>& prices) {
        // 1. 初始化：使用 INT_MAX 确保第一个价格能被正确捕获为 min_price
        int min_price = INT_MAX;
        int max_profit = 0;

        // 2. 线性扫描：利用 Cache Locality 的最佳访存模式
        for (int price : prices) {
            // 状态更新逻辑：
            // 如果当前价格更低，更新买入成本
            if (price < min_price) {
                min_price = price;
            } 
            // 否则，计算并尝试更新最大利润
            else if (price - min_price > max_profit) {
                max_profit = price - min_price;
            }
        }

        return max_profit;
    }
};