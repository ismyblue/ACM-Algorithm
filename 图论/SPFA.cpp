#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
const int MAX = 1005;

struct edge{
	int v, w;
	edge(int v, int w) :v(v), w(w){}
};
vector<edge> e[MAX];

void addEdge(int u, int v, int w)
{
	e[u].push_back(edge(v, w));
}

int dis[MAX];
bool inque[MAX];
int Rank[MAX];
const int inf = 1 << 30;
bool spfa(int s, int n)
{
	int i, j;
	for (i = 0; i <= n; i++)
	{
		dis[i] = inf;
		inque[i] = false;
		Rank[i] = 0;
	}

	dis[s] = 0;
	Rank[s]++;
	inque[s] = true;
	queue<int> qu;
	qu.push(s);
	while (!qu.empty())
	{
		int u = qu.front();
		inque[u] = false;
		qu.pop();
		for (i = 0; i < (int)e[u].size(); i++)
		{
			int v = e[u][i].v;
			int w = e[u][i].w;
			if (dis[u] + w < dis[v])
			{
				dis[v] = dis[u] + w;
				if (!inque[v])
				{
					qu.push(v);
					inque[v] = true;
					Rank[v]++;
					if (Rank[v] >= n)
						return false;
				}
			}
		}
	}
	return true;
}

int main()
{
	int ca;
	int n, m, w;
	int a, b, c;
	scanf("%d", &ca);
	while (ca--)
	{
		scanf("%d%d%d", &n, &m, &w);
		for (int i = 0; i <= n + 1; i++)
			e[i].clear();
		for (int i = 0; i < m; i++)
		{
			scanf("%d%d%d", &a, &b, &c);
			addEdge(a, b, c);
			addEdge(b, a, c);
		}
		for (int i = 0; i < w; i++)
		{
			scanf("%d%d%d", &a, &b, &c);
			addEdge(a, b, -c);
		}
		for (int i = 1; i <= n; i++)
			addEdge(n + 1, i, 0);
		if (!spfa(n + 1, n + 1))
			printf("YES\n");
		else
			printf("NO\n");
	}

	return 0;
}

/*
2
3 3 1
1 2 2
1 3 4
2 3 1
3 1 3

3 2 1
1 2 3
2 3 4
3 1 8

NO
YES
*/
