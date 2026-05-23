/**
 * @file 0198_House_Robber.cpp
 * @brief 198. 打家劫舍
 * @link https://leetcode.cn/problems/house-robber/
 *
 * @algorithm 动态规划 (O(1) 空间滚动变量优化版)
 * @time_complexity O(N) - N 为房屋数量。我们只需单遍线性扫描数组。
 * @space_complexity O(1) - 仅使用了三个辅助变量，未开辟额外的数组空间。
 *
 * @note 核心思路（DP 五步说明）：
 * 1. dp 数组含义：原 dp[i] 表示走到第 i 间房时能偷到的最高金额。此处优化为变量 prev1 (dp[i-2]) 和 prev2 (dp[i-1])。
 * 2. 状态转移方程：对每间房做出“偷”与“不偷”的抉择，新状态为 curr = max(prev2, prev1 + nums[i])。
 * 3. 初始化：未开始时 prev1 = 0（代表第 -1 间房金额为 0），第一间房时 prev2 = nums[0]。
 * 4. 遍历顺序：外层循环从索引 1 顺序遍历至数组末尾。
 * 5. 返回值：遍历结束后，prev2 中保存的即为偷窃完毕后的最高金额。
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int rob(vector<int>& nums) {
        // 边界条件：若没有房屋，小偷无法偷窃任何金额
        if (nums.empty()) {
            return 0;
        }
        // 边界条件：若只有一间房屋，直接偷窃该房屋即可
        if (nums.size() == 1) {
            return nums[0];
        }

        // prev1 保存 dp[i-2]（“前两间房”的最优值），初始化为 0（代表第 -1 间房）
        int prev1 = 0;
        // prev2 保存 dp[i-1]（“前一间房”的最优值），初始化为第一间房的金额 nums[0]
        int prev2 = nums[0];

        // 从第二间房屋（索引为 1）开始遍历，顺次向后推算
        for (size_t i = 1; i < nums.size(); ++i) {
            // 当前第 i 间房的最优决策：
            // 1. 若不偷当前房，金额等于前一间房的最优值 prev2；
            // 2. 若选择偷当前房，金额等于前两间房的最优值 prev1 加上当前房的金额 nums[i]；
            int curr = max(prev2, prev1 + nums[i]);

            // 滚动更新：前两间的最优值变为前一间，前一间的最优值变为当前最新值
            prev1 = prev2;
            prev2 = curr;
        }

        // 最终 prev2 存储的就是遍历到最后一间房屋时的最高可偷窃金额
        return prev2;
    }
};