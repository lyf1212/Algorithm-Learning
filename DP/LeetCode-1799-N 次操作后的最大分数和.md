#### [1799. N 次操作后的最大分数和](https://leetcode.cn/problems/maximize-score-after-n-operations/)

给你 `nums` ，它是一个大小为 `2 * n` 的正整数数组。你必须对这个数组执行 `n` 次操作。

在第 `i` 次操作时（操作编号从 **1** 开始），你需要：

- 选择两个元素 `x` 和 `y` 。
- 获得分数 `i * gcd(x, y)` 。
- 将 `x` 和 `y` 从 `nums` 中删除。

请你返回 `n` 次操作后你能获得的分数和最大为多少。

函数 `gcd(x, y)` 是 `x` 和 `y` 的最大公约数。

**示例 1：**

```
输入：nums = [1,2]
输出：1
解释：最优操作是：
(1 * gcd(1, 2)) = 1
```

**示例 2：**

```
输入：nums = [3,4,6,8]
输出：11
解释：最优操作是：
(1 * gcd(3, 6)) + (2 * gcd(4, 8)) = 3 + 8 = 11
```

##### 思路：动态规划+状态压缩

本题具有明显的子结构，即给定数组按照操作得到最大分数。状态转移关系也很明显，问题是如何表示数组中的数字是已经被删除的还是仍然存在可供挑选的。

一个技巧性的方法是“**状态压缩**”，即使用二进制的0和1分辨是否存在某个数字，可以用从右往左数的第$i$个二进制位表示$nums[i]$是否被取走做过操作。

动态规划的重要一步是选取合适的状态枚举顺序进行子结构的转移。详见下方代码注释：

```C++
class Solution {
public:
    int Gcd(int a, int b)
    {
        return b == 0 ? a : (Gcd(b, a % b));
    }
    int maxScore(vector<int>& nums) {
        int gcd[20][20];
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                gcd[i][j] = Gcd(nums[i], nums[j]);
            }
        }
        // 记忆化搜索.
        // dp[mask]表示删除状态为mask时继续操作能够获得的最大分数.
        // mask是以二进制记录的压缩状态，1代表数字尚未被删除，0表示已经被删除.
        int dp[1 << n];
        memset(dp, 0, sizeof(dp));
        int all = (1 << n) - 1;
        for (int status = 1; status <= all; status++)  // (Core Step)从小到大枚举状态，这也是逻辑顺序.
        {
            int cnt_one = __builtin_popcount(status);   // 使用内置函数快速计数内部1的个数.
            if (cnt_one%2)  // 如果没有偶数个数字剩余，就继续枚举状态
                continue;

            // 枚举操作需要的两个数字.
            for (int i = 0; i < n; i++)
            {
                if (status & (1 << i))
                {
                    for (int j = i + 1; j < n; j++)
                    {
                        if (status & (1 << j))
                        {
                            int status_modified = status & (~(1 << i)) & (~(1 << j));   //将二者删除.
                            int _i = (n - cnt_one)/2 + 1; // 这是第几次操作（注意编号从1开始）.
                            dp[status] = max(dp[status],
                                dp[status_modified] + (_i)*gcd[i][j]);
                        }
                    }
                }
            }

        }
        return dp[all];
    }
};
```

