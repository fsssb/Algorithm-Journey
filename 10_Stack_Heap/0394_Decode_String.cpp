/**
 * @file 0394_Decode_String_Optimized.cpp
 * @brief 394. 字符串解码 (高性能优化版)
 * 
 * @algorithm Dual Stack + Memory Pre-allocation
 * @note 优化点：
 * 1. 精确的 reserve 尺寸计算，降低 allocator 压力。
 * 2. 深度利用移动语义 (Move Semantics)，消除不必要的堆拷贝。
 * 3. 逻辑分明，符合状态机处理规范。
 */

#include <string>
#include <stack>

using namespace std;


class Solution {
public:
    string decodeString(string s) {
        string res = "";
        int multi = 0;
        stack<string> resStack;
        stack<int> countStack;

        for (char ch : s) {
            if (ch == '[') {
                resStack.push(std::move(res)); // 将当前 res 移入栈，避免拷贝
                countStack.push(multi);
                res = ""; // 重置为空串
                multi = 0;
            } else if (ch == ']') {
                int curMulti = countStack.top();
                countStack.pop();
                string lastRes = std::move(resStack.top());
                resStack.pop();

                // 核心优化 1：精确计算长度
                string tmp;
                tmp.reserve(res.size() * curMulti); 
                for (int i = 0; i < curMulti; ++i) {
                    tmp.append(res);
                }
                
                // 核心优化 2：原地追加并移动，彻底消除冗余对象
                lastRes.append(std::move(tmp));
                res = std::move(lastRes);
            } else if (isdigit(ch)) {
                multi = multi * 10 + (ch - '0');
            } else {
                res += ch;
            }
        }
        return res;
    }
};