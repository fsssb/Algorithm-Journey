/**
 * @file 0031_Next_Permutation.cpp
 * @brief 31. 下一个排列
 * @link https://leetcode.cn/problems/next-permutation/
 * 
 * @algorithm Lexicographical Order Generation (字典序生成)
 * @time_complexity O(N)  - 最多两次扫描，一次反转
 * @space_complexity O(1) - 原地修改
 * 
 * @note 核心思路：
 * 1. 从后往前找第一个相邻升序对 (i, i+1)，nums[i] 为待替换的“低位”。
 * 2. 从后往前找第一个大于 nums[i] 的数 nums[j]，交换之。
 * 3. 将 i 之后的序列反转，使其从降序变为升序，达到最小增量。
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void nextPermutation(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        if (n <= 1) return;

        // 1. 从右向左寻找第一个下降点
        int i = n - 2;
        while (i >= 0 && nums[i] >= nums[i + 1]) {
            i--;
        }

        // 2. 如果找到了下降点
        if (i >= 0) {
            // 从右向左寻找第一个比 nums[i] 大的数
            int j = n - 1;
            while (j >= 0 && nums[j] <= nums[i]) {
                j--;
            }
            // 交换
            swap(nums[i], nums[j]);
        }

        // 3. 反转右侧序列（无论是全局还是局部）
        // 此时 i+1 后的序列必然是降序的，反转后变为升序
        reverse(nums.begin() + i + 1, nums.end());
    }
};