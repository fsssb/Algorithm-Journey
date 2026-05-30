#include <array>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

struct Pair{
    int key;
    string val;

    Pair(int key,string val){
        this->key = key;
        this->val = val;
    }
};

//基于数组实现的哈希表
 
class ArrayHashMap{

private:
    vector<Pair*> buckets;

public:
    ArrayHashMap(){
        buckets = vector<Pair*> (100);
    }

    ~ArrayHashMap(){
        for(const auto& bucket : buckets){
            delete bucket;
        }
        buckets.clear();
    }
    
    //哈希函数
    int hashFunc(int key){
        int index = key % 100;
        return index;
    }

    //查询操作
    string get(int key){
        int index = hashFunc(key);
        Pair* pair = buckets[index];
        if(pair == nullptr) return ""; //哈希表中没有 key
        return pair->val;
    }
    //添加操作
    void put(int key,string val){
        Pair* pair = new Pair(key,val);
        int index = hashFunc(key);
        buckets[index] = pair; 
    }

    //删除操作
    void remove(int key){
        int index = hashFunc(key);
        delete buckets[index];
        buckets[index] = nullptr;        
    }

    //打印哈希表
    void print(){
        for(auto kv : buckets){
            cout << kv->key << "->" << kv->val << endl;
        }
    }
};
