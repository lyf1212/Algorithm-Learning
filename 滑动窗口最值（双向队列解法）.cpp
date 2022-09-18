#include<iostream>
#include<stdio.h>
#include<deque>
using namespace std;
int nums[1000002];
int Max[1000002];
int Min[1000002];
int main()
{
	int n, k; cin >> n >> k;
	for (int i = 0; i < n; i++)
		cin >> nums[i];
	deque<int> q;
	for (int r = 0; r < n; r++)
	{
		while (!q.empty() && nums[q.back()] < nums[r])
			//当队列中最后一个元素小于nums中即将插入到队列中的元素时，将队列中的元素弹出：它肯定不是最大值.
			//这就完成了关键性的一步：选择最大值.
			//Caution：存放在双向队列中的是下标，要转换成nums数组元素才可以.本题样例给得太好了，即使这个地方写错也能过样例...
			q.pop_back();
		q.push_back(r);//队列当中存放下标：便于判定该元素是否已经不在窗口内了.(Line.22)
		int l = r - k + 1;//完整窗口的左下标.
		if (q.front() < l)
			q.pop_front();
		if (r >= k - 1)//一旦右侧下标大于k-1，那么就开始形成窗口，一直到nums最后.可凭此更新Max数组，注意下标是l.
			Max[l] = nums[q.front()];
		
	}
	q.clear();
	for (int r = 0; r < n; r++)
	{
		while (!q.empty() && nums[q.back()] > nums[r])
			//当队列中最后一个元素大于nums中即将插入到队列中的元素时，将队列中的元素弹出：它肯定不是最小值.
			//这就完成了关键性的一步：选择最小值.
			q.pop_back();
		q.push_back(r);//队列当中存放下标：便于判定该元素是否已经不在窗口内了.(Line.36)
		int l = r - k + 1;//完整窗口的左下标.
		if (q.front() < l)
			q.pop_front();
		if (r >= k - 1)//一旦右侧下标大于k-1，那么就开始形成窗口，一直到nums最后.可凭此更新Min数组，注意下标是l.
			Min[l] = nums[q.front()];

	}
	printf("%d", Min[0]);
	for (int i = 1; i < n - k + 1; i++)//最终结果数组元素个数为n-k+1.
		printf(" %d", Min[i]);
	cout << endl;
	printf("%d", Max[0]);
	for (int i = 1; i < n - k + 1; i++)//最终结果数组元素个数为n-k+1.
		printf(" %d", Max[i]);
	return 0;
}