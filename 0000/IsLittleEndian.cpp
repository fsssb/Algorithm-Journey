/*
 * @brief 判断系统是否为小端序
 * @return true 表示是小端序，false 表示是大端序
 */

//方法一：使用联合体（Union）判断
bool isLittleEndian()
{
    union
    {
        int i;
        char c;
    } u;
    u.i = 1;  // 0x00000001
    // 小端内存：[01][00][00][00] → c 读到 01
    // 大端内存：[00][00][00][01] → c 读到 00
    return u.c == 1;
}

//方法二：使用指针判断
bool isLittleEndian()
{
    int i = 1;
    return *(char*)&i == 1;  // 取 i 的最低地址字节
}
