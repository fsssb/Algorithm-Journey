/**
 * @file 0034_Find_First_and_Last_Position.cpp
 * @brief 34. 在排序数组中查找元素的第一个和最后一个位置
 * @link https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/
 * 
 * @algorithm Dual Binary Search (双边界二分搜索)
 * @time_complexity O(log N) - 两次独立的二分查找
 * @space_complexity O(1)    - 仅使用常数变量
 * 
 * @note 核心思路：
 * 1. 封装通用二分逻辑，通过 findBound(isFirst) 标志位控制边界收缩方向。
 * 2. 寻找起始位置：nums[mid] == target 时，继续向左(right = mid - 1)搜索。
 * 3. 寻找结束位置：nums[mid] == target 时，继续向右(left = mid + 1)搜索。
 * 4. 注意边界检查：判断最终找到的索引是否越界且值确实等于 target。
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<int> searchRange(vector<int>& nums, int target) {
        int first = findBound(nums, target, true);
        if (first == -1) return {-1, -1}; // 若找不到起点，终点必不存在

        int last = findBound(nums, target, false);
        return {first, last};
    }

private:
    /**
     * @param isFirst true 找左边界，false 找右边界
     */
    int findBound(const vector<int>& nums, int target, bool isFirst) {
        int left = 0;
        int right = static_cast<int>(nums.size()) - 1;
        int bound = -1;

        while (left <= right) {
            int mid = left + (right - left) / 2;

            if (nums[mid] < target) {
                left = mid + 1;
            } else if (nums[mid] > target) {
                right = mid - 1;
            } else {
                // 命中 target，记录位置并继续收缩区间
                bound = mid;
                if (isFirst) {
                    right = mid - 1; // 尝试寻找更靠左的匹配
                } else {
                    left = mid + 1;  // 尝试寻找更靠右的匹配
                }
            }
        }
        return bound;
    }
};