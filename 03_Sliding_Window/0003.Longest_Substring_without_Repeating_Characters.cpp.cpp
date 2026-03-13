/**
 * @file 003_Longest_Substring_Without_Repeating_Characters.cpp
 * @brief 3. 无重复字符的最长子串
 * @link <https://leetcode.cn/problems/longest-substring-without-repeating-characters/>
 *
 * @algorithm 滑动窗口 (Sliding Window) + 哈希表 (Hash Map / Array)
 *
 * @time_complexity O(N)
 * @space_complexity O(1)
 *
 * @note 核心思路 (滑动窗口)：
 * 1. 窗口定义：[left, right] 区间内的字符就是我们当前考察的“无重复子串”。
 * 2. 状态记录：使用 unordered_map 记录每个字符**最后一次出现的下标**。
 * 3. 窗口扩张：右指针 right 主动向右移动，每次尝试把新字符 s[right] 纳入窗口。
 * 4. 窗口收缩：
 *    - 如果 s[right] 已经在窗口里了（发生重复！），说明当前窗口“无效”了。
 *    - 左指针 left 开始向右移动，并且把移出窗口的字符从记录中删掉。
 *    - 直到把那个与 s[right] 发生冲突的“罪魁祸首”移出窗口为止。
 * 5. 更新答案：在每次窗口处于“有效状态”（不包含重复字符）时，
 *    计算当前窗口的长度 (right - left + 1)，并更新全局最大长度 maxLength。
 */

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int lengthOfLongestSubstring(string s) {
        int len = s.length();
        if (len < 2) return len;

        //用哈希表记录字符最后一次出现的下标
        unordered_map<char,int> charIdxMap;
        
        int maxLength = 0;
        int left = 0;
        for(int right = 0; right < len; right++)
        {
            char currentChar = s[right];
            if(charIdxMap.count(currentChar)) //说明窗口内出现过该字符了！
            {
                left = max(left,charIdxMap[currentChar] + 1);  //防止倒车！！
            }
            //更新或者插入当前字符的最新下标！
            charIdxMap[currentChar] = right;

            //此时窗口是无重复的！
            int currentLength = right - left + 1;
            maxLength = max(maxLength,currentLength);
        }

        return maxLength;
    }
};