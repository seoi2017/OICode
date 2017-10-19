#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#define N 10003
#define M 100007
#define INF 0x3F3F3F3F
using namespace std;
struct edge_t
{
    int dat, f;
    edge_t *nxt;
} p[N + M], *cur[N]; //有向边，不需要乘二
int n, m, s, t, top, lv[N];
inline void add_edge(int x, int y, int z)
{
    p[++top].dat = y, p[top].f = z;
    p[top].nxt = p[x].nxt, p[x].nxt = &p[top];
}
inline bool dinic_bfs()
{
    queue<int> Q;
    memset(lv, 0, sizeof(lv));
    Q.push(s);
    lv[s] = 1;
    while (!Q.empty())
    {
        int x = Q.front();
        Q.pop();
        for (edge_t *k = p[x].nxt; k != NULL; k = k->nxt)
        {
            if (!lv[k->dat] && k->f)
            {
                lv[k->dat] = lv[x] + 1;
                Q.push(k->dat);
            }
        }
    }
    return lv[t] != 0;
}
int dinic_dfs(int x, int flow)
{
    if (x == t)
        return flow;
    int tmp = flow, res = 0;
    for (edge_t *&k = cur[x]; k != NULL && tmp; k = k->nxt)
    { //带当前弧优化的遍历出边
        if (lv[x] + 1 == lv[k->dat] && k->f)
        {
            res = dinic_dfs(k->dat, min(k->f, tmp));
            k->f -= res;
            tmp -= res;
        }
    }
    return flow - tmp;
}
inline int Dinic()
{
    int ans = 0, tmp = 0;
    while (dinic_bfs())
    {
        for (int i = 1; i <= n; i++)
            cur[i] = &p[i]; //重置当前弧
        while (tmp = dinic_dfs(s, INF))
            ans += tmp;
    }
    return ans;
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d%d%d", &n, &m, &s, &t);
    top = n;
    for (int i = 1, x, y, z; i <= m; i++)
    {
        scanf("%d%d%d", &x, &y, &z);
        add_edge(x, y, z);
    }
    printf("%d\n", Dinic());
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}