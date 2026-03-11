/**
 * @file 011_Container_With_Most_Water.cpp
 * @brief 11. 盛最多水的容器
 * @link <https://leetcode.cn/problems/container-with-most-water/>
 *
 * @algorithm 双指针 (左右相向指针 Left & Right Pointers) + 贪心 (Greedy)
 *
 * @time_complexity O(N)
 *      - 两个指针分别从数组两端向中间移动，相遇时停止。
 *      - 整个数组的每个元素最多只被访问一次，总共执行 N 步。
 *
 * @space_complexity O(1)
 *      - 只需要常数级别的额外空间来存储指针和最大面积。
 *
 * @note 核心思路 (木桶原理)：
 * 1. 容器的容量由两方面决定：
 *    - 宽度：两个指针之间的距离 (right - left)
 *    - 高度：两块木板中**较短**的那一块决定了水位 (min(height[left], height[right]))
 *    - 面积 = 宽度 × 高度
 *
 * 2. 初始状态下，我们把指针放在最左边 (left=0) 和最右边 (right=n-1)。
 *    此时**宽度是最大的**，如果想要得到更大的面积，我们只能去寻找**更高**的木板。
 *
 * 3. 贪心策略：移动哪块木板？
 *    - 如果我们移动**较高**的木板，宽度一定变小，而新的高度最多只能受限于那块没动的**较短**木板。
 *      因此，无论新的木板多高，面积**一定**会变小或不变，绝不可能变大！
 *    - 所以，我们**必须**移动那块**较短**的木板，去赌下一个木板足够高，从而弥补宽度变小带来的损失。
 *
 * 4. 每次计算当前面积，更新全局最大面积，然后移动较短板的指针，直到相遇。
 */

#include <vector>
#include <algorithm> // 为了使用 std::max 和 std::min

using namespace std;

class Solution {
public:
    int maxArea(vector<int>& height) {
        //边界条件判断
        if(height.size() < 2){ //有两块以上的板才能构成容器，虽然题目限制此处n>2;
            return 0;
        }

        int left = 0;                     
        int right = height.size() - 1;    
        int max_area = 0;                 

        // 当左指针严格小于右指针时，说明还可以构成容器
        while (left < right) {

            int current_area = (right - left) * min(height[left], height[right]);

            max_area = max(max_area, current_area);

            // 贪心决策：哪块板子短，就抛弃哪块板子，向内寻找更高的可能
            if (height[left] < height[right]) {
                left++;  // 左板短，左指针右移
            } else {
                right--; // 右板短 (或两板一样高)，右指针左移
            }
        }
        return max_area;
    }
};
