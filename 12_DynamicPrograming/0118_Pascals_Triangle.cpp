/**
 * @file 0118_Pascals_Triangle.cpp
 * @brief 118. 杨辉三角
 * @link https://leetcode.cn/problems/pascals-triangle/
 *
 * @algorithm 动态规划 / 递推
 * @time_complexity O(N^2) - N 为 numRows。我们需要填充的总元素个数为 N*(N+1)/2，每个元素的计算时间为 O(1)。
 * @space_complexity O(1) - 除了保存返回结果所需的空间外，仅使用了常数级别的辅助变量。
 *
 * @note 核心思路：
 * 1. 杨辉三角的每一行长度为行索引加一，即第 i 行有 i+1 个元素。
 * 2. 每一行的首尾元素（j = 0 和 j = i）固定为 1。
 * 3. 每一行的中间元素通过状态转移方程 res[i][j] = res[i-1][j-1] + res[i-1][j] 计算。
 * 4. 采用 resize 事先为每一行分配空间，可以避免频繁 push_back，提升运行效率。
 */

#include <vector>

using namespace std;

class Solution {
public:
    vector<vector<int>> generate(int numRows) {
        // 创建外层 vector，大小为 numRows，用来存放整个杨辉三角的所有行
        vector<vector<int>> res(numRows);
        
        // 外层循环：控制生成的行数，行索引 i 从 0 到 numRows - 1
        for (int i = 0; i < numRows; ++i) {
            
            // 1. 动态调整当前行的大小：杨辉三角的第 i 行（从 0 开始）恰好有 i + 1 个元素
            res[i].resize(i + 1);
            
            // 2. 初始化边界条件：每一行的第一个元素和最后一个元素的值必然为 1
            res[i][0] = 1;      // 首元素
            res[i][i] = 1;      // 尾元素
            
            // 3. 填充中间元素：当第 i 行拥有多于 2 个元素时（即 i >= 2 时），才会有中间元素
            //    内层循环范围是 [1, i - 1]，正好避开了已经初始化的首尾边界
            for (int j = 1; j < i; ++j) {
                // 根据状态转移方程：当前元素 = 上一行的左上方元素 + 上一行的正上方元素
                res[i][j] = res[i - 1][j - 1] + res[i - 1][j];
            }
        }
        
        // 返回构造完成的二维动态数组
        return res;
    }
};