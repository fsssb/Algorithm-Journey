/**
 * @file 0139_Word_Break.cpp
 * @brief 139. 单词拆分
 * @link https://leetcode.cn/problems/word-break/
 *
 * @algorithm 动态规划 + 哈希集合
 * @time_complexity O(N^2 * L) - N 为字符串 s 的长度，L 为字典中单词的最大长度。外层循环 N 次，内层循环 N 次，substr 与哈希表查找耗时 O(L)。
 * @space_complexity O(N + M * L) - N 为 dp 数组的大小，M * L 为哈希集合存储字典所需的空间。
 *
 * @note 核心思路（DP 五步说明）：
 * 1. dp 数组含义：dp[i] 表示字符串 s 长度为 i 的前缀子串 s[0...i-1] 是否可以被成功拆分。
 * 2. 状态转移方程：对于每个位置 i，在 0 <= j < i 范围内寻找切刀位置：
 *    dp[i] = dp[j] && (word_set 包含 s[j...i-1])。
 * 3. 初始化：dp[0] = true（空字符串可以被成功拆分），其余 dp[i] 初始化为 false。
 * 4. 遍历顺序：外层 i 从 1 遍历到 s.length()；内层 j 从 0 遍历到 i - 1。
 *    - 优化：仅在 dp[j] 为 true 时提取子串并查词典；一旦 dp[i] 为 true，立即 break 剪枝。
 * 5. 返回值：返回 dp[s.length()]。
 */

#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool wordBreak(string s, vector<string>& wordDict) {
        // 优化 1：将 vector 字典转存入 unordered_set 中，将单次单词查找的时间复杂度降至平均 O(L)
        unordered_set<string> word_set(wordDict.begin(), wordDict.end());

        int n = s.length();
        // 创建 dp 数组，默认全部初始化为 false
        // dp[i] 代表长度为 i 的前缀子串是否可以被成功拆分
        vector<bool> dp(n + 1, false);

        // 基础边界初始化：空字符串可以被成功拆分
        dp[0] = true;

        // 外层循环：遍历前缀的长度 i（从 1 到 n）
        for (int i = 1; i <= n; ++i) {
            // 内层循环：寻找切刀位置 j（从 0 到 i - 1）
            for (int j = 0; j < i; ++j) {
                // 优化 2：只有当左半部分是可以成功拆分的（dp[j] 为 true）时，
                // 我们才需要去查字典校验右半部分。否则怎么拼都是错的，直接跳过。
                if (dp[j]) {
                    // 提取右半部分子串：从下标 j 开始，长度为 i - j
                    string suffix = s.substr(j, i - j);
                    
                    // 若右半部分在字典中存在，则当前长度 i 拆分成功
                    if (word_set.count(suffix)) {
                        dp[i] = true;
                        // 优化 3：只要找到一种可行的拆分方式，dp[i] 就是可行的，直接 break 剪枝
                        break;
                    }
                }
            }
        }

        // 返回整条字符串 s 是否可以被成功拆分的结果
        return dp[n];
    }
};


/*
    我们可以盯着题目给出的**数据范围（Constraints）**来寻找线索：
    字符串 s 的长度：最大为 300[1]。
    字典中单词的最大长度：最大只有 20[1]！
    发现痛点了吗？
    在我们的基础版代码中：
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < i; ++j) { // 这里 j 从 0 开始往右扫
    如果当 i = 100 时，j 从 0 开始。我们提取的后缀子串长度就是 i - j（比如 100 - 0 = 100）。
    但是，字典里的单词最长也就 20[1]！我们去字典里查一个长度为 100、80 甚至 30 的单词，是 100% 绝对不可能查到的！

*/

// // 1. 先找出字典中单词的最大长度
// int max_len = 0;
// for (const string& word : wordDict) {
//     max_len = max(max_len, (int)word.length());
// }

// // 2. 状态转移
// for (int i = 1; i <= n; ++i) {
//     // 💡 优化：j 倒着走，且最多只往前看 max_len 的距离！
//     for (int j = i - 1; j >= max(0, i - max_len); --j) {
//         if (dp[j]) {
//             string suffix = s.substr(j, i - j);
//             if (word_set.count(suffix)) {
//                 dp[i] = true;
//                 break; // 只要找到一种拆分方式，就成功
//             }
//         }
//     }
// }