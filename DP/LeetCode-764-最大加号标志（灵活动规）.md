#### [764. 最大加号标志](https://leetcode.cn/problems/largest-plus-sign/)

在一个 `n x n` 的矩阵 `grid` 中，除了在数组 `mines` 中给出的元素为 `0`，其他每个元素都为 `1`。`mines[i] = [xi, yi]`表示 `grid[xi][yi] == 0`

返回 `grid` *中包含 `1` 的最大的 **轴对齐** 加号标志的阶数* 。如果未找到加号标志，则返回 `0` 。

一个 `k` 阶由 *`1`* 组成的 **“轴对称”加号标志** 具有中心网格 `grid[r][c] == 1` ，以及4个从中心向上、向下、向左、向右延伸，长度为 `k-1`，由 `1` 组成的臂。注意，只有加号标志的所有网格要求为 `1` ，别的网格可能为 `0` 也可能为 `1` 。

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/06/13/plus1-grid.jpg)

```
输入: n = 5, mines = [[4, 2]]
输出: 2
解释: 在上面的网格中，最大加号标志的阶只能是2。一个标志已在图中标出。
```

##### 思路：发现相邻块的性质与构造十字有关系 -> 考虑动态规划

基本递推：记子状态$dp[i][j][k]$为$grid$中第$i$行第$j$列某方向上的连续1的个数，其中$k$标识了方向，假定
$$
k=0,1,2,3 =左、右、上、下
$$
那么
$$
dp[i][j][0] = \begin{cases}
0 ,grid[i][j]=0 \\
dp[i][j-1][0] + 1,otherwise\\
\end{cases}
$$
其余情况可以类推得到。

最终的结果是综合每个$(i,j)$位置的$dp$的最小值的最大值。

其他思路：改变枚举顺序

选定一个$(i,j)$之后，可以用四个方向去逼近

##### Code

```C++
class Solution {
public:
    int orderOfLargestPlusSign(int n, vector<vector<int>>& mines) {
        vector<vector<int>> dp(n, vector<int>(n, n));
        for (auto& e : mines) dp[e[0]][e[1]] = 0;
        for (int i = 0; i < n; ++i) {
            int left = 0, right = 0, up = 0, down = 0;
            for (int j = 0, k = n - 1; j < n; ++j, --k) {
                left = dp[i][j] ? left + 1 : 0;
                right = dp[i][k] ? right + 1 : 0;
                up = dp[j][i] ? up + 1 : 0;
                down = dp[k][i] ? down + 1 : 0;
                dp[i][j] = min(dp[i][j], left);
                dp[i][k] = min(dp[i][k], right);
                dp[j][i] = min(dp[j][i], up);
                dp[k][i] = min(dp[k][i], down);
            }
        }
        int ans = 0;
        for (auto& e : dp) ans = max(ans, *max_element(e.begin(), e.end()));
        return ans;
    }
};
```

