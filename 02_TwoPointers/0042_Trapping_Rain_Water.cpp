/**
 * @file 0042_Trapping_Rain_Water.cpp
 * @brief 42. 接雨水
 * @link https://leetcode.cn/problems/trapping-rain-water/
 *
 * @algorithm 1. DP 预处理 | 2. 双指针 | 3. 单调栈
 * @time_complexity
 *   - 方法 1 (DP 预处理)：O(N)
 *   - 方法 2 (双指针)：O(N)
 *   - 方法 3 (单调栈)：O(N)
 * @space_complexity
 *   - 方法 1 (DP 预处理)：O(N)
 *   - 方法 2 (双指针)：O(1)
 *   - 方法 3 (单调栈)：O(N)
 *
 * @note 核心思路：
 * 1. DP 预处理：提前计算每个位置左侧最高墙 leftMax[i] 和右侧最高墙 rightMax[i]，
 *    当前格水量为 min(leftMax[i], rightMax[i]) - height[i]。
 * 2. 双指针：两端向中间收缩，实时维护 leftMax 和 rightMax。先更新墙，再看短板；
 *    左短算左，右短算右。该方法是面试主推写法。
 * 3. 单调栈：栈中保存单调递减的柱子下标。遇到更高右墙时，弹出坑底，
 *    用 left / bottom / right 结算一个凹槽的水量。
 */

#include <algorithm>
#include <stack>
#include <vector>

class SolutionDP {
public:
    int trap(const std::vector<int>& height) {
        int n = static_cast<int>(height.size());
        if (n == 0) {
            return 0;
        }

        std::vector<int> leftMax(n);
        std::vector<int> rightMax(n);

        leftMax[0] = height[0];
        for (int i = 1; i < n; ++i) {
            leftMax[i] = std::max(leftMax[i - 1], height[i]);
        }

        rightMax[n - 1] = height[n - 1];
        for (int i = n - 2; i >= 0; --i) {
            rightMax[i] = std::max(rightMax[i + 1], height[i]);
        }

        int water = 0;
        for (int i = 0; i < n; ++i) {
            water += std::min(leftMax[i], rightMax[i]) - height[i];
        }

        return water;
    }
};

class SolutionTwoPointers {
public:
    int trap(const std::vector<int>& height) {
        int water = 0;
        int left = 0;
        int right = static_cast<int>(height.size()) - 1;
        int leftMax = 0;
        int rightMax = 0;

        while (left < right) {
            leftMax = std::max(leftMax, height[left]);
            rightMax = std::max(rightMax, height[right]);

            if (height[left] < height[right]) {
                water += leftMax - height[left];
                ++left;
            } else {
                water += rightMax - height[right];
                --right;
            }
        }

        return water;
    }
};

class SolutionMonotonicStack {
public:
    int trap(const std::vector<int>& height) {
        int water = 0;
        std::stack<int> st;

        for (int i = 0; i < static_cast<int>(height.size()); ++i) {
            while (!st.empty() && height[i] > height[st.top()]) {
                int bottom = st.top();
                st.pop();

                if (st.empty()) {
                    break;
                }

                int left = st.top();
                int width = i - left - 1;
                int boundedHeight = std::min(height[left], height[i]) - height[bottom];

                water += width * boundedHeight;
            }

            st.push(i);
        }

        return water;
    }
};

class Solution {
public:
    int trap(const std::vector<int>& height) {
        return SolutionTwoPointers().trap(height);
    }
};
