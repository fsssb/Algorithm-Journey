/**
 * @file 0394_Decode_String.cpp
 * @brief 394. 字符串解码
 * @link https://leetcode.cn/problems/decode-string/
 * 
 * @algorithm Dual Stack Parsing (双栈解析状态机)
 * @time_complexity O(S) - S 为解码后的字符串长度，每个字符仅被处理常数次
 * @space_complexity O(S) - 栈空间开销，最坏情况取决于嵌套深度和结果长度
 * 
 * @note 核心思路：
 * 1. 维护当前倍数 multi 和当前字符串 res。
 * 2. 遇到 '['：将 multi 和 res 入栈，随后清空，开启新层级。
 * 3. 遇到 ']'：弹出栈顶的上层 res 和倍数，将当前 res 重复后拼接。
 * 4. 字符串优化：使用 reserve 或避免频繁分配（本题结果长度不确定，重点在逻辑）。
 */

#include <string>
#include <stack>
#include <vector>
#include <iostream>

using namespace std;

class Solution {
public:
    string decodeString(string s) {
        string res = "";
        int multi = 0;
        stack<int> countStack;
        stack<string> resStack;

        for (char c : s) {
            if (c == '[') {
                // 1. 存档当前状态
                countStack.push(multi);
                resStack.push(res);
                // 2. 清空状态，准备接收括号内的内容
                multi = 0;
                res = "";
            } else if (c == ']') {
                // 3. 读档：弹出倍数和上层字符串
                int curMulti = countStack.top();
                countStack.pop();
                string lastRes = resStack.top();
                resStack.pop();
                
                // 4. 合并：上层结果 + 倍数 * 当前括号内结果
                string tmp = "";
                for (int i = 0; i < curMulti; ++i) tmp += res;
                res = lastRes + tmp;
            } else if (isdigit(c)) {
                // 5. 处理多位数字
                multi = multi * 10 + (c - '0');
            } else {
                // 6. 普通字符追加
                res += c;
            }
        }
        return res;
    }
};


// int main(){
//     string s = "3[a2[c]]";
//     Solution sol;
//     string result = sol.decodeString(s);
//     cout << result << endl;

//     return 0;
// }