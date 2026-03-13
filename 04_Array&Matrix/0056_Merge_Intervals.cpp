/**
 * @file 056_Merge_Intervals.cpp
 * @brief 56. 合并区间
 * @link <https://leetcode.cn/problems/merge-intervals/>
 *
 * @algorithm 排序 (Sorting) + 贪心遍历
 *
 * @time_complexity O(N log N)
 *      - N 是区间的数量。
 *      - 排序的时间复杂度为 O(N log N)。
 *      - 遍历一遍数组的时间复杂度为 O(N)。
 *      - 总时间复杂度由排序主导，为 O(N log N)。
 *
 * @space_complexity O(log N)
 *      - C++ 的 std::sort 内部使用的是 IntroSort，其递归栈的深度为 O(log N)。
 *      - 不考虑存储返回结果的额外空间。
 *
 * @note 核心思路：
 * 1. 【排序是灵魂】：如果不排序，判断两个区间是否重叠的逻辑会极其复杂 (O(N^2))。
 *    我们必须先按照每个区间的**左端点 (起点)** 从小到大排序。
 *    排序后，能合并的区间一定在数组中是连续相邻的。
 *
 * 2. 【维护一个当前合并区间】：
 *    - 我们拿数组的第一个区间作为初始的“当前合并区间”。
 *    - 遍历后续的区间：
 *      - 场景 A (重叠)：如果下一个区间的**左端点** <= 当前区间的**右端点**，
 *        说明有交集！我们更新当前区间的右端点为两者右端点的最大值 (`max`)。
 *      - 场景 B (不重叠)：如果下一个区间的**左端点** > 当前区间的**右端点**，
 *        说明断开了！当前的合并区间已经完全确定，把它推入结果数组中，
 *        然后把这个新区间作为新的“当前合并区间”。
 *
 * 3. 遍历结束后，别忘了把最后一个停留在手中的“当前合并区间”推入结果数组。
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


class Solution
{
public:
    vector<vector<int>> merge(vector<vector<int>>& intervals){
        if(intervals.size() <= 1){
            return intervals;
        }

        sort(intervals.begin(),intervals.end());

        vector<vector<int>> ans;
        
        int left = intervals[0][0];
        int right = intervals[0][1];

        for(int i = 1; i < intervals.size(); ++i)
        {
            if(intervals[i][0] <= right){
                right = max(right,intervals[i][1]); 
            }
            else{
                ans.push_back({left,right});
                left = intervals[i][0];
                right = intervals[i][1];
            }
        }
        ans.push_back({left,right});
        return ans;
    }
};


/*
    对比一下：“为什么你要用两个 int 变量，而不是用一个 vector<int> 来暂存当前合并的区间？
*/

// // 1. 在内存堆 (Heap) 上申请空间，并且发生一次数组深拷贝
// vector<int> currentInterval = intervals[0]; 

// for (int i = 1; i < intervals.size(); i++) {
//     if (intervals[i][0] <= currentInterval[1]) {
//         // 2. 访问 vector 元素，底层是指针加偏移量的寻址
//         currentInterval[1] = max(currentInterval[1], intervals[i][1]);
//     } else {
//         result.push_back(currentInterval);
//         // 3. 再次发生 vector 对象的赋值（深拷贝或移动）
//         currentInterval = intervals[i];
//     }
// }



// // 1. 在栈 (Stack) 上创建两个 4 字节的整数，直接塞进 CPU 寄存器
// int left = intervals[0][0];
// int right = intervals[0][1];

// for (int i = 1; i < intervals.size(); i++) {
//     if (intervals[i][0] <= right) {
//         // 2. 直接在寄存器里做比较和赋值，速度极快
//         right = max(right, intervals[i][1]);
//     } else {
//         ans.push_back({left, right});
//         // 3. 仅仅是两个 4 字节整数的赋值
//         left = intervals[i][0];
//         right = intervals[i][1];
//     }
// }