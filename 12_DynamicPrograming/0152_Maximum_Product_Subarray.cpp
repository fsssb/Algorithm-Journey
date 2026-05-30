/**
 * @file 0152_Maximum_Product_Subarray.cpp
 * @brief 152. 乘积最大子数组
 * @link https://leetcode.cn/problems/maximum-product-subarray/
 *
 * @algorithm 动态规划 (O(1) 空间滚动变量版)
 * @time_complexity O(N) - N 为数组长度。我们只需单遍线性扫描数组一次。
 * @space_complexity O(1) - 仅使用了三个辅助变量，未开辟额外的数组空间。
 *
 * @note 核心思路（DP 五步说明）：
 * 1. dp 数组含义：原 dp[i] 表示以 nums[i] 结尾的连续子数组的最大/最小乘积。此处优化为滚动变量 max_val 和 min_val。
 * 2. 状态转移方程：对于当前位置 i，由于负数的存在，最大值可能由“前一步最小值 * 当前负数”产生。所以：
 *    - max_val = max({nums[i], prev_max * nums[i], min_val * nums[i]})
 *    - min_val = min({nums[i], prev_max * nums[i], min_val * nums[i]})
 * 3. 溢出防范：题目提示保证了任何子数组的乘积都在 32 位整型范围内，故无需考虑中间状态溢出，直接使用 int 即可。
 * 4. 初始化：max_val = nums[0]，min_val = nums[0]，全局最大值 res = nums[0]。
 * 5. 遍历顺序：外层 i 从 1 到 n - 1 顺序遍历。
 *    - 关键细节：由于 max_val 更新后会污染 min_val 的计算，须在每轮循环开始时使用临时变量 temp_max 备份上一轮的 max_val。
 * 5. 返回值：最终返回全局出现过的最大乘积 res。
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxProduct(vector<int>& nums) {
        // 边界条件：若数组为空，直接返回 0
        if (nums.empty()) {
            return 0;
        }

        // 初始化状态变量，以第一个元素 nums[0] 作为起点
        int max_val = nums[0]; // 记录以当前位置结尾的最大乘积
        int min_val = nums[0]; // 记录以当前位置结尾的最小乘积
        int res = nums[0];     // 全局记录出现过的最大乘积

        int n = nums.size();
        // 从第二个元素开始顺序遍历
        for (int i = 1; i < n; ++i) {
            // 🚀 安全加固：使用临时变量备份未更新前的上一轮最大值，防止更新后发生变量污染
            int temp_max = max_val;

            // 状态更新：三者中取最大值和最小值
            // 1. nums[i] 自己重新开始（丢弃前面很差的乘积结果）
            // 2. 乘上上一轮的最大值
            // 3. 乘上上一轮的最小值（在 nums[i] 为负数、上一轮最小值为负数时，负负得正能产生巨大的最大值）
            max_val = max({nums[i], temp_max * nums[i], min_val * nums[i]});
            min_val = min({nums[i], temp_max * nums[i], min_val * nums[i]});

            // 每轮更新完后，尝试更新全局的最大乘积
            res = max(res, max_val);
        }

        return res;
    }
};
