/**
 * @file 0045_Jump_Game_II.cpp
 * @brief 45. 跳跃游戏 II
 * @link https://leetcode.cn/problems/jump-game-ii/
 * 
 * @algorithm Greedy with Dual Boundaries (双边界贪心)
 * @time_complexity O(N)  - 线性扫描一次
 * @space_complexity O(1) - 仅需三个辅助变量
 * 
 * @note 核心思路：
 * 1. max_reach: 维护下一跳能到的最远位置。
 * 2. cur_end: 当前步数能覆盖的范围，走到这里就必须增加步数。
 * 3. 遍历范围是 [0, n-2]，因为如果已经到达 n-1，不需要再增加跳数。
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int jump(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n <= 1) return 0;

        int jumps = 0;      // 跳跃总次数
        int cur_end = 0;    // 当前跳跃能覆盖的最远边界
        int max_reach = 0;  // 下一跳能覆盖的最远边界

        // 线性扫描：Stride-1 访存模式
        for (int i = 0; i < n - 1; ++i) {
            // 1. 实时更新下一跳的潜力（潜力探测）
            max_reach = max(max_reach, i + nums[i]);

            // 2. 触发跳跃：当到达当前跳跃的极限时
            if (i == cur_end) {
                jumps++;
                cur_end = max_reach; // 扩展当前覆盖范围

                // 早期退出：如果当前边界已覆盖终点，无需继续扫描
                if (cur_end >= n - 1) break;
            }
        }

        return jumps;
    }
};