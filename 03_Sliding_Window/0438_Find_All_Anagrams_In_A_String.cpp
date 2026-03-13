/**
 * @file 438_Find_All_Anagrams.cpp
 * @brief 438. 找到字符串中所有字母异位词
 * @link <https://leetcode.cn/problems/find-all-anagrams-in-a-string/>
 *
 * @algorithm 定长滑动窗口 (Fixed-size Sliding Window) + 频次数组
 *
 * @time_complexity O(N)
 *      - N 是字符串 s 的长度。
 *      - 窗口滑动时，每次只有一次加法、一次减法和一次数组比较（比较 26 个元素是 O(1)）。
 *
 * @space_complexity O(1)
 *      - 只需要两个长度固定为 26 的 vector，不随数据规模增长。
 */

#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution{

public:
    vector<int> findAnagrams(string& s,string& p)
    {
        vector<int> result;
        int sLen =  s.length();
        int pLen = p.length();
        
        if(sLen < pLen) return result;  //边界判断

        vector<int> pCount(26,0);
        vector<int> sCount(26,0);
        
        for(int i = 0; i < pLen; i++)
        {
            pCount[p[i] - 'a'] ++;  //字符偏移法
            sCount[s[i] - 'a'] ++;
        }

        if(sCount == pCount){
            result.push_back(0);
        }

        for(int i = pLen; i < sLen; i++) 
        {
            //只需要处理窗口的头和尾，一进一出！
            sCount[s[i] - 'a'] ++;

            sCount[s[i - pLen] - 'a'] --;

            if(sCount == pCount)  //C++ vector的operator==运算符重载!
            {
                result.push_back(i - pLen + 1);
            }
        }
        return result;
    }
};













/*
    TLE
*/
// class Solution{

// public:
//     vector<int> findAnagrams(string& s,string& p)
//     {
//         vector<int> result{};
        
//         if(p.length() > s.length()) return{};
//         for(int i = 0; i < s.length() - p.length() + 1; i++)
//         {
//             string currentStr = s.substr(i,p.length());
//             sort(p.begin(),p.end());
//             sort(currentStr.begin(),currentStr.end());
//             if(currentStr == p)
//             {
//                 result.push_back(i);
//             }
//         }
//         return result;
//     }
// };