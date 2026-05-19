/**
 * @file 0136_Single_Number.cpp
 * @brief 136. 只出现一次的数字
 * @link https://leetcode.cn/problems/single-number/
 * 
 * @algorithm Bitwise XOR (位运算 - 异或)
 * @time_complexity O(N)  - 遍历一次数组
 * @space_complexity O(1) - 仅使用一个变量存储中间异或结果
 * 
 * @note 核心思路：
 * 1. 初始化 ans = 0。
 * 2. 遍历数组，将每个元素与 ans 执行异或操作。
 * 3. 利用异或自反性 (a ^ a = 0)，所有出现两次的数字都会抵消，最终 ans 即为所求。
 */

#include <vector>

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        int ans = 0;
        // 范围 for 循环：减少迭代器维护开销
        for (int num : nums) {
            ans ^= num;
        }
        return ans;
    }
};