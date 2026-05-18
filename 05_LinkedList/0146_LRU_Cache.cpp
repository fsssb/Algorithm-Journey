/**
 * @file 0146_LRU_Cache.cpp
 * @brief 146. LRU 缓存
 * @link https://leetcode.cn/problems/lru-cache/
 * 
 * @algorithm Hash Table + Doubly Linked List
 * @time_complexity O(1) - get 和 put 均为常数时间
 * @space_complexity O(Capacity) - 存储 capacity 个键值对
 * 
 * @note 核心优化：
 * 1. 使用 std::list 存储数据，保持访问顺序。
 * 2. 使用 unordered_map 存储 key 到 list iterator 的映射，实现 O(1) 定位。
 * 3. 利用 list::splice 实现 O(1) 的节点移动（移动到头部），无需删除再插入。
 */

#include <unordered_map>
#include <list>

using namespace std;

class LRUCache {
private:
    int cap;
    // 存储 {key, value} 的双向链表
    list<pair<int, int>> cache;
    // key -> list 中对应节点的迭代器
    unordered_map<int, list<pair<int, int>>::iterator> m;

public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        auto it = m.find(key);
        if (it == m.end()) return -1;

        // 利用 splice 将节点移动到链表头部 (MRU)
        // 参数：目标位置，源链表，待移动元素的迭代器
        cache.splice(cache.begin(), cache, it->second);
        
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = m.find(key);
        
        // 1. 如果 key 已存在：更新值并移到头部
        if (it != m.end()) {
            it->second->second = value;
            cache.splice(cache.begin(), cache, it->second);
            return;
        }

        // 2. 如果 key 不存在：
        // 2.1 如果容量满了，删除队尾最久未使用的元素 (LRU)
        if (cache.size() == cap) {
            int key_to_del = cache.back().first;
            m.erase(key_to_del);
            cache.pop_back();
        }

        // 2.2 插入新元素到头部，并记录其迭代器
        cache.push_front({key, value});
        m[key] = cache.begin();
    }
};


// #include <iostream>
//   #include <unordered_map>
//   using namespace std;

//   class LRUCache {
//   private:
//       struct Node {
//           int key;
//           int value;
//           Node* prev;
//           Node* next;

//           Node(int k, int v) {
//               key = k;
//               value = v;
//               prev = nullptr;
//               next = nullptr;
//           }
//       };

//       int capacity;
//       unordered_map<int, Node*> cache;

//       Node* head;
//       Node* tail;

//   public:
//       LRUCache(int cap) {
//           capacity = cap;

//           head = new Node(0, 0);
//           tail = new Node(0, 0);

//           head->next = tail;
//           tail->prev = head;
//       }

//       int get(int key) {
//           if (cache.find(key) == cache.end()) {
//               return -1;
//           }

//           Node* node = cache[key];
//           moveToHead(node);

//           return node->value;
//       }

//       void put(int key, int value) {
//           if (cache.find(key) != cache.end()) {
//               Node* node = cache[key];
//               node->value = value;
//               moveToHead(node);
//               return;
//           }

//           Node* node = new Node(key, value);
//           cache[key] = node;
//           addToHead(node);

//           if (cache.size() > capacity) {
//               Node* old = removeTail();
//               cache.erase(old->key);
//               delete old;
//           }
//       }

//   private:
//       void removeNode(Node* node) {
//           node->prev->next = node->next;
//           node->next->prev = node->prev;
//       }

//       void addToHead(Node* node) {
//           node->next = head->next;
//           node->prev = head;

//           head->next->prev = node;
//           head->next = node;
//       }

//       void moveToHead(Node* node) {
//           removeNode(node);
//           addToHead(node);
//       }

//       Node* removeTail() {
//           Node* node = tail->prev;
//           removeNode(node);
//           return node;
//       }
//   };

//   ———

//   # 8. 最核心的四个辅助函数

//   你真正要记的是这四个：

//   removeNode(node)
//   addToHead(node)
//   moveToHead(node)
//   removeTail()

//   ## 删除节点

//   void removeNode(Node* node) {
//       node->prev->next = node->next;
//       node->next->prev = node->prev;
//   }

//   意思是：

//   让 node 前面的节点直接指向 node 后面的节点
//   让 node 后面的节点直接指向 node 前面的节点

//   ———

//   ## 插入头部

//   void addToHead(Node* node) {
//       node->next = head->next;
//       node->prev = head;

//       head->next->prev = node;
//       head->next = node;
//   }

//   意思是把节点插到：

//   head 和 head->next 中间

//   ———

//   ## 移动到头部

//   void moveToHead(Node* node) {
//       removeNode(node);
//       addToHead(node);
//   }

//   ———

//   ## 删除尾部

//   Node* removeTail() {
//       Node* node = tail->prev;
//       removeNode(node);
//       return node;
//   }

//   注意：
//   真正的尾部节点是虚拟节点 tail，所以要删的是：

//   tail->prev

