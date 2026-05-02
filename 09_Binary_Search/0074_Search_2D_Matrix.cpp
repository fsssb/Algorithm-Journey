/**
 * @file 0074_Search_a_2D_Matrix.cpp
 * @brief 74. 搜索二维矩阵
 * @link https://leetcode.cn/problems/search-a-2d-matrix/
 * 
 * @algorithm Binary Search on Flattened Matrix (一维化二分查找)
 * @time_complexity O(log(M * N)) - M 为行数，N 为列数，单次二分即可覆盖全矩阵
 * @space_complexity O(1)         - 仅使用常数个整型变量
 * 
 * @note 核心思路：
 * 1. 视矩阵为连续线性空间。全长 L = m * n。
 * 2. 二分范围 [0, L - 1]。
 * 3. 关键点：通过 mid / n 和 mid % n 将一维中点映射回二维空间进行取值。
 * 4. 该方法比“先二分行再二分列”代码更简洁，且边界处理更统一。
 */

#include <vector>

using namespace std;

class Solution{

public:
    bool searchMatrix(vector<vector<int>>& matrix,int target)
    {
        if(matrix.empty() || matrix[0].empty()) return false;
    
        int m = static_cast<int>(matrix.size());
        int n = static_cast<int>(matrix[0].size());
        int left = 0;
        int right = m * n - 1;

        while(left <= right)
        {
            int mid = left + (right - left) / 2;            
            /**
             * 映射逻辑 (Tensor Indexing Logic):
             * 行号 = 总偏移 / 每行元素个数
             * 列号 = 总偏移 % 每行元素个数
             */
            int row = mid / n;
            int col = mid % n;

            if(matrix[row][col] == target)
            {
                return true;
            }
            else if(matrix[row][col] < target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return false;
    }
};