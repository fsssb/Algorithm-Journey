/**
 * @file 054_Spiral_Matrix.cpp
 * @brief 54. 螺旋矩阵
 * @link https://leetcode.cn/problems/spiral-matrix/
 * 
 * @algorithm 四边界收缩法 (Boundary Shrinkage)
 * 
 * @time_complexity O(M * N)
 *      - M 是行数，N 是列数。每个元素恰好被访问并放入结果数组一次。
 * 
 * @space_complexity O(1)
 *      - 除了存储返回值的数组外，只使用了常数个指针/下标变量。
 * 
 * @note 核心思路：
 * 1. 定义四个边界：上(top)、下(bottom)、左(left)、右(right)。
 * 2. 按照“左到右 -> 上到下 -> 右到左 -> 下到上”的循环顺序进行遍历。
 * 3. 【关键逻辑】：每走完一个方向，对应的边界就要向内收缩一格，并立即判断是否已经越界。
 *    - 从左向右走完一行：top++。如果 top > bottom，说明全部走完，跳出循环。
 *    - 从上向下走完一列：right--。如果 left > right，跳出。
 *    - 从右向左走完一行：bottom--。如果 top > bottom，跳出。
 *    - 从下向上走完一列：left++。如果 left > right，跳出。
 */
#include <vector>
using namespace std;

class Solution {
public:
    vector<int> spiralOrder(vector<vector<int>>& matrix) {
        if (matrix.empty()) return {};

        int top = 0;
        int bottom = matrix.size() - 1; // 修改 1：指向最后一行
        int left = 0;
        int right = matrix[0].size() - 1; // 修改 2：指向最后一列
        
        vector<int> res;
        res.reserve((bottom + 1) * (right + 1));

        while (true) {
            // 场景 1: 左 -> 右
            for (int j = left; j <= right; ++j) { // 修改 3：<=
                res.push_back(matrix[top][j]);
            }
            if (++top > bottom) break; 

            // 场景 2: 上 -> 下
            for (int i = top; i <= bottom; ++i) {
                res.push_back(matrix[i][right]);
            }
            if (--right < left) break; 

            // 场景 3: 右 -> 左
            for (int j = right; j >= left; --j) {
                res.push_back(matrix[bottom][j]);
            }
            if (--bottom < top) break; 

            // 场景 4: 下 -> 上
            for (int i = bottom; i >= top; --i) {
                res.push_back(matrix[i][left]);
            }
            if (++left > right) break; 
        }
        return res; 
    }
};