/**
 * @file 0169_Majority_Element.cpp
 * @brief 169. 多数元素
 * @link https://leetcode.cn/problems/majority-element/
 * 
 * @algorithm Boyer-Moore Majority Vote Algorithm (摩尔投票法)
 * @time_complexity O(N)  - 线性扫描
 * @space_complexity O(1) - 仅需两个变量
 * 
 * @note 核心思路：
 * 1. 众数个数 > n/2，意味着它比其他所有元素之和还多。
 * 2. 通过 count 的增减模拟“抵消”过程，最后活下来的候选者即为所求。
 */

#include <vector>

using namespace std;

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int candidate = 0;
        int count = 0;

        for (int num : nums) {
            if (count == 0) {
                candidate = num;
            }
            // 技巧：三元运算符减少代码行数，但底层依然是分支逻辑
            count += (num == candidate) ? 1 : -1;
        }

        return candidate;
    }
};