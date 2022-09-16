#include<iostream>
#include<stdio.h>
#include<cstring>
#include<queue>
#include<stack>
using namespace std;
int dir[8][2] = { {1,2},{-1,2},{1,-2},{-1,-2}, {2,1},{2,-1},{-2,-1},{-2,1} };
int path[12][12];//��¼ǰ��.
int vis[12][12];
int ans_path[12][12];
struct point
{
	int x, y;
	int step;
	point(int x_, int y_, int step_) :x(x_), y(y_), step(step_) {};
};
int main()
{
	int x0, y0, x1, y1;
	cin >> x0 >> y0 >> x1 >> y1;
	int m; cin >> m;
	int obstacle[12][12];
	memset(obstacle, 0, sizeof(obstacle));
	while (m--)
	{
		int t1, t2;
		cin >> t1 >> t2;
		obstacle[t1][t2] = 1;
	}
	point start = point(x0, y0, 0);
	queue<point> frontier;
	frontier.push(start);
	vis[x0][y0] = 1;
	int ans = 999999;
	int min_cnt = 0;
	while (!frontier.empty())
	{
		point node = frontier.front();
		frontier.pop();//û�б�Ҫ���ñսڵ㼯.
		if (node.step > ans)
			continue;
		
		for (int k = 0; k < 8; k++)
		{
			int new_x = node.x+ dir[k][0];
			int new_y = node.y + dir[k][1];
			int ob_x = node.x + dir[k][0] / 2;
			int ob_y = node.y + dir[k][1] / 2;//��������ŵĵ㣺ϸ��.
			if (!(new_x >= 0 && new_y >= 0 && new_x <= 10 && new_y <= 10))//�ж��Ƿ����.
				continue;
			if (obstacle[ob_x][ob_y] == 1 || vis[new_x][new_y] == 1 || obstacle[new_x][new_y] == 1)//�ж��Ƿ�����Ų���û��������Ҫȥ��Ŀ�ĵ�û�����ӵ�·���������ֱ����������Ϊ����һ���޺�Ч�ԵĶ�������.
				continue;
			vis[new_x][new_y] = 1;
			path[new_x][new_y] = k;//ֻ��¼ǰ������.
			if (new_x == x1 && new_y == y1)
			{
				if (ans > node.step)
				{
					ans = node.step;
					min_cnt = 1;
					memset(vis, 0, sizeof(vis));
					memcpy(ans_path, path, sizeof(path));
				}
				else
				{
					if (node.step == ans)	
						min_cnt++;
					memset(vis, 0, sizeof(vis));
					memset(path, 0, sizeof(path));
				}
			}
			else
			{
				point subnode = point(new_x, new_y, node.step + 1);
				frontier.push(subnode);
			}
	
		}
	}
	if (min_cnt == 1)
	{
		printf("(%d,%d)", x0, y0);
		int x_next = x1, y_next = y1;
		stack<pair<int,int>> ans_xy;
		for (int i = 0; i < ans; i++)
		{
			int x_pre = x_next - dir[ans_path[x_next][y_next]][0];
			int y_pre = y_next - dir[ans_path[x_next][y_next]][1];
			ans_xy.push({ x_pre,y_pre });

		}
		while (!ans_xy.empty())
		{
			int tx = ans_xy.top().first;
			int ty = ans_xy.top().second;
			ans_xy.pop();
			printf("-(%d,%d)", tx, ty);
		}
		printf("-(%d,%d)", x1, y1);
	}
	else
		cout << min_cnt << endl;
	return 0;
	

}