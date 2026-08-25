/**
 * @file 0239_Sliding_Window_Maximum.cpp
 * @brief 239. 滑动窗口最大值
 * @link https://leetcode.cn/problems/sliding-window-maximum/
 *
 * @algorithm 单调队列 (Monotonic Queue / std::deque)
 *
 * @time_complexity O(N)
 *      - 每个下标最多入队一次、出队一次，总共约 2N 次操作。
 *      - 对比暴力解 O(N*K) ≈ 2.5e9 次比较（n=k/2=5e4 时），本解约 2e5 次，稳过。
 *
 * @space_complexity O(K)
 *      - deque 最多同时存放窗口内 K 个下标。
 *
 * @note 核心思路（三句话版）：
 * 1. deque 存"下标"（不存值）：判断队头是否滑出窗口需要靠下标与窗口左界 i-k+1 比较。
 * 2. 入队前从队尾碾压：队尾所有值 <= 新元素的下标全部弹出。
 *    —— 被碾压者比新元素小，且更早过期，未来任何它在窗口内的时刻新元素必也在，
 *       它永远成不了最大值，踢掉零影响。
 * 3. 碾压用 <= 而非 <：同值后来者优先（更晚过期），旧同值没机会翻身。
 * 4. 队头只检查一次：队头是队列中最先入队者，它没过期则全员未过期。
 * 5. i >= k-1 时窗口成形，队头即为当前窗口最大值。
 */

#include <deque>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k)
    {
        vector<int> res;
        deque<int> dq;  // 存下标，队头到队尾对应值严格递减

        for (int i = 0; i < nums.size(); ++i)
        {
            // ① 队尾碾压：弹出所有值 <= nums[i] 的下标
            while (!dq.empty() && nums[dq.back()] <= nums[i])
            {
                dq.pop_back();
            }
            dq.push_back(i);

            // ② 队头过期检查：队头下标已滑出窗口左界则弹出
            if (dq.front() < i - k + 1)
            {
                dq.pop_front();
            }

            // ③ 取答案：窗口成形后队头即最大值
            if (i >= k - 1)
            {
                res.push_back(nums[dq.front()]);
            }
        }
        return res;
    }
};
