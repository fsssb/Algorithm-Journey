#include <iostream>
#include <vector>
using namespace std;

class Solution{

public:
    bool canPartion(vector<int>& nums){
        //calculate the sum of coins!
        int sum = 0;
        for(int num : nums)
        {
            sum += num;
        }

        //奇偶判断：如果是奇数自然无法平分
        if(sum % 2 != 0){
            return false;
        }

        int n = nums.size();
        int target = sum / 2; //平分得到的数额
        
        // 创建二维 DP 矩阵，大小为 (n + 1) 行，(target + 1) 列，默认初始化为 false
        // 多出来的 "+1" 完美承载了 "0个金币" 和 "0元目标和" 的初始状态，避开了下标错位
        vector<vector<bool>> dp(n + 1,vector<bool>(target + 1,false));

        //初始化第一列：任意的 前 i 个金币都能够实现 0 的和，也就是什么都不选！
        for(int i = 0; i <= n; ++i){
            dp[i][0] = true;
        }

        //状态转移
        //外层循环：顺次遍历每一个金币i（从 1 到 n）
        for(int i = 1; i <= n; ++i){
            int x = nums[i - 1]; // 下标的转换
            
            //内层循环：遍历每个可能的目标和 j (从 1 到 target)；
            for(int j = 1; j <= target; ++j){
                if(j >= x){
                    // 如果当前目标和 j 大于等于当前金币面值 x，我们可以选择：
                    // 1. 不选当前金币：dp[i-1][j]
                    // 2. 选择当前金币：dp[i-1][j-x]
                    dp[i][j] = dp[i - 1][j] || dp[i - 1][j - x];
                }else{
                    // 如果当前目标和 j 小于金币面值 x，放不下，我们只能选择不选
                    dp[i][j] = dp[i - 1][j];
                }
            }
        }
        return dp[n][target];
    }
};
