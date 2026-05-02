/**
 * @file 0153_Find_Minimum_in_Rotated_Sorted_Array.cpp
 * @brief 153. 寻找旋转排序数组中的最小值
 * @link https://leetcode.cn/problems/find-minimum-in-rotated-sorted-array/
 * 
 * @algorithm Binary Search (二分查找边界收缩)
 * @time_complexity O(log N) - 对数级时间复杂度
 * @space_complexity O(1)    - 仅使用常数级辅助空间
 * 
 * @note 核心思路：
 * 1. 始终与右边界 nums[right] 进行比较。
 * 2. 如果中间值大于右边界，说明断点（最小值）在右半部。
 * 3. 如果中间值小于右边界，说明断点在左半部（包含 mid）。
 * 4. 循环条件为 left < right，最终 left 指向的位置即为最小值。
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findMin(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        // 健壮性检查：基础架构开发中的前置条件断言
        if (n == 0) return -1; 
        
        int left = 0;
        int right = n - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] > nums[right]) {
                // 中值大于右值，最小值必然在右侧，且不可能是 mid
                left = mid + 1;
            } else {
                // 中值小于右值，最小值在左侧或就是 mid 
                // 注意这里不执行 mid - 1，防止跳过可能的最小值点
                right = mid;
            }
        }

        /**
         * 为什么返回 nums[left]？
         * 当 left == right 时，区间收缩到唯一一点，
         * 该点即为旋转数组中打破单调性的那个极小值点。
         */
        return nums[left];
    }
};