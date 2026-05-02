/**
 * @file 0035_Search_Insert_Position.cpp
 * @brief 35. 搜索插入位置
 * @link https://leetcode.cn/problems/search-insert-position/
 * 
 * @algorithm Binary Search (二分查找)
 * @time_complexity O(log N) - 典型的对数折半搜索，每次排除一半空间
 * @space_complexity O(1)    - 仅使用若干整型变量，属于原地搜索
 * 
 * @note 核心思路：
 * 1. 初始化双指针 left = 0, right = n - 1。
 * 2. 在 while (left <= right) 条件下循环。
 * 3. 计算 mid = left + (right - left) / 2 防止整型溢出。
 * 4. 若 nums[mid] == target，直接命中返回 mid。
 * 5. 若 nums[mid] < target，说明插入点在右侧，left = mid + 1。
 * 6. 若 nums[mid] > target，说明插入点在左侧，right = mid - 1。
 * 7. 循环结束时，left 即为目标值所在位置或其应当插入的索引位置。
 */

#include <vector>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;

        while (left <= right) {
            // 底层优化：避免 (left + right) 可能产生的溢出
            int mid = left + (right - left) / 2;

            if (nums[mid] == target) {
                return mid; // 完美匹配
            } else if (nums[mid] < target) {
                left = mid + 1; // 目标在右半区
            } else {
                right = mid - 1; // 目标在左半区
            }
        }

        /**
         * 为什么返回 left？
         * 循环终止条件是 left > right。
         * 此时 left 指向第一个大于 target 的元素，
         * right 指向最后一个小于 target 的元素。
         * 插入位置恰好就是 left。
         */
        return left;
    }
};