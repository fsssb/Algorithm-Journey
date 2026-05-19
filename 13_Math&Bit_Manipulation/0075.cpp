/**
 * @file 0075_Sort_Colors.cpp
 * @brief 75. 颜色分类
 * @link https://leetcode.cn/problems/sort-colors/
 * 
 * @algorithm Three-pointer Partitioning (三指针划分)
 * @time_complexity O(N)  - 只需一次遍历
 * @space_complexity O(1) - 原地交换，无额外内存分配
 * 
 * @note 核心思路：
 * 1. p0 维护 0 的右边界，p2 维护 2 的左边界。
 * 2. 遍历过程中，将 0 扔到左边，将 2 扔到右边，1 自然留在中间。
 * 3. 交换 2 时不移动 curr，是防止漏检从后端交换回来的 0。
 */

#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    void sortColors(vector<int>& nums) {
        int n = static_cast<int>(nums.size());
        int p0 = 0;
        int curr = 0;
        int p2 = n - 1;

        while (curr <= p2) {
            if (nums[curr] == 0) {
                // 将 0 交换到左侧区域
                swap(nums[curr], nums[p0]);
                p0++;
                curr++;
            } 
            else if (nums[curr] == 2) {
                // 将 2 交换到右侧区域
                swap(nums[curr], nums[p2]);
                p2--;
                // 重要：此处 curr 不增加，需在下一轮处理交换回来的新值
            } 
            else {
                // 遇到 1，保持原位，指针后移
                curr++;
            }
        }
    }
};

/*
class Solution {
public:
    void sortColors(vector<int>& nums){
        int n = static_cast<int>(nums.size());
        int ptr = 0;
        for(int i = 0; i < n; ++i){
            if(nums[i] == 0){
                swap(nums[i],nums[ptr]);
                ++ptr;
            }
        }
        for(int i = ptr; i < n;++i){
            if(nums[i] == 1){
                swap(nums[i],nums[ptr]);
                ++ptr;
            }
        }
    }
};
*/
