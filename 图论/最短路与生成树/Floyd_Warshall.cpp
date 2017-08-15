#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstring>
using namespace std;
const int MAX = 1000;
const int inf = 1<<30;
long long e[MAX][MAX];//邻接矩阵
int n,m;

void Floyd_Warshall()
{
    int k,i,j;//通过从i点到j点，通过k点松弛
    for(k = 1;k <= n;k++)
        for(i = 1;i <= n;i++)
            for(j = 1;j <= n;j++)
                e[i][j] = min(e[i][j] , e[i][k] + e[k][j]);//inf + inf 爆int变成负数，会造成不可控制的错误，所以用long long

}

int main()
{
    long long a,b,c;
    int i,j;
    while(~scanf("%d%d",&n,&m))
    {
        for(i = 0;i <= n;i++)
            for(j = 0;j <= n;j++)
                e[i][j] = i==j?0:inf;
        for(i = 1;i <= m;i++)
        {
            scanf("%lld%lld%lld",&a,&b,&c);
            e[a][b] = min(e[a][b],c);
            e[b][a] = min(e[b][a],c);
        }
        Floyd_Warshall();
        for(i = 1;i <= n;i++)
        {
            for(j = 1;j <= n;j++)
                printf("%d ",e[i][j]);
            printf("\n");
        }

    }
    return 0;
}

/*
Floyd
5 7
2 4 3
1 2 2
1 4 7
1 3 6
3 5 1
2 5 6
4 5 5

0 2 6 5 7
2 0 7 3 6
6 7 0 6 1
5 3 6 0 5
7 6 1 5 0
*/
