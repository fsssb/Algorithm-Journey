/**
 * @file 0347_Top_K_Frequent_Elements.cpp
 * @brief 347. 前 K 个高频元素
 * @link https://leetcode.cn/problems/top-k-frequent-elements/
 * 
 * @algorithm Hash Map + Min-Heap (小顶堆)
 * @time_complexity O(N log K) - N 为元素个数，堆维护成本为 log K
 * @space_complexity O(N)      - 哈希表存储所有不重复元素
 * 
 * @note 核心思路：
 * 1. 统计频率。
 * 2. 维护大小为 K 的小顶堆。堆顶是当前 Top K 中频率最低的。
 * 3. 遍历完后，堆中剩下的就是最高频的 K 个。
 */

#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    vector<int> topKFrequent(vector<int>& nums, int k) {
        // 1. 统计频率：工业级优化，预留空间防止多次 Rehash
        unordered_map<int, int> counts;
        counts.reserve(nums.size()); 
        for (int num : nums) {
            counts[num]++;
        }

        // 2. 小顶堆：pair.first 是频率，pair.second 是元素
        // 使用 greater 定义小顶堆，让最小频率排在 top
        using pii = pair<int, int>;
        priority_queue<pii, vector<pii>, greater<pii>> pq;

        for (auto const& [val, freq] : counts) {
            if (pq.size() < k) {
                pq.push({freq, val});
            } else if (freq > pq.top().first) {
                pq.pop();
                pq.push({freq, val});
            }
        }

        // 3. 构造结果：堆内元素即为所求
        vector<int> res;
        res.reserve(k);
        while (!pq.empty()) {
            res.push_back(pq.top().second);
            pq.pop();
        }
        return res;
    }
};