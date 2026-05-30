/**
 * @file 0416_Partition_Equal_Subset_Sum.cpp
 * @brief 416. 分割等和子集
 * @link https://leetcode.cn/problems/partition-equal-subset-sum/
 *
 * @algorithm 动态规划 (0-1 背包问题 2D 版本)
 * @time_complexity O(N * target) - N 为数组长度，target 为数组总和的一半。双重循环遍历整个二维状态矩阵。
 * @space_complexity O(N * target) - 使用了一个 (N + 1) * (target + 1) 大小的二维布尔矩阵。
 *
 * @note 核心思路（DP 五步说明）：
 * 1. dp 数组含义：dp[i][j] 表示能否从前 i 个金币中挑出一部分，凑出总和刚好为 j 的子集。
 * 2. 状态转移方程：对于第 i 个金币（面值为 x = nums[i-1]）：
 *    - 若不选它，继承前 i-1 个的状态：dp[i][j] = dp[i-1][j]
 *    - 若选择它（前提是 j >= x），则为：dp[i][j] = dp[i-1][j] || dp[i-1][j-x]
 * 3. 初始化：j = 0 的一列初始化为 true（不选任何金币即可凑出 0）；i = 0 的一行除第一个元素外初始化为 false。
 * 4. 遍历顺序：行 i 从 1 到 N，列 j 从 1 到 target，顺序推进。
 * 5. 返回值：最终返回 dp[N][target]。
 */

#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        // 计算数组中所有金币的总和
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }

        // 奇偶判断：如果总和是奇数，绝对无法平分，直接返回 false
        if (sum % 2 != 0) {
            return false;
        }

        int n = nums.size();
        int target = sum / 2; // 每个人需要分到的目标面额

        // 创建二维 DP 矩阵，大小为 (n + 1) 行，(target + 1) 列，默认初始化为 false
        // 多出来的 "+1" 完美承载了 "0个金币" 和 "0元目标和" 的初始状态，避开了下标错位
        vector<vector<bool>> dp(n + 1, vector<bool>(target + 1, false));

        // 初始化第 0 列：任意前 i 个金币，凑齐 0 元的目标永远可行（什么都不选即可）
        for (int i = 0; i <= n; ++i) {
            dp[i][0] = true;
        }

        // 状态递推
        // 外层循环：顺次遍历每一个金币 i（从 1 到 n）
        for (int i = 1; i <= n; ++i) {
            int x = nums[i - 1]; // 当前第 i 个金币的实际面值（注意 nums 的下标是 i - 1）
            
            // 内层循环：遍历每一个可能的目标和 j（从 1 到 target）
            for (int j = 1; j <= target; ++j) {
                if (j >= x) {
                    // 如果当前目标和 j 大于等于当前金币面值 x，我们可以选择：
                    // 1. 不选当前金币：dp[i-1][j]
                    // 2. 选择当前金币：dp[i-1][j-x]
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - x];
                } else {
                    // 如果当前目标和 j 小于金币面值 x，放不下，我们只能选择不选
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }

        // 返回前 n 个金币能否凑齐 target 的结果
        return dp[n][target];
    }
};


/**
 * @file 0416_Partition_Equal_Subset_Sum.cpp
 * @brief 416. 分割等和子集
 * @link https://leetcode.cn/problems/partition-equal-subset-sum/
 *
 * @algorithm 动态规划 (0-1 背包问题 1D 空间滚动数组版)
 * @time_complexity O(N * target) - N 为数组长度，target 为目标和。双重循环遍历一维状态数组。
 * @space_complexity O(target) - 压缩了行维度，仅需一个大小为 target + 1 的一维布尔数组。
 *
 * @note 核心思路（DP 五步说明）：
 * 1. dp 数组含义：dp[j] 表示当前能否从数组中挑出一部分数字，凑出总和刚好为 j 的子集。
 * 2. 状态转移方程：dp[j] = dp[j] || dp[j - num]，其中 num 为当前数字，且 j >= num。
 * 3. 初始化：dp[0] = true（凑出和为 0 的情况永远可行，什么都不选即可），其余位置默认初始化为 false。
 * 4. 遍历顺序：外层顺序遍历每个数字 num；内层倒序遍历目标和 j（从 target 递减到 num）。
 *    - 核心：必须倒序遍历！这确保了在更新 dp[j] 时，其左边所依赖的 dp[j - num] 依然是上一轮未被污染的旧值，防止同一硬币被重复使用。
 * 5. 返回值：最终返回 dp[target]。
 */

#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        // 计算数组中所有金币的总和
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }

        // 奇偶判断：若总和是奇数，绝对无法平分，直接返回 false
        if (sum % 2 != 0) {
            return false;
        }

        int target = sum / 2; // 每个人需要分到的目标面额

        // 一维空间滚动数组，默认全部初始化为 false
        // 空间复杂度由 O(N * target) 完美缩减至 O(target)
        vector<bool> dp(target + 1, false);

        // 初始化基础边界：和为 0 的情况永远是可行状态（什么都不选即可）
        dp[0] = true;

        // 外层循环：顺次遍历每一个数字 num
        for (int num : nums) {
            // 内层循环：必须倒序遍历！
            // j 从 target 开始倒序递减到 num。当 j < num 时放不下当前硬币，状态自动保持上一轮不变。
            for (int j = target; j >= num; --j) {
                // 状态转移方程：只要“不选”和“选择”当前数字有一个可行，当前状态即为 true
                dp[j] = dp[j] || dp[j - num];
            }
        }

        // 返回最终能否凑齐目标和的结果
        return dp[target];
    }
};



/**
 * @file 0416_Partition_Equal_Subset_Sum.cpp
 * @brief 416. 分割等和子集
 * @link https://leetcode.cn/problems/partition-equal-subset-sum/
 *
 * @algorithm 动态规划 (0-1 背包问题 std::bitset 极速优化版)
 * @time_complexity O(N * (target / 64)) - N 为数组长度，target 为目标和。由于 64 位 CPU 可以并行处理 64 个位的移位和或运算，因此常数项非常小，几乎等同于 O(N)。
 * @space_complexity O(target / 64) - 仅需一个大小为 10001 位的 bitset，实际占用内存约 1.2 KB，比普通的 vector 节省了 64 倍以上的物理空间。
 *
 * @note 核心思路（DP 五步说明）：
 * 1. dp 数组含义：此处使用 std::bitset<10001> bits 替代原本的一维 bool 数组。第 j 位为 1 代表可以凑出和为 j 的子集。
 * 2. 状态转移方程：对于每个数字 num，状态转移可以表示为 bits |= (bits << num)。
 *    - bits << num：利用 CPU 位移，瞬间将所有可行状态向右平移 num 位（相当于把每个原可行状态 j 加上新硬币，变为 j + num）；
 *    - bits |= ...：通过按位或运算，一键合并旧的可行状态与新增的可行状态。
 * 3. 初始化：bits(1) 代表将第 0 位（代表 dp[0]）初始化为 1，其余位为 0。
 * 4. 遍历顺序：直接顺序遍历 nums 数组中的每一个数字，内层完全由高效的 CPU 硬件位运算代替，省去了手动循环。
 * 5. 返回值：最终返回 bits[target] 对应二进制位上的值（0 代表 false，1 代表 true）。
 */

#include <vector>
#include <numeric>
#include <bitset>

using namespace std;

class Solution {
public:
    bool canPartition(vector<int>& nums) {
        // 计算数组中所有数字的总和
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }

        // 奇偶判断：若总和是奇数，绝对无法平分，直接返回 false
        if (sum % 2 != 0) {
            return false;
        }

        int target = sum / 2; // 每个人需要分到的目标面额

        // C++ 极致性能黑魔法：std::bitset
        // 题目限制中：nums.length <= 200，nums[i] <= 100，所以最大总和为 20000，最大 target 为 10000。
        // 我们开辟 10001 位的 bitset 即可满足所有测试用例（最高位索引为 10000）。
        // 初始参数为 1，代表二进制的 00...01，即将第 0 位（代表 dp[0]）设为 1，其余位为 0。
        bitset<10001> bits(1);

        // 遍历数组中的每一个数字
        for (int num : nums) {
            // 核心状态转移一行流：
            // 1. bits << num：将所有当前能凑出的状态全部向右偏移 num 位（等同于对所有原状态 j 执行 +num）；
            // 2. bits |= ...：通过按位或，一键合并“保留原状态”与“累加当前硬币后产生的新状态”。
            bits |= (bits << num);
        }

        // 返回 target 对应二进制位上的值（0 代表 false，1 代表 true）
        return bits[target];
    }
};
