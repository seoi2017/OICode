#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#define N 10003
#define M 500007
using namespace std;
typedef long long ll_t;
const ll_t INF = 0x3F3F3F3F3F3F3F3F;
struct edge_t
{
    int dat;
    ll_t len;
    edge_t *nxt;
} p[N + (M << 1)];
int top, n, m, st;
ll_t dis[N];
bool vis[N];
inline void add_edge(int x, int y, ll_t l)
{ //有向图单向建边
    p[++top].dat = y, p[top].len = l, p[top].nxt = p[x].nxt, p[x].nxt = &p[top];
}
inline void SPFA(int c)
{
    memset(dis, 0x3F, sizeof(dis));
    dis[c] = 0LL;
    queue<int> Q;
    Q.push(c);
    vis[c] = true;
    while (!Q.empty())
    {
        int x = Q.front();
        Q.pop();
        vis[x] = false;
        for (edge_t *k = p[x].nxt; k != NULL; k = k->nxt)
        {
            if (dis[k->dat] > dis[x] + k->len)
            {
                dis[k->dat] = dis[x] + k->len;
                if (!vis[k->dat])
                {
                    Q.push(k->dat);
                    vis[k->dat] = true;
                }
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
    scanf("%d%d%d", &n, &m, &st);
    top = n;
    ll_t tl;
    for (int i = 1, tx, ty; i <= m; i++)
    {
        scanf("%d%d%lld", &tx, &ty, &tl);
        add_edge(tx, ty, tl);
    }
    SPFA(st);
    for (int i = 1; i <= n; i++)
        dis[i] == INF ? printf("2147483647 ") : printf("%lld ", dis[i]);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}