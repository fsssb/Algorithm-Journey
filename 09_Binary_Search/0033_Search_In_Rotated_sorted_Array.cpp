/**
 * @file 0033_Search_in_Rotated_Sorted_Array.cpp
 * @brief 33. 搜索旋转排序数组
 * @link https://leetcode.cn/problems/search-in-rotated-sorted-array/
 * 
 * @algorithm Modified Binary Search (变体二分查找)
 * @time_complexity O(log N) - 尽管数组被旋转，仍能保持对数级搜索效率
 * @space_complexity O(1)    - 仅使用常量级辅助空间
 * 
 * @note 核心思路：
 * 1. 关键在于通过比较 nums[left] 和 nums[mid] 确定哪一侧是“单调区间”。
 * 2. 只要有一侧单调，就能通过区间边界判断 target 是否在该侧。
 * 3. 这里的边界处理必须严格使用 <=，以处理 mid 和 left 重合的情况。
 */

#include <vector>

using namespace std;

class Solution {
public:
    int search(vector<int>& nums, int target) {
        int n = static_cast<int>(nums.size());
        if (n == 0) return -1;

        int left = 0;
        int right = n - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) return mid;

            // 情况 1: 左半部分是有序的
            if (nums[left] <= nums[mid]) {
                // target 落在左半部分的有序区间内
                if (nums[left] <= target && target < nums[mid]) {
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            } 
            // 情况 2: 右半部分是有序的
            else {
                // target 落在右半部分的有序区间内
                if (nums[mid] < target && target <= nums[right]) {
                    left = mid + 1;
                } else {
                    right = mid - 1;
                }
            }
        }

        return -1;
    }
};