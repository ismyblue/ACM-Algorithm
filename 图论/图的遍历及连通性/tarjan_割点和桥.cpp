#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAX_V = 1005;
const int MAX_E = 2020050;
const int inf = 100000000;

struct edge
{
    int v,w,next;
    bool cut;
}e[MAX_E];
int head[MAX_V];
int edgeCnt;

void addEdge(int u,int v,int w)
{
    e[edgeCnt].v = v;
    e[edgeCnt].w = w;
    e[edgeCnt].next = head[u];
    e[edgeCnt].cut = false;
    head[u] = edgeCnt++;
}

int dfn[MAX_E];
int low[MAX_E];
int top;
int dfsIndex;
int father[MAX_V];
void tarjan(int u,int uw)
{
    dfn[u] = low[u] = ++dfsIndex;
    int children = 0;
    for(int i = head[u];i != -1;i = e[i].next)
    {
        int v = e[i].v;
        int w = e[i].w;
        if(!dfn[v])
        {
            children++;
            father[v] = u;
            tarjan(v,w);
            low[u] = min(low[u],low[v]);
            if(low[v] > dfn[u])//是桥
                printf("桥：<%d,%d>\n",u,v);
            if(father[u] == -1 && children == 2)//防止多输出几次，这样根节点有多棵子树时只输出一次
                printf("割点：%d\n",u);
            if(father[u] != -1 && low[v] >= dfn[u])
                printf("割点：%d\n",u);/**/
        }
        else if(father[u] != v || (uw != w && father[u] == v))
        {
            low[u] = min(low[u],dfn[v]);
        }
    }
    return ;
}


int main()
{
    int n,m,u,v,w;
    while(~scanf("%d%d",&n,&m) && !(n == 0 && m == 0))
    {

        edgeCnt = 0;
        memset(head,-1,sizeof(head));
        for(int i = 0 ;i < m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            addEdge(u,v,w);
            addEdge(v,u,w);
        }
        memset(dfn,0,sizeof(dfn));
        memset(father,-1,sizeof(father));
        dfsIndex = 0;
        for(int i = 1;i <= n;i++)
        {
            if(!dfn[i])
                tarjan(i,e[head[u]].w);
        }
    }
    return 0;
}

/*
求割点和桥
割点：1.u是根节点，u有两个及以上子树，即为children>1
2.u不是根节点，但是low[v] >= dfn[u];

桥：low[v] > dfn[u]；

3 3
1 2 7
2 3 4
3 1 4

3 2
1 2 7
2 3 4

3 4
1 2 7
2 1 7
2 3 4
3 2 4

4 3
1 2 1
1 2 3
3 4 4

4 4
1 2 1
1 2 3
3 4 4
2 4 6

4 5
1 2 1
1 2 3
3 4 4
2 4 6
1 3 0

4 5
4 3 0
3 4 4
2 4 6
2 3 0
1 3 0

2 1
1 2 0

4 2
1 2 3
1 3 5

4 5
1 2 3
2 3 4
1 3 5
4 3 7
4 3 6

4 4
1 2 3
2 3 4
1 3 5
4 3 6

4 4
1 2 4
1 3 5
4 3 6
3 4 7

6 7
1 2 1
1 3 2
2 3 3
3 4 4
4 6 5
4 5 6
5 6 7

5 6
1 2 3
1 3 4
2 3 5
3 4 7
3 5 8
5 4 9

8 9
1 8 1
5 1 2
1 7 3
1 4 4
1 2 5
4 3 6
3 2 7
5 6 8
6 7 9

6 6
1 4 1
1 2 4
2 5 4
5 6 4
3 6 4
4 3 2

6 5
1 2 4
2 5 4
5 6 4
3 6 4
4 3 2

8 10
1 8 1
5 1 2
1 7 3
1 4 4
1 2 5
4 3 6
3 2 7
5 6 8
6 7 9
8 1 2

3 3
1 2 7
1 3 1
1 3 4

0 0
//-----------------------一条华丽的分割线------------------------//
3 3
1 2 7
2 3 4
3 1 4

3 2
1 2 7
2 3 4
桥：<2,3>
割点：2
桥：<1,2>

3 4
1 2 7
2 1 7
2 3 4
3 2 4
桥：<2,3>
割点：2
桥：<1,2>

4 3
1 2 1
1 2 3
3 4 4
桥：<3,4>

4 4
1 2 1
1 2 3
3 4 4
2 4 6
桥：<4,3>
割点：4
桥：<2,4>
割点：2

4 5
1 2 1
1 2 3
3 4 4
2 4 6
1 3 0

4 5
4 3 0
3 4 4
2 4 6
2 3 0
1 3 0
割点：3
桥：<1,3>

2 1
1 2 0
桥：<1,2>

4 2
1 2 3
1 3 5
桥：<1,3>
桥：<1,2>
割点：1

4 5
1 2 3
2 3 4
1 3 5
4 3 7
4 3 6
割点：3

4 4
1 2 3
2 3 4
1 3 5
4 3 6
桥：<3,4>
割点：3

4 4
1 2 4
1 3 5
4 3 6
3 4 7
割点：3
桥：<1,3>
桥：<1,2>
割点：1

6 7
1 2 1
1 3 2
2 3 3
3 4 4
4 6 5
4 5 6
5 6 7
割点：4
桥：<3,4>
割点：3

5 6
1 2 3
1 3 4
2 3 5
3 4 7
3 5 8
5 4 9
割点：3

8 9
1 8 1
5 1 2
1 7 3
1 4 4
1 2 5
4 3 6
3 2 7
5 6 8
6 7 9
割点：1
桥：<1,8>

6 6
1 4 1
1 2 4
2 5 4
5 6 4
3 6 4
4 3 2

6 5
1 2 4
2 5 4
5 6 4
3 6 4
4 3 2
桥：<3,4>
割点：3
桥：<6,3>
割点：6
桥：<5,6>
割点：5
桥：<2,5>
割点：2
桥：<1,2>

8 10
1 8 1
5 1 2
1 7 3
1 4 4
1 2 5
4 3 6
3 2 7
5 6 8
6 7 9
8 1 2
割点：1

3 3
1 2 7
1 3 1
1 3 4
桥：<1,2>
割点：1

0 0


*/

