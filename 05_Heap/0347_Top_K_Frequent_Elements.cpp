
/**
 * @file 347_Top_K_Frequent_Elements.cpp
 * @brief 347. 前 K 个高频元素
 * @link https://leetcode.cn/problems/top-k-frequent-elements/
 * 
 * @algorithm 哈希表 (统计频率) + 优先级队列/堆 (Priority Queue)
 * 
 * @time_complexity O(N log K) 
 *      - 统计频率：O(N)
 *      - 维护一个大小为 K 的堆：O(N log K)
 *      - 总复杂度：O(N log K)
 * 
 * @space_complexity O(N)
 *      - 哈希表存储所有元素频率 O(N)，堆存储 K 个元素 O(K)。
 * 
 * @note 核心思路 (堆的艺术)：
 * 1. 统计频率：遍历数组，用 unordered_map<int, int> 记录 <数值, 出现次数>。
 * 2. 建立小顶堆 (Min-Heap)：
 *    - 这里是本题的神来之笔！我们要找“前 K 个最大”，为什么要用“小顶堆”？
 *    - 维护一个大小为 K 的小顶堆。
 *    - 当堆没满时，直接塞入。
 *    - 当堆满了，如果新元素比堆顶（堆里最小的）还大，就把堆顶扔掉，塞入新元素。
 *    - 最后堆里留下的，就是全数组里最大的 K 个元素！
 * 3. 为什么不用大顶堆？
 *    - 建立大顶堆需要 O(N) 的空间把所有元素放进去，然后再 pop K 次，这是 O(N + K log N)。
 *    - 用小顶堆维护大小为 K 的容器，空间只需 O(K)，更加高效。
 */
#include <vector>
#include <unordered_map>
#include <queue> 

using namespace std;

class Solution{

public:
    vector<int> topKFrequent(vector<int>& nums,int k)
    {
        unordered_map<int,int> counts;

        for(int num : nums)
        {
            counts[num]++;
        }

        typedef pair<int,int> PII;
        priority_queue<PII,vector<PII>,greater<PII>> minHeap;

        for(auto& pair : counts)
        {
            minHeap.push({pair.second,pair.first});
            if(minHeap.size() > k)
            {
                minHeap.pop();
            }
        }

        vector<int> ans;
        ans.reserve(k);  //提前分配内存，防止多次扩容

        while(!minHeap.empty()){
            ans.push_back(minHeap.top().second);
            minHeap.pop();
        }
        return ans;
    }
};