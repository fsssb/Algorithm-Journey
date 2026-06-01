/**
 * @file 0029_Divide_Two_Integers.cpp
 * @brief 29. 两数相除
 * @link https://leetcode.cn/problems/divide-two-integers/
 *
 * @algorithm Exponential Search / Bit Manipulation (倍增减法)
 * @time_complexity O(logN * logN) - 每轮用倍增快速逼近，`外层最多约 31 次
 * @space_complexity O(1)
 *
 * @note 核心思路：
 * 1. 不能使用乘法、除法和取模，因此用“不断减去 divisor 的倍数”来模拟除法。
 * 2. 为了避免 abs(INT_MIN) 溢出，把 dividend 和 divisor 都转成负数处理。
 * 3. 每次从 divisor 开始倍增，找到不超过当前 dividend 的最大负数倍数，一次性减掉。
 * 4. 最后根据符号决定商的正负，并单独处理 INT_MIN / -1 的溢出。
 */

#include <climits>

class Solution {
public:
    int divide(int dividend, int divisor) {
        if (dividend == INT_MIN && divisor == -1) {
            return INT_MAX;
        }

        int negativeCount = 0;
        long long dvd = dividend;
        long long dvs = divisor;

        if (dvd > 0) {
            dvd = -dvd;
            negativeCount++;
        }
        if (dvs > 0) {
            dvs = -dvs;
            negativeCount++;
        }

        long long quotient = 0;
        while (dvd <= dvs) {
            long long current = dvs;
            long long multiple = 1;

            while (dvd <= current + current) {
                current += current;
                multiple += multiple;
            }

            dvd -= current;
            quotient += multiple;
        }

        return negativeCount == 1 ? -quotient : quotient;
    }
};
