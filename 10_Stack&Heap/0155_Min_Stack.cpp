/**
 * @file 0155_Min_Stack.cpp
 * @brief 155. 最小栈
 * @link https://leetcode.cn/problems/min-stack/
 * 
 * @algorithm Auxiliary Stack (辅助栈同步记录)
 * @time_complexity O(1)  - push, pop, top, getMin 均为常数时间
 * @space_complexity O(N) - 额外使用一个辅助栈存储最小值序列
 * 
 * @note 核心思路：
 * 1. 维护两个栈：data_st (存数据), min_st (存当前状态下的最小值)。
 * 2. push 时：data_st 正常压入；min_st 压入当前值与原栈顶的较小者。
 * 3. pop 时：两个栈同时弹出，保持状态同步。
 * 4. getMin 时：直接返回 min_st 的栈顶。
 */

#include <stack>
#include <algorithm>

using namespace std;

class MinStack {
private:
    stack<int> data_st;
    stack<int> min_st;

public:
    /** initialize your data structure here. */
    MinStack() {
        // 在某些 Infra 实现中，这里可以执行 data_st.c.reserve() 
        // 但由于 stack 封装了 deque，无法直接 reserve，
        // 除非手动指定 vector 为底层容器。
    }
    
    void push(int val) {
        data_st.push(val);
        // 如果辅助栈为空，直接压入；否则压入当前值与辅助栈顶的最小值
        if (min_st.empty()) {
            min_st.push(val);
        } else {
            min_st.push(min(val, min_st.top()));
        }
    }
    
    void pop() {
        // 同步弹出，无需判断，由调用方保证栈非空（符合标准库行为）
        data_st.pop();
        min_st.pop();
    }
    
    int top() {
        return data_st.top();
    }
    
    int getMin() {
        return min_st.top();
    }
};