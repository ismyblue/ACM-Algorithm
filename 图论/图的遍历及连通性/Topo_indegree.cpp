#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
const int MAX = 105;
vector<int> e[MAX];
int indegree[MAX];
int toponum[MAX];
int n,m,u,v;

void topo_sort()
{
    int u;
    queue<int> qu;
    for(int i = 1; i <= n; i++)
    {
        if (!indegree[i])//入度数为0加入队列
            qu.push(i);
    }
    int cnt = 0;
    while(!qu.empty())
    {
        u = qu.front();
        qu.pop();
        toponum[cnt++] = u;
        for(int i = 0;i < e[u].size();i++)
        {
            int v = e[u][i];//删除这条边，终点的入度减一
            indegree[v]--;
            if(indegree[v] == 0)
                qu.push(v);
        }
    }
    if(cnt != n)
        printf("这个有向图存在环，没有拓扑序\n");
    //如果这个图并不是全连通的，那么
    for(int i = 1;i <= n;i++)
        if(indegree[i]) printf("存在环\n");

    for(int i = 0;i < cnt;i++)
        printf("%d ",toponum[i]);

}

int main()
{
    while(~scanf("%d%d",&n,&m))//n个点，m条有向边
    {
        for(int i = 0; i <= n; i++)
        {
            e[i].clear();
            indegree[i] = 0;//第i个顶点的度数
            toponum[i] = 0;//topo数组存储排序后的顶点
        }
        for(int i = 1 ; i <= m; i++)
        {
            scanf("%d%d",&u,&v);
            e[u].push_back(v);
            indegree[v]++;//度数 入度数加一
        }
        topo_sort();
    }
}

/*
Topo_sort 针对有向图
5 7
3 1
2 1
2 4
2 5
3 5
4 3
4 5

2 4 3 1 5
*/
