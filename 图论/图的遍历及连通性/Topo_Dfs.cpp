#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
const int MAX = 105;
vector<int> e[MAX];
int toponum[MAX];
bool istopo[MAX];
int cnt;
int n,m;

void topo_dfs(int u)
{
    istopo[u] = true;
    for(int i = 0;i < e[u].size();i++)
    {
        int v = e[u][i];
        if(istopo[v] == false)
            topo_dfs(v);
    }
    toponum[cnt++] = u;//倒序存储的拓扑序
}

int main()
{
    int u,v;
    while(~scanf("%d%d",&n,&m))//n个点，m条有向边
    {
        for(int i = 0; i <= n; i++)
            {
                e[i].clear();
                istopo[i] = false;
                toponum[i] = -1;
            }

        for(int i = 1 ; i <= m; i++)
        {
            scanf("%d%d",&u,&v);
            e[u].push_back(v);
        }
        cnt = 0;
        for(int i = 1;i <= n;i++)
        {
            if(istopo[i] == false)//如果没有被排好序
                topo_dfs(i);
        }
        cout<<cnt<<endl;
        for(int i = cnt-1;i >= 0;i--)
            printf("%d ",toponum[i]);
    }
}

/*
拓扑排序有向无环图，dfs深搜，排好的序是倒序
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
