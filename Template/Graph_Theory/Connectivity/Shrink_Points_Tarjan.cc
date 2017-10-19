#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <stack>
#include <queue>
#define N 100003
#define M 100007
#define MIN 0x80000001
using namespace std;
struct edge_t
{
    int dat;
    edge_t *nxt;
} p[N + M], np[N + M];
int n, m, top, s[N];          //读入相关变量
int deep, low[N], dfn[N], nd; //Tarjan相关变量
int belong[N], ntop, ns[N];   //缩点重建图相关变量
int ind[N], dis[N], ans;      //SPFA相关变量
bool vis[N];                  //Tarjan和SPFA都需要用到的访问数组
stack<int> S;                 //Tarjan需要用到的栈，千万注意不要开成队列！
queue<int> Q;                 //SPFA需要用到的队列
inline void add_edge(int x, int y, bool z = false)
{
    if (z) //给缩点后的图加边
        np[++ntop].dat = y, np[ntop].nxt = np[x].nxt, np[x].nxt = &np[ntop];
    else //给缩点前的图加边
        p[++top].dat = y, p[top].nxt = p[x].nxt, p[x].nxt = &p[top];
}
void Tarjan(int x)
{
    low[x] = dfn[x] = ++deep;
    vis[x] = true, S.push(x);
    for (edge_t *k = p[x].nxt; k != NULL; k = k->nxt)
    {
        if (!dfn[k->dat])
        {
            Tarjan(k->dat);
            low[x] = min(low[x], low[k->dat]);
        }
        if (vis[k->dat])
            low[x] = min(low[x], dfn[k->dat]);
    }
    //缩点
    if (low[x] == dfn[x])
    {
        nd++; //强连通分量加一
        int v = S.top();
        while (v != x)
        { //只能pop到x而不能pop完整个栈，因为x之前的点不属于这个强连通分量
            S.pop();
            ns[nd] += s[v]; //整合强连通分量内的点权值
            vis[v] = false;
            belong[v] = nd; //记录该点属于哪个强连通分量
            v = S.top();
        }
        S.pop();
        ns[nd] += s[v]; //整合强连通分量内的点权值
        vis[v] = false;
        belong[v] = nd; //记录该点属于哪个强连通分量
    }
}
inline void SPFA(int c)
{
    /*
    由于刚才缩点时清空了vis数组，所以这里不用再次清空
    由于是求最长路，且没有负权点，所以起始点的dis值直接赋为对应点权值即可
    */
    Q.push(c);
    vis[c] = true;
    ans = max(ans, dis[c] = ns[c]);
    //有可能该强连通分量并无出边，这样会漏记ans，所以记得在SPFA前更新一下ans
    while (!Q.empty())
    {
        int x = Q.front();
        Q.pop();
        vis[x] = false;
        for (edge_t *k = np[x].nxt; k != NULL; k = k->nxt)
            if (dis[k->dat] < dis[x] + ns[k->dat])
            {
                dis[k->dat] = dis[x] + ns[k->dat];
                ans = max(ans, dis[k->dat]);
                if (!vis[k->dat])
                {
                    vis[k->dat] = true;
                    Q.push(k->dat);
                }
            }
    }
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    top = n; //别丢了这句话！
    for (int i = 1, x; i <= n; i++)
        scanf("%d", &s[i]);
    for (int i = 1, x, y; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        add_edge(x, y);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            Tarjan(i);
    //根据强连通分量重新建图
    ntop = nd; //注意别丢了这句话
    for (int i = 1; i <= n; i++)
        for (edge_t *k = p[i].nxt; k != NULL; k = k->nxt)
            //这里不能用low值建图，因为low值未必是连续的，可能会超出ntop范围
            if (belong[k->dat] != belong[i])
            {
                add_edge(belong[i], belong[k->dat], true);
                ind[belong[k->dat]]++;
            }
    //SPFA求最长路（最大权值和）
    for (int i = 1; i <= nd; i++)
        if (ind[i] == 0)
            SPFA(i);
    printf("%d\n", ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}