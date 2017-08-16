#include <iostream>
#include <cstring>
#include <queue>
#include <cstdio>
using namespace std;
#define MAX 2000
const int inf = 100000;
int n;
int e[MAX][MAX];

//经典写法
void Prim1(int v)
{
    int i,j,k;
    int lowcost[MAX];
    int min;
    int closest[MAX];
    for(i = 0;i < n;i++)
    {
        lowcost[i] = e[v][i];//存储起点到各个顶点的长度
        closest[i] = v;//各个顶点到生成树中的对应顶点
    }
    for(i = 1;i < n;i++)
    {
        min = inf;
        for(j = 0;j < n;j++)
        {
            if(lowcost[j] != 0 && lowcost[j] < min)
            {
                min = lowcost[j];
                k = j;
            }
        }
        printf("add edge (%d,%d) ,wight is %d\n",closest[k],k,min);
        lowcost[k] = 0;
        for(j = 0;j < n;j++)
        {
            if(e[k][j] != 0 && e[k][j] < lowcost[j])
            {
                lowcost[j] = e[k][j];
                closest[j] = k;
            }
        }
    }
}

//用优先队列做
struct edge
{
    int u,v,w;
    edge(int u,int v,int w):u(u),v(v),w(w){}
    friend bool operator < (const edge &a,const edge &b)
    {
        return a.w > b.w;
    }
};
bool vis[MAX];
void Prim2(int s)
{
    memset(vis,false,sizeof(vis));
    vis[s] = true;
    priority_queue<edge> qu;
    for(int i = 0;i < n;i++)
        qu.push(edge(s,i,e[s][i]));
    int oldu = s;
    while(!qu.empty())
    {
        while(vis[qu.top().v])
            qu.pop();
        edge t = qu.top();
        qu.pop();
        vis[t.v] = true;
        printf("add edge (%d,%d) ,wight is %d\n",t.u,t.v,t.w);
        for(int i = 0;i < n;i++)
        {
            if(!vis[i] && e[t.v][i] != inf)
                qu.push(edge(t.v,i,e[t.v][i]));
        }
    }
}

int main()
{
    int m;
    while(~scanf("%d%d",&n,&m))
    {
        for(int i = 0;i < n;i++)
        {
            for(int j = 0;j < n;j++)
                e[i][j] = i==j?0:inf;
        }
        for(int i = 0;i < m;i++)
        {
            int u,v,w;
            scanf("%d%d%d",&u,&v,&w);
            e[u][v] = w;
            e[v][u] = w;
        }
        printf("prim1:\n");
        Prim1(0);
        printf("\nprim2:\n");
        Prim2(0);
    }

    return 0;
}

/*
Prim:
6 10
0 2 1
2 3 5
2 5 4
2 4 6
2 1 5
1 0 6
0 3 5
3 5 2
5 4 6
4 1 3

add edge (0,2) ,wight is 1
add edge (2,5) ,wight is 4
add edge (5,3) ,wight is 2
add edge (2,1) ,wight is 5
add edge (1,4) ,wight is 3
*/
