/**
 * @file 049_Group_Anagrams.cpp
 * @brief 49. 字母异位词分组
 * @link https://leetcode.cn/problems/group-anagrams/
 * 
 * @algorithm Hash Map + 排序 (Sorting)
 * 
 * @time_complexity O(N * K * logK) 
 *      - N 是字符串数组的长度
 *      - K 是字符串的最大长度
 *      - 每次对字符串排序需要 O(K * logK) 的时间，总共遍历 N 次
 * 
 * @space_complexity O(N * K)
 *      - 需要一个哈希表存储所有的字符串，最坏情况下所有字符串各不相同
 * 
 * @note 核心思路：
 * 1. 什么是字母异位词？比如 "eat" 和 "tea"，它们包含的字母完全一样，只是顺序不同。
 * 2. 如何把它们分到一组？我们需要一个“统一的标准”（Key）。
 * 3. 破局点：既然字母一样，只要把它们**内部排序**，结果肯定是一模一样的！
 *    "eat" -> 排序 -> "aet"
 *    "tea" -> 排序 -> "aet"
 * 4. 我们用排序后的字符串 "aet" 作为哈希表的 Key。
 * 5. 哈希表的 Value 存一个 vector<string>，用来收集所有原始字符串。
 * 
 * @optimize 进阶思路 (计数法 O(N*K))
 * 这种方法在字符串很长时更优。
 */

#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm> 

using namespace std;

class Solution {
public:
    vector<vector<string>> groupAnagrams(vector<string>& strs) {
        unordered_map<string, vector<string>> anagramMap;
        
        // 1. 遍历所有的原始字符串
        for (const string& str : strs) { //常量引用，避免拷贝且防止修改原数据
      
            string key = str;
            
            // 2. 将字符串内部按字母序排序，得到通用标识符 (Key)
            // 时间复杂度: O(K logK)
            sort(key.begin(), key.end());
            
            // 3. 将原始字符串放入对应的“桶”里
            // 如果 key 不存在，它会自动创建一个空的 vector，然后再 push_back
            anagramMap[key].push_back(str);
        }
        
        // 4. 将哈希表中的所有 Value 提取出来，组成最终的结果
        vector<vector<string>> result;
        // 提前分配内存，避免 vector 多次扩容
        result.reserve(anagramMap.size()); 
        
        // auto& pair 会自动推导为 std::pair<const string, vector<string>>&
        for (auto& pair : anagramMap) {
            // 使用 std::move 可以避免拷贝，直接转移所有权，极大提升性能
            result.push_back(move(pair.second)); 
        }
        
        return result;
    }
};
