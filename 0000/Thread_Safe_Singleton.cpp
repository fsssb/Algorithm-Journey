/**
 * @file 0000_Thread_Safe_Singleton.cpp
 * @brief 手写线程安全的懒汉式单例模式（梅耶斯单例）
 * @link 经典 C++ 面试设计题
 *
 * @algorithm Meyers' Singleton (梅耶斯单例)
 * @time_complexity O(1) - 仅在第一次调用时进行 lazy 构造，后续调用均为常数级直接返回。
 * @space_complexity O(1) - 在内存全局区中仅存储一个唯一的静态实例。
 *
 * @note 核心思路：
 * 1. 构造函数私有化：禁止外部通过 new 或直接声明创建新对象。
 * 2. 禁用拷贝与赋值：显式删除（= delete）拷贝构造和赋值运算符，防止实例被复制。
 * 3. 延迟初始化（懒汉式）：在 getInstance() 内部使用局部静态变量。
 * 4. 线程安全（C++11 魔法静态特性）：C++11 起，标准保证局部静态变量的初始化是线程安全的，编译器会自动生成底层的互斥和阻塞代码，避免了手动加锁的性能开销。
 */

#include <iostream>

class MySingleton {
public:
    // 外部获取唯一实例的公有静态接口，返回引用更安全，防止外部意外 delete 指针
    static MySingleton& getInstance() {
        // 局部静态变量：只在第一次调用此函数时被初始化，此后一直保存在内存中直到程序结束
        // C++11 起，底层自动保证此处初始化的线程安全（Magic Statics）
        static MySingleton instance; 
        return instance;
    }

    // 显式删除拷贝构造函数，防止外部拷贝
    MySingleton(const MySingleton&) = delete;

    // 显式删除赋值运算符，防止外部赋值
    MySingleton& operator=(const MySingleton&) = delete;

    // 建议同时显式删除移动构造和移动赋值（C++11 健壮性保障）
    MySingleton(MySingleton&&) = delete;
    MySingleton& operator=(MySingleton&&) = delete;

    // 单例类的业务方法示例
    void doSomething() {
        std::cout << "Thread-safe Singleton is doing something!" << std::endl;
    }

private:
    // 构造函数私有化：防止外部创建实例
    MySingleton() {
        std::cout << "Singleton Instance Created!" << std::endl;
    }

    // 析构函数私有化（可选，但推荐）：防止外部意外销毁实例
    ~MySingleton() {
        std::cout << "Singleton Instance Destroyed!" << std::endl;
    }
};

int main() {
    // 外部正确使用方式
    MySingleton& s1 = MySingleton::getInstance();
    s1.doSomething();

    MySingleton& s2 = MySingleton::getInstance();
    
    // 验证是否为同一个实例
    std::cout << "Address s1: " << &s1 << std::endl;
    std::cout << "Address s2: " << &s2 << std::endl;

    // 以下代码若取消注释，均会引起编译报错，证明了其完美的安全性：
    // MySingleton s3;                     // 报错：构造函数私有
    // MySingleton s4(s1);                 // 报错：拷贝构造已被删除
    // MySingleton s5 = std::move(s1);     // 报错：移动构造已被删除
    // delete &s1;                         // 报错：析构函数私有
    
    return 0;
}
