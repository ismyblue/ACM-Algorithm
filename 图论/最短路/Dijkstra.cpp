#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
const int MAX = 10000;
int n,m,s,en;
int dis[MAX];
int vis[MAX];
const int inf = 1<<30;

struct edge{
    int v,w;
    edge(int v,int w):v(v),w(w){}
};

struct node{
    int u,dis;
    node(int u,int dis):u(u),dis(dis){}
    friend bool operator<(const node &a,const node &b)
    {
        return a.dis>b.dis;
    }
};

vector<edge> e[MAX];
void add(int u,int v,int w)
{
    e[u].push_back(edge(v,w));
}

void dijsktra(int s,int en)
{
    cout<<s<<" "<<en<<endl;
    int i,j;
    for(i = 0;i <= n;i++)
    {
        dis[i] = inf;
        vis[i] = false;
    }
    dis[s] = 0;
    vis[s] = true;
    priority_queue<node> qu;
    qu.push(node(s,dis[s]));
    while(!qu.empty())
    {
        int u = qu.top().u;
        //cout<<qu.top().u<<" "<<qu.top().dis<<endl;
        vis[u] = true;
        qu.pop();
        for(j = 0;j < e[u].size();j++)
        {
            int v = e[u][j].v;
            int w = e[u][j].w;
            if(dis[u] + w < dis[v] && vis[v]==false)
            {
                dis[v] = dis[u] + w;
                qu.push(node(v,dis[v]));
            }
        }
    }
    if(dis[en] != inf)
        printf("%d\n",dis[en]);
    else
        printf("-1\n");
}
int main()
{
    int a,b,c;
    freopen("in.txt","r",stdin);
    while(~scanf("%d%d%d%d",&n,&m,&s,&en))
    {
        for(int i = 0;i < m;i++)
        {
            scanf("%d%d%d",&a,&b,&c);
            add(a,b,c);
            add(b,a,c);
        }
        dijsktra(s,en);
    }
    return 0;
}
/*Dijkstra
10 10 1 4
3 7 7
7 2 1
2 1 5
2 8 9
8 10 5
6 8 3
4 6 5
4 5 8
7 8 8
5 8 2

*/