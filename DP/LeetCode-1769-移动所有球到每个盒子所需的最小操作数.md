#### [1769. 移动所有球到每个盒子所需的最小操作数](https://leetcode.cn/problems/minimum-number-of-operations-to-move-all-balls-to-each-box/)

有 `n` 个盒子。给你一个长度为 `n` 的二进制字符串 `boxes` ，其中 `boxes[i]` 的值为 `'0'` 表示第 `i` 个盒子是 **空** 的，而 `boxes[i]` 的值为 `'1'` 表示盒子里有 **一个** 小球。

在一步操作中，你可以将 **一个** 小球从某个盒子移动到一个与之相邻的盒子中。第 `i` 个盒子和第 `j` 个盒子相邻需满足 `abs(i - j) == 1` 。注意，操作执行后，某些盒子中可能会存在不止一个小球。

返回一个长度为 `n` 的数组 `answer` ，其中 `answer[i]` 是将所有小球移动到第 `i` 个盒子所需的 **最小** 操作数。

每个 `answer[i]` 都需要根据盒子的 **初始状态** 进行计算。

**示例 1：**

```
输入：boxes = "110"
输出：[1,1,3]
解释：每个盒子对应的最小操作数如下：
1) 第 1 个盒子：将一个小球从第 2 个盒子移动到第 1 个盒子，需要 1 步操作。
2) 第 2 个盒子：将一个小球从第 1 个盒子移动到第 2 个盒子，需要 1 步操作。
3) 第 3 个盒子：将一个小球从第 1 个盒子移动到第 3 个盒子，需要 2 步操作。将一个小球从第 2 个盒子移动到第 3 个盒子，需要 1 步操作。共计 3 步操作。
```

##### 思路：状态转移

可以设$operation[i]$为将小球都移动到下标$i$处时花费的操作数。下标小于等于$i$的1的个数有$left[i]$个，下标大于$i$的个数有$right[i]$个。

那么有$operation[i+1]=operation[i]+left[i]-right[i].$

因为左边的1需要多走一步，右边的1可以少走一步。

由于$left$和$right$的定义，需要根据$boxes[i+1]$进行更新。

由状态转移方程也可以知道可以进行一维压缩。

##### Code：

```C++
class Solution {
public:
    vector<int> minOperations(string boxes) {
        /* operation[i+1] = operation[i] + left[i] - right[i] */
        int left = boxes[0]-'0';
        int n=boxes.length();
        int right=0, operation=0;
        for(int i=1;i<n;i++)
        {
            if(boxes[i]=='1')
            {
                right++;
                operation += i;
            }
        }
        vector<int> ans;
        ans.push_back(operation);
        for(int i=0;i<n-1;i++)
        {
            operation=operation + left - right;
            if(boxes[i+1]-'0')
            {
                left++;
                right--;
            }
            ans.push_back(operation);
        }
        return ans;
    }
};
```

##### 注：

本题若采用记录子状态的方法，则$O(n)$的时间复杂度。如果暴力模拟而没有利用子状态之间的信息重叠，则$O(n^{2})$的时间复杂度。