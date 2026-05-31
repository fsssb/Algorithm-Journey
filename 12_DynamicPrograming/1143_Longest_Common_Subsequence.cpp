/**
 * @file 1143_Longest_Common_Subsequence.cpp
 * @brief 1143. 最长公共子序列
 * @link https://leetcode.cn/problems/longest-common-subsequence/
 *
 * @algorithm 动态规划 (区间/双序列 DP)
 * @time_complexity O(M * N)
 * @space_complexity O(M * N)
 *
 * @note 核心思路：
 * 1. 状态定义：dp[i][j] 表示 text1 的前 i 个字符与 text2 的前 j 个字符的最长公共子序列长度。
 * 2. 状态转移：
 *    - 若 text1[i-1] == text2[j-1]，则当前字符可合入 LCS：dp[i][j] = dp[i-1][j-1] + 1；
 *    - 若不相等，则退而求其次，在丢弃其中一个字符的分支中取最大值：dp[i][j] = max(dp[i-1][j], dp[i][j-1])。
 * 3. 边界处理：空字符串与任何串的 LCS 均为 0，即 dp[0][...] = dp[...][0] = 0。通过申请 (m+1)*(n+1) 空间完美实现。
 * 4. 遍历顺序：外层 i 从 1 到 m，内层 j 从 1 到 n，正向递推。
 */


#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        // 使用 static_cast 确保无符号整型比较安全，避免类型提升陷阱
        const int m = static_cast<int>(text1.size());
        const int n = static_cast<int>(text2.size());

        // 初始化二维 DP 数组，多申请一行一列用于处理空串边界
        vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

        // 双层正序循环递推状态
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (text1[i - 1] == text2[j - 1]) {
                    // 末尾字符相等，继承左上角的状态并加 1
                    dp[i][j] = dp[i - 1][j - 1] + 1;
                } else {
                    // 末尾字符不等，取上方和左方状态的最大值
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        // 返回两串完整长度时的 LCS 长度
        return dp[m][n];
    }
};


/**
 * @file 1143_Longest_Common_Subsequence.cpp
 * @brief 1143. 最长公共子序列
 * @link https://leetcode.cn/problems/longest-common-subsequence/
 *
 * @algorithm 动态规划 (一维滚动数组空间优化)
 * @time_complexity O(M * N)
 * @space_complexity O(min(M, N))
 *
 * @note 核心思路：
 * 1. 经典二维 DP 的递推仅依赖于“上一行”和“当前行左侧”的状态。
 * 2. 采用一维数组进行空间压缩。由于正向遍历更新 dp[j] 时，其左上方邻居 dp[i-1][j-1] 会被提前更新覆盖，
 *    因此引入临时变量 prev 在循环中扮演“接力棒”角色，安全保存并传递左上方的老状态。
 * 3. 每一轮更新前，用 temp 备份即将被覆盖的上一行当前列旧值，并在迭代结束时交接：prev = temp。
 * 4. 极致空间优化：若 text1 长度小于 text2，则交换两串，确保一维数组的大小始终受限于 min(M, N) + 1。
 */

#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestCommonSubsequence(string text1, string text2) {
        int m = static_cast<int>(text1.size());
        int n = static_cast<int>(text2.size());

        // 极致空间优化：确保内层循环对应的字符串较短，从而将一维数组空间死死锁定在 O(min(M, N))
        if (m < n) {
            return longestCommonSubsequence(text2, text1);
        }

        // 此时，n 必定是较短的那个长度
        vector<int> dp(n + 1, 0);

        for (int i = 1; i <= m; ++i) {
            int prev = 0; // 每一行开始前，左上角对应的 dp[i-1][j-1] 默认为 0
            for (int j = 1; j <= n; ++j) {
                int temp = dp[j]; // 1. 暂存当前格（代表上一行的当前列，是下一步 j + 1 的左上角）

                if (text1[i - 1] == text2[j - 1]) {
                    dp[j] = prev + 1; // 2. 匹配：使用保存完好的左上角状态 prev 递推
                } else {
                    dp[j] = max(dp[j], dp[j - 1]); // 3. 不匹配：取上方旧值 dp[j] 与左侧新值 dp[j-1] 的最大值
                }

                prev = temp; // 4. 接力棒交接：备份的老值成为下一步的左上角状态
            }
        }

        return dp[n];
    }
};