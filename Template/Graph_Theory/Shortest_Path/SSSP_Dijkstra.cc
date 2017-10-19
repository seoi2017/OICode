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
struct node_t
{
    int dat;
    ll_t len;
    node_t(int x, ll_t y)
    {
        this->dat = x, this->len = y;
    }
    bool operator<(const node_t &x) const
    {
        return x.len < this->len;
    }
};
int top, n, m, st;
ll_t dis[N];
bool vis[N];
inline void add_edge(int x, int y, ll_t l)
{
    p[++top].dat = y, p[top].len = l, p[top].nxt = p[x].nxt, p[x].nxt = &p[top];
}
inline void dijkstra(int c)
{
    memset(dis, 0x3F, sizeof(dis));
    priority_queue<node_t> Q;
    Q.push(node_t(c, dis[c] = 0));
    while (!Q.empty())
    {
        node_t x = Q.top();
        Q.pop();
        if (x.len != dis[x.dat])
            continue;
        vis[x.dat] = true;
        for (edge_t *k = p[x.dat].nxt; k != NULL; k = k->nxt)
        {
            if (!vis[k->dat] && dis[k->dat] > dis[x.dat] + k->len)
            {
                dis[k->dat] = dis[x.dat] + k->len;
                Q.push(node_t(k->dat, dis[k->dat]));
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
    dijkstra(st);
    for (int i = 1; i <= n; i++)
        dis[i] == INF ? printf("2147483647 ") : printf("%lld ", dis[i]);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}