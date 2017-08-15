#include <iostream>
#include <cstring>
#include <cstdio>
using namespace std;
#define MAX 10000000
int nEdge;//代表的是输入边的总数
int head[MAX];//head[i]保存的是连接第i个点的最后一条边的序号。

struct node
{
    int v,w,pre;//pre保存的是上一条边的序号（输入时的序号）
} e[MAX];

void addEdge(int u,int v,int w)//把u->v权重为w的边加入到边集。
{
    nEdge++;//新增了一条u->v的边，此时这条边的序号是nEdge；
    e[nEdge].v = v;
    e[nEdge].w = w;
    e[nEdge].pre = head[u];//连接u点这条边的上一条边的序号是p[u];
    head[u] = nEdge;//连接u点又新增了一条边，这条边的序号是nEdge;
}

int main()
{
    int n,m;//n个点，m条边
    int a,b,c;
    while(~scanf("%d%d",&n,&m))
    {
        memset(head,0,sizeof(head));//初始化连接每个点的边的序号都是0，因为这个时候还没有边
        for(int i = 0; i < m; i++)
        {
            scanf("%d%d%d",&a,&b,&c);//a点到b点权重为c的边
            addEdge(a,b,c);//有向图，所以a->b,只是a到b，b不能到a;
            //addEdge(b,a,c);如果是无向图，就加上这一句，添加b->a的边
        }
        for(int i = 1; i <= n; i++) //输出边，一共有n个点，把从这个点出发的边分别输出出来。
        {
            printf("第%d个点：\n",i);
            for(int j = head[i]; j; j = e[j].pre) //遍历从i点出发的边的时候，是从最后一条边开始遍历，直到第一条边
            {
                printf("%d->%d,权重：%d\n",i,e[j].v,e[j].w);
            }
        }
    }
    return 0;
}
/*链式前向星
5 7
1 3 6
1 4 5
1 2 3
4 5 3
3 5 2
2 3 4
5 2 2
第1个点：
1->2,权重：3
1->4,权重：5
1->3,权重：6
第2个点：
2->3,权重：4
第3个点：
3->5,权重：2
第4个点：
4->5,权重：3
第5个点：
5->2,权重：2
*/
