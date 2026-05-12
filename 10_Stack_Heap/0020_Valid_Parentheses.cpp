/**
 * @file 0020_Valid_Parentheses.cpp
 * @brief 20. 有效的括号
 * @link https://leetcode.cn/problems/valid-parentheses/
 * 
 * @algorithm Stack (栈)
 * @time_complexity O(N)  - 遍历一次字符串
 * @space_complexity O(N) - 最坏情况下（全是左括号）栈占用 N 个字符空间
 * 
 * @note 核心思路：
 * 1. 奇数长度预处理：长度为奇数必然不匹配。
 * 2. 哈希表映射：使用 unordered_map 存储右括号到左括号的映射，增加扩展性。
 * 3. 栈操作：遇到左括号入栈，遇到右括号弹出栈顶元素进行匹配。
 * 4. 最终状态检查：匹配完成后栈必须为空。
 */

#include <string>
#include <stack>
#include <unordered_map>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        // 1. 早期退出：奇数长度直接排除
        if (s.size() % 2 != 0) return false;

        // 2. 映射表：右括号作为 Key，方便在匹配时查找期望的左括号
        static const unordered_map<char, char> pairs = {
            {')', '('},
            {']', '['},
            {'}', '{'}
        };

        stack<char> st;

        for (char ch : s) {
            // 如果是右括号
            if (pairs.count(ch)) {
                // 如果栈为空（说明右括号多余）或者栈顶不匹配
                if (st.empty() || st.top() != pairs.at(ch)) {
                    return false;
                }
                st.pop(); // 匹配成功，弹出
            } 
            // 如果是左括号
            else {
                st.push(ch);
            }
        }

        // 最后检查栈内是否还有残留的左括号
        return st.empty();
    }
};