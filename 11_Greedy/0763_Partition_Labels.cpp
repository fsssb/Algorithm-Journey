/**
 * @file 0763_Partition_Labels.cpp
 * @brief 763. 划分字母区间
 * @link https://leetcode.cn/problems/partition-labels/
 * 
 * @algorithm Greedy with Boundary Tracking (贪心边界追踪)
 * @time_complexity O(N)  - 两次线性扫描（预处理 + 划分）
 * @space_complexity O(1) - 辅助空间仅为固定大小的 26 长度数组
 * 
 * @note 核心思路：
 * 1. 预处理记录每个字母最后出现的下标。
 * 2. 遍历过程中动态更新当前分区内字符所能触达的最远边界 end。
 * 3. 当遍历索引 i 触及 end 时，完成一个分区的切分。
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> partitionLabels(string s) {
        int n = static_cast<int>(s.size());
        // 1. 预处理：利用栈空间或静态区分配固定大小数组，避免堆内存抖动
        int last_pos[26] = {0};
        for (int i = 0; i < n; ++i) {
            last_pos[s[i] - 'a'] = i;
        }

        vector<int> res;
        int start = 0;
        int end = 0;

        // 2. 贪心划分
        for (int i = 0; i < n; ++i) {
            // 更新当前分区必须覆盖的最远位置
            end = max(end, last_pos[s[i] - 'a']);
            
            // 如果当前索引已到达已知的最远边界，说明分区可以闭合
            if (i == end) {
                res.push_back(end - start + 1);
                start = i + 1;
            }
        }

        return res;
    }
};