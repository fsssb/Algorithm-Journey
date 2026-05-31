/**
 * @file 0208_Implement_Trie_Prefix_Tree.cpp
 * @brief 208. 实现 Trie (前缀树)
 * @link https://leetcode.cn/problems/implement-trie-prefix-tree/
 *
 * @algorithm 前缀树 (Trie / Prefix Tree)
 * @time_complexity 
 *   - insert: O(L) - L 为单词长度，每一步仅需常数时间寻址。
 *   - search: O(L) - 顺着前缀树向下搜索，最坏只需走 L 步。
 *   - startsWith: O(L) - 只需顺利走完前缀的所有字符路径。
 * @space_complexity O(N * L) - 最坏情况下为所有插入字符的总数。
 *
 * @note 核心思路：
 * 1. 节点设计：TrieNode 内部不存储字符本身，而是通过 children[26] 的下标映射（ch - 'a'）隐式表达。
 * 2. 内存安全：C++ 原始指针数组不会默认清空，因此构造函数中使用 std::fill 强制将所有子节点初始化为 nullptr，规避野指针风险。
 * 3. 内存回收：实现后序递归清理函数 clear(TrieNode*)，在析构函数中自动回收堆区所有分配的节点内存，防止内存泄漏。
 * 4. 三大核心：
 *    - insert: 沿路径建房，遇空则 new，最后标记 isEnd = true。
 *    - search: 沿路径探路，遇空则返回 false，最后返回 curr->isEnd。
 *    - startsWith: 沿路径探路，遇空则返回 false，若路径畅通则直接返回 true。
 */

#include <bits/stdc++.h>
using namespace std;

class Trie {
private:

        // 前缀树节点结构体
    struct TrieNode {
        bool isEnd;
        TrieNode* children[26];

        // 构造函数：清空内存，赋初值
        TrieNode() {
            isEnd = false;
            // 强制初始化所有指针为 nullptr
            std::fill(begin(children), end(children), nullptr);  //std::fill(children, children + 26, nullptr);  
        }
    };

    TrieNode* root;

    // 递归后序遍历，彻底释放堆区节点，防止内存泄漏
    void clear(TrieNode* node) {
        if (node == nullptr) {
            return;
        }
        for (int i = 0; i < 26; ++i) {
            clear(node->children[i]); // 递归释放子树
        }
        delete node; // 释放自己
    }

public:
    // 初始化前缀树对象
    Trie() {
        root = new TrieNode();
    }

    // 析构函数：生命周期结束时自动触发，保障内存安全
    ~Trie() {
        clear(root);
    }

    // 向前缀树中插入一个单词
    void insert(const string& word) {
        TrieNode* curr = root;
        for (char ch : word) {
            int index = ch - 'a';
            // 若路不通，则建新房
            if (curr->children[index] == nullptr) {
                curr->children[index] = new TrieNode();
            }
            // 顺着节点往下走
            curr = curr->children[index];
        }
        // 标记最后一个字符为单词结尾
        curr->isEnd = true;
    }

    // 检索一个单词是否存在于前缀树中
    bool search(const string& word) {
        TrieNode* curr = root;
        for (char ch : word) {
            int index = ch - 'a';
            // 若中途没路，说明单词不存在
            if (curr->children[index] == nullptr) {
                return false;
            }
            curr = curr->children[index];
        }
        // 路径走通后，必须确认其是否为完整单词的结尾
        return curr->isEnd;
    }

    // 检索是否存在任何单词以给定前缀开头
    bool startsWith(const string& prefix) {
        TrieNode* curr = root;
        for (char ch : prefix) {
            int index = ch - 'a';
            // 若前缀匹配过程中断，直接返回 false
            if (curr->children[index] == nullptr) {
                return false;
            }
            curr = curr->children[index];
        }
        // 只要顺利走完前缀的所有节点，即证明前缀存在
        return true;
    }
};




