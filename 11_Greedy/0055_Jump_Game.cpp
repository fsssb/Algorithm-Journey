/**
 * @file 0055_Jump_Game.cpp
 * @brief 55. 跳跃游戏
 * @link https://leetcode.cn/problems/jump-game/
 * 
 * @algorithm Greedy (贪心算法)
 * @time_complexity O(N)  - 仅需一次线性扫描
 * @space_complexity O(1) - 仅使用一个辅助变量记录边界
 * 
 * @note 核心思路：
 * 1. 维护变量 max_reach 记录当前能到达的最远索引。
 * 2. 遍历过程中，若当前索引 i 已超过 max_reach，说明路径中断。
 * 3. 实时更新 max_reach，若已覆盖终点则提前退出。
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool canJump(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        int max_reach = 0;

        // 顺序扫描：利用 Cache 预取的最佳访存模式
        for (int i = 0; i < n; ++i) {
            // 1. 连通性检查：如果当前位置已经不可达，后续必然无法到达
            if (i > max_reach) {
                return false;
            }

            // 2. 更新最远边界：当前位置 + 该位置提供的跳力
            max_reach = max(max_reach, i + nums[i]);

            // 3. 早期退出：Infra 级别的性能优化，减少冗余计算
            if (max_reach >= n - 1) {
                return true;
            }
        }

        return max_reach >= n - 1;
    }
};