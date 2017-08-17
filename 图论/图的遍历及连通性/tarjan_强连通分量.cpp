#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
using namespace std;
const int MAX_V = 10010;
const int MAX_E = 100010;

struct edge{
    int v,next;
}e[MAX_E];
int head[MAX_V];
int edgeCnt;
void addEdge(int u,int v)
{
    e[edgeCnt].v = v;
    e[edgeCnt].next = head[u];
    head[u] = edgeCnt;
    edgeCnt++;
}

int dfn[MAX_V];
int low[MAX_V];
int Stack[MAX_V];
bool inStack[MAX_V];
int top; //栈的指针
int dfsIndex;//深搜的序号
int Bcnt;//强连通分量的个数
int belong[MAX_V];
void tarjan(int u)
{
    dfn[u] = low[u] = ++dfsIndex;
    Stack[top++] = u;
    inStack[u] = true;
    for(int i = head[u];i != -1;i = e[i].next)//遍历u的出边
    {
        int v = e[i].v;
        if(!dfn[v])
        {
            tarjan(v);
            low[u] = min(low[u],low[v]);
        }
        else if(inStack[v])
            low[u] = min(low[u],dfn[v]);
    }
    if(dfn[u] == low[u])//u以及u的子树上的点组成一个强连通分量
    {
        Bcnt++;
        printf("强连通分量%d: ",Bcnt);
        int v;int num = 0;
        do{
            v = Stack[--top];
            inStack[v] = false;
            belong[v] = Bcnt;
            printf("%d ",v);
        }while(v != u);
        printf("\n");
    }
    return ;
}

int main()
{
    int n,m,i,j;
    int u,v;
    while(~scanf("%d%d",&n,&m))
    {
        memset(head,-1,sizeof(head));
        memset(dfn,0,sizeof(dfn));
        memset(inStack,false,sizeof(inStack));
        edgeCnt = 0;
        top = 0;
        for(i = 0;i < m;i++)
        {
            scanf("%d%d",&u,&v);
            addEdge(u,v);
        }
        dfsIndex = 0;
        Bcnt = 0;
        for(int i = 1;i <= n;i++)
        {
            if(!dfn[i])
                tarjan(i);
        }
    }
    return 0;
}

/*
tarjan 求强连通分量
6 8
1 3
3 5
5 6
1 2
4 1
3 4
2 4
4 6

强连通分量1: 6
强连通分量2: 5
强连通分量3: 3 4 2 1
*/
