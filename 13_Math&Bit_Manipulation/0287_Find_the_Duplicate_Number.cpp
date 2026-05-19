/**
 * @file 0287_Find_the_Duplicate_Number.cpp
 * @brief 287. 寻找重复数
 * @link https://leetcode.cn/problems/find-the-duplicate-number/
 * 
 * @algorithm Floyd's Cycle-Finding Algorithm (快慢指针/龟兔赛跑)
 * @time_complexity O(N)  - 线性扫描，寻找环入口
 * @space_complexity O(1) - 仅使用两个指针变量，不修改原数组
 * 
 * @note 核心思路：
 * 1. 将数组值视为指向下一个下标的指针，建立逻辑链表。
 * 2. 第一阶段：通过 fast = nums[nums[fast]] 和 slow = nums[slow] 找到环内交点。
 * 3. 第二阶段：从起点和交点同步出发，步长为 1，再次相遇处即为环入口（重复数）。
 */

#include <vector>

using namespace std;

class Solution {
public:
    int findDuplicate(vector<int>& nums) {
        // 初始化：由于值从 1 开始，0 不会在环内，作为安全起点
        int slow = nums[0];
        int fast = nums[nums[0]];

        // 阶段一：寻找相遇点
        while (slow != fast) {
            slow = nums[slow];
            fast = nums[nums[fast]];
        }

        // 阶段二：寻找环入口
        int ptr1 = 0;
        int ptr2 = slow;
        while (ptr1 != ptr2) {
            ptr1 = nums[ptr1];
            ptr2 = nums[ptr2];
        }

        return ptr1;
    }
};