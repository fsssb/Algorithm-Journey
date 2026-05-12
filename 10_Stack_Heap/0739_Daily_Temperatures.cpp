/**
 * @file 0739_Daily_Temperatures.cpp
 * @brief 739. 每日温度
 * @link https://leetcode.cn/problems/daily-temperatures/
 * 
 * @algorithm Monotonic Stack (单调栈)
 * @time_complexity O(N)  - 每个元素进出栈各一次
 * @space_complexity O(N) - 栈空间开销，最坏情况为单调递减数组
 * 
 * @note 核心思路：
 * 1. 维护一个存储下标的单调递减栈。
 * 2. 遍历温度数组，若当前温度大于栈顶下标对应的温度，则栈顶找到了其“下一个更大值”。
 * 3. 弹出栈顶，计算下标差值即为等待天数。
 * 4. 这种“暂时存起来，等后面人来救”的逻辑是处理“右侧第一个更大值”问题的标准范式。
 */

#include <vector>
#include <stack>

using namespace std;

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        int n = static_cast<int>(temperatures.size());
        // 预分配空间：避免 vector 动态扩容产生的拷贝开销
        vector<int> res(n, 0);
        
        // 性能优化：使用 vector 模拟栈比 std::stack (基于 deque) 具有更好的缓存局部性
        // 但为了逻辑通用性，此处先使用标准 stack
        stack<int> st;

        for (int i = 0; i < n; ++i) {
            // 当前温度 > 栈顶温度时，说明栈顶找到了答案
            while (!st.empty() && temperatures[i] > temperatures[st.top()]) {
                int prev_index = st.top();
                st.pop();
                res[prev_index] = i - prev_index;
            }
            // 每一个索引必然入栈一次
            st.push(i);
        }

        return res;
    }
};