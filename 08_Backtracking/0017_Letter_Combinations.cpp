/**
 * @file 0017_Letter_Combinations.cpp
 * @brief 17. 电话号码的字母组合
 * @link https://leetcode.cn/problems/letter-combinations-of-a-phone-number/
 * 
 * @algorithm 回溯 (Backtracking)
 * @time_complexity O(3^N * 4^M) 
 *      - N 是对应 3 个字母的数字个数，M 是对应 4 个字母的数字个数。
 * @space_complexity O(N + M) 
 *      - 递归栈深度等于输入字符串的长度。
 * 
 * @note 核心思路：
 * 1. 映射建模：首先建立数字到字母集合的映射表。
 * 2. 跨集合组合：本题与“子集”或“全排列”最大的区别在于，它是从【多个独立集合】中各取一个元素。
 * 3. 递归深度控制：使用一个 index 记录当前正在处理 digits 中的第几个数字。
 * 4. 现场恢复：在每一层循环结束后，执行 pop_back() 以保证 path 能被下一条路径复用。
 */

#include <vector>
#include <string>

using namespace std;

class Solution {
private:
    // 侯捷提示：使用静态常量数组作为映射表，避免每次调用函数都重新分配内存
    const string letterMap[10] = {
        "",     // 0
        "",     // 1
        "abc",  // 2
        "def",  // 3
        "ghi",  // 4
        "jkl",  // 5
        "mno",  // 6
        "pqrs", // 7
        "tuv",  // 8
        "wxyz"  // 9
    };

    vector<string> result;
    string path;

    /**
     * @brief 回溯核心
     * @param index 指向当前正在处理 digits 的第几个按键
     */
    void backtracking(const string& digits, int index) {
        // 1. 终止条件：处理完了所有的数字按键
        if (index == digits.size()) {
            result.push_back(path);
            return;
        }

        // 2. 取出当前按键对应的字母集
        int digit = digits[index] - '0'; // 字符转整数
        string letters = letterMap[digit];

        // 3. 遍历当前按键对应的所有字母
        for (int i = 0; i < letters.size(); ++i) {
            path.push_back(letters[i]);     // 修改现场
            backtracking(digits, index + 1); // 递归：处理下一个按键
            path.pop_back();                // 恢复现场
        }
    }

public:
    vector<string> letterCombinations(string digits) {
        if (digits.empty()) return {};
        
        // 性能优化：根据数学预期提前分配结果集空间
        // 虽本题 digits 长度较小，但这是工业级 C++ 的良好习惯
        result.clear();
        path.clear();
        
        backtracking(digits, 0);
        return result;
    }
};