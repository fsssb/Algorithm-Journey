/**
 * @file 0005_Longest_Palindromic_Substring.cpp
 * @brief 5. 最长回文子串
 * @link https://leetcode.cn/problems/longest-palindromic-substring/
 *
 * @algorithm 动态规划 (区间 DP)
 * @time_complexity O(N^2)
 * @space_complexity O(N^2)
 *
 * @note 核心思路：
 * 1. 定义二维布尔状态 dp[i][j] 刻画子串 s[i..j] 的对称回文状态。
 * 2. 利用外层反向、内层正向的双重循环，使状态转换无缝依赖已计算完毕的子区间状态。
 * 3. 在行数递减、列数递增的递推中，动态维护最长回文子串的 [start, max_len] 记录。
 */

#include<string>
#include <vector>
 using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        const int n = static_cast<int>(s.size());
        if (n < 2) {
            return s;
        }

        vector<vector<bool>> dp(n, vector<bool>(n, false));
        int start = 0;
        int max_len = 1;

        for (int i = n - 1; i >= 0; --i) {
            for (int j = i; j < n; ++j) {
                if (s[i] == s[j]) {
                    if (j - i <= 2) {
                        dp[i][j] = true;
                    } else {
                        dp[i][j] = dp[i + 1][j - 1];
                    }
                }

                if (dp[i][j] && (j - i + 1) > max_len) {
                    max_len = j - i + 1;
                    start = i;
                }
            }
        }

        return s.substr(start, max_len);
    }
};



/**
 * @file 0005_Longest_Palindromic_Substring.cpp
 * @brief 5. 最长回文子串
 * @link https://leetcode.cn/problems/longest-palindromic-substring/
 *
 * @algorithm 中心扩展法 (Center Expansion)
 * @time_complexity O(N^2)
 * @space_complexity O(1)
 *
 * @note 核心思路：
 * 1. 遍历全部 2N-1 个对称中心（N 个单字符中心，N-1 个双字符缝隙中心）。
 * 2. 引入 lambda 辅助函数 expandAroundCenter，利用双指针向两端发散，在边界内通过 s[left] == s[right] 持续校验。
 * 3. 循环终止时，合法回文串区间为 [left + 1, right - 1]，长度为 right - left - 1。
 * 4. 统一计算公式 start = i - (len - 1) / 2，无缝兼容奇数与偶数长度的回文串起点定位。
 */

using namespace std;

class Solution {
public:
    string longestPalindrome(string s) {
        // 使用 static_cast 确保无符号整型比较安全
        const int n = static_cast<int>(s.size());
        if (n < 2) {
            return s;
        }

        int start = 0;
        int max_len = 1;

        // 定义辅助扩展函数（C++ Lambda 捕获局部变量）
        auto expandAroundCenter = [&](int left, int right) -> int {
            while (left >= 0 && right < n && s[left] == s[right]) {
                left--;
                right++;
            }
            // 退出循环时，回文子串长度公式为 right - left - 1
            return right - left - 1;
        };

        for (int i = 0; i < n; ++i) {
            // 情况 1：以 s[i] 为中心进行奇数长度扩展
            int len1 = expandAroundCenter(i, i);
            // 情况 2：以 s[i] 和 s[i+1] 为中心进行偶数长度扩展
            int len2 = expandAroundCenter(i, i + 1);
            
            int len = max(len1, len2);

            if (len > max_len) {
                max_len = len;
                // 统一的起点计算公式，完美兼容奇偶数长度
                start = i - (len - 1) / 2;
            }
        }

        return s.substr(start, max_len);
    }
};