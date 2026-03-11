/**
 * @file 0001_Two_Sum.cpp
 * @brief 1. 两数之和
 * @link https://leetcode.cn/problems/two-sum/
 * 
 * @algorithm Hash Map
 * @time_complexity O(N)  - 只需遍历一次数组
 * @space_complexity O(N) - 需要一个哈希表存 N 个元素
 * 
 * @note 核心思路：
 * 准备一个 unordered_map<数值, 下标>。
 * 遍历数组，对于当前数字 x，去 map 里找有没有 (target - x)。
 * 如果有，直接返回下标；如果没有，把自己存进 map 里，继续往后找。
 */

#include <vector>
#include <unordered_map>

using namespace std; 

class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        unordered_map<int, int> idx;//创建一个空的哈希表
        
        for (int i = 0; i < nums.size(); i++) {  //边界条件不可漏
            auto it = idx.find(target - nums[i]);
            if(it != idx.end())
            {
                return {it->second,i};
            }
            idx[nums[i]] = i; 
        }
        return {};//返回兜底！
    }
};

