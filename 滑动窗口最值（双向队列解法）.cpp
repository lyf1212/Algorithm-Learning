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
			//�����������һ��Ԫ��С��nums�м������뵽�����е�Ԫ��ʱ���������е�Ԫ�ص��������϶��������ֵ.
			//�������˹ؼ��Ե�һ����ѡ�����ֵ.
			//Caution�������˫������е����±꣬Ҫת����nums����Ԫ�زſ���.������������̫���ˣ���ʹ����ط�д��Ҳ�ܹ�����...
			q.pop_back();
		q.push_back(r);//���е��д���±꣺�����ж���Ԫ���Ƿ��Ѿ����ڴ�������.(Line.22)
		int l = r - k + 1;//�������ڵ����±�.
		if (q.front() < l)
			q.pop_front();
		if (r >= k - 1)//һ���Ҳ��±����k-1����ô�Ϳ�ʼ�γɴ��ڣ�һֱ��nums���.��ƾ�˸���Max���飬ע���±���l.
			Max[l] = nums[q.front()];
		
	}
	q.clear();
	for (int r = 0; r < n; r++)
	{
		while (!q.empty() && nums[q.back()] > nums[r])
			//�����������һ��Ԫ�ش���nums�м������뵽�����е�Ԫ��ʱ���������е�Ԫ�ص��������϶�������Сֵ.
			//�������˹ؼ��Ե�һ����ѡ����Сֵ.
			q.pop_back();
		q.push_back(r);//���е��д���±꣺�����ж���Ԫ���Ƿ��Ѿ����ڴ�������.(Line.36)
		int l = r - k + 1;//�������ڵ����±�.
		if (q.front() < l)
			q.pop_front();
		if (r >= k - 1)//һ���Ҳ��±����k-1����ô�Ϳ�ʼ�γɴ��ڣ�һֱ��nums���.��ƾ�˸���Min���飬ע���±���l.
			Min[l] = nums[q.front()];

	}
	printf("%d", Min[0]);
	for (int i = 1; i < n - k + 1; i++)//���ս������Ԫ�ظ���Ϊn-k+1.
		printf(" %d", Min[i]);
	cout << endl;
	printf("%d", Max[0]);
	for (int i = 1; i < n - k + 1; i++)//���ս������Ԫ�ظ���Ϊn-k+1.
		printf(" %d", Max[i]);
	return 0;
}