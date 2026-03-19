#include <vector>
#include <iostream>

using namespace std;
class Solution_1{
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();  //矩阵的长
        int n = matrix[0].size(); //矩阵的宽
        vector<bool> linHasZero(m,false);
        vector<bool> colHasZero(n,false);
        //找出zero所在位置
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(matrix[i][j] == 0)
                {
                    linHasZero[i] = true;
                    colHasZero[j] = true;
                }
            }
        }
        //遍历矩阵，按标志实现置零
        for(int i = 0; i < m; ++i)
        {
            for(int j = 0; j < n; ++j)
            {
                if(linHasZero[i] || colHasZero[j])
                {
                    matrix[i][j] = 0;
                }
            }
        }
    }
};
//时间复杂度：O(M*N)  两次嵌套循环。
//空间复杂度：O(m+n)  额外的两个布尔数组


/**
 * @file 073_Set_Matrix_Zeroes.cpp
 * @brief 73. 矩阵置零
 * @link https://leetcode.cn/problems/set-matrix-zeroes/
 * 
 * @algorithm 矩阵原地标记法 (Using first row and column as storage)
 * 
 * @time_complexity O(M * N)
 *      - 需要遍历整个矩阵两次。M 是行数，N 是列数。
 * 
 * @space_complexity O(1)
 *      - 我们利用了矩阵的第一行和第一列来存储标记，只用了常数个额外变量。
 * 
 * @note 核心思路：
 * 1. 为什么不能直接遍历，看到 0 就把整行整列改了？
 *    - 因为你会把原本不是 0 的元素改成 0，导致后面遍历时产生“连锁反应”，全矩阵变 0。
 * 
 * 2. 空间优化的进阶：
 *    - [普通] O(M*N)：拷贝一个完整的备份矩阵。
 *    - [中等] O(M+N)：用两个数组 row[M], col[N] 记录哪一行/哪一列该变 0。
 *    - [最优] O(1)：我们直接白嫖“矩阵的第一行和第一列”来充当上面的 row 和 col 数组！
 * 
 * 3. 具体步骤：
 *    - a. 先记录第一行和第一列原本是否有 0 (用两个 bool 变量)。
 *    - b. 遍历剩下的部分 [1...M][1...N]，如果发现 matrix[i][j] == 0，
 *         就在 matrix[i][0] 和 matrix[0][j] 做标记（设为 0）。
 *    - c. 根据标记，将对应的行和列置零。
 *    - d. 最后，根据第 a 步的记录，处理第一行和第一列自己。
 */



class Solution_2 {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        int m = matrix.size();
        int n = matrix[0].size();
        
        bool firstRowHasZero = false;
        bool firstColHasZero = false;

        // 1. 扫描第一列，检查是否有 0
        for (int i = 0; i < m; i++) {
            if (matrix[i][0] == 0) {
                firstColHasZero = true;
                break;
            }
        }

        // 2. 扫描第一行，检查是否有 0
        for (int j = 0; j < n; j++) {
            if (matrix[0][j] == 0) {
                firstRowHasZero = true;
                break;
            }
        }

        // 3. 使用第一行和第一列作为“标记位”
        // 扫描剩下的 [1...m-1][1...n-1]
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][j] == 0) {
                    matrix[i][0] = 0; // 标记该行
                    matrix[0][j] = 0; // 标记该列
                }
            }
        }

        // 4. 根据第一行/列的标记位，执行置零
        for (int i = 1; i < m; i++) {
            for (int j = 1; j < n; j++) {
                if (matrix[i][0] == 0 || matrix[0][j] == 0) {
                    matrix[i][j] = 0;
                }
            }
        }

        // 5. 最后单独处理第一行和第一列（因为它们被用来存标记了）
        if (firstColHasZero) {
            for (int i = 0; i < m; i++) matrix[i][0] = 0;
        }
        if (firstRowHasZero) {
            for (int j = 0; j < n; j++) matrix[0][j] = 0;
        }
    }
};

/* 
// --- 本地调试代码 ---
#include <iostream>
int main() {
    Solution sol;
    vector<vector<int>> matrix = {{0,1,2,0}, {3,4,5,2}, {1,3,1,5}};
    sol.setZeroes(matrix);
    
    // 预期输出: [[0,0,0,0], [0,4,5,0], [0,3,1,0]]
    for (const auto& row : matrix) {
        for (int val : row) cout << val << " ";
        cout << endl;
    }
    return 0;
}
*/