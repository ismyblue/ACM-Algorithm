#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
const int MAX = 10000;
int pre[MAX];
int n,m;

int findr(int x)
{
    int r = x;
    while(r != pre[r])
        r = pre[r];
    int j = x,t;
    while(r != pre[j])
    {
        t = pre[j];
        pre[j] = r;
        j = t;
    }
    return r;
}

void join(int x,int y)
{
    int fx = findr(x);
    int fy = findr(y);
    if(fx == fy)
        return ;
    pre[fx] = fy;
    return ;
}

struct edge{
    int u,v,w;
    friend bool operator < (const edge &a,const edge &b)
    {
        return  a.w<b.w;
    }
}e[MAX];

int main()
{
    int n,m;
    int u,v,w;
    while(~scanf("%d%d",&n,&m))
    {
        for(int i = 0;i <= n;i++)
        {
            pre[i] = i;
        }
        for(int i = 0;i < m;i++)
        {
            scanf("%d%d%d",&u,&v,&w);
            e[i].u = u;
            e[i].v = v;
            e[i].w = w;
        }
        sort(e,e+m);
        for(int i = 0;i < m;i++)
        {
            if(findr(e[i].u) != findr(e[i].v))
            {
                printf("add edge (%d,%d) ,wight is %d\n",e[i].u,e[i].v,e[i].w);
                join(e[i].u,e[i].v);
            }
        }

    }
    return 0;
}

/*
并查集 + Kruskal
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
add edge (3,5) ,wight is 2
add edge (4,1) ,wight is 3
add edge (2,5) ,wight is 4
add edge (2,1) ,wight is 5
*/
