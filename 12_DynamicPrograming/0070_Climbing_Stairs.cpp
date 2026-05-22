/**
 * @file 0070_Climbing_Stairs.cpp
 * @brief 70. 爬楼梯
 * @link https://leetcode.cn/problems/climbing-stairs/
 * 
 * @algorithm Dynamic Programming (Space-Optimized)
 * @time_complexity O(N)  - 线性扫描一次
 * @space_complexity O(1) - 仅使用三个标量变量，无额外内存分配
 * 
 * @note 核心思路：
 * 1. 状态转移方程 dp[i] = dp[i-1] + dp[i-2]。
 * 2. 空间压缩：仅保留前两个状态 prev 和 curr，循环滚动更新。
 * 3. 边界处理：n <= 2 直接返回。
 */

#include <vector>

using namespace std;

class Solution {
public:
    int climbStairs(int n) {
        // 1. 边界防御：基础架构级稳健性
        if (n <= 2) return n;

        // 2. 状态初始化：仅使用栈内存（Stack Memory）
        int p_prev = 1; // f(n-2)
        int prev = 2;   // f(n-1)
        int curr = 0;

        // 3. 迭代计算：自底向上（Bottom-up）
        for (int i = 3; i <= n; ++i) {
            curr = p_prev + prev;
            // 滚动更新
            p_prev = prev;
            prev = curr;
        }

        return curr;
    }
};
/*
    class Solution {
    public:
        int climbStairs(int n) {
            if (n <= 2) return n;

            vector<int> dp(n + 1, 0);
            dp[1] = 1;
            dp[2] = 2;

            for (int i = 3; i <= n; i++) {
                dp[i] = dp[i - 1] + dp[i - 2];
            }

            return dp[n];
        }
    };
*/
/*
    class Solution {
    public:
        int climbStairs(int n) {
            if (n <= 2) return n;

            int a = 1, b = 2;
            for (int i = 3; i <= n; i++) {
                int c = a + b;
                a = b;
                b = c;
            }

            return b;
        }
    };

*/

//我会用一维 DP。定义 dp[i] 表示爬到第 i 阶一共有多少种方法。因为每次只能爬 1 阶或 2 阶，所以到第 i 阶只能从第 i-1 阶走一步，或者从第 i-2 阶走两步，因此状态转移是 dp[i] = dp[i-1] + dp[i-2]。初
// 始化 dp[1]=1，dp[2]=2，然后从 3 遍历到 n，最后返回 dp[n]。时间复杂度 O(n)，空间复杂度可以从 O(n) 优化到 O(1)。