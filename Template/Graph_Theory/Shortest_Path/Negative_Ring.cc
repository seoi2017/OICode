#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 200007
#define M 200007
using namespace std;
typedef long long ll_t;
struct edge_t
{
    int dat;
    ll_t len;
    edge_t *nxt;
} p[N + (M << 1)];
int T, n, m, top;
ll_t dis[N];
bool vis[N], has;
inline void add_edge(int x, int y, ll_t z)
{
    p[++top].dat = y, p[top].len = z, p[top].nxt = p[x].nxt, p[x].nxt = &p[top];
    if (z >= 0LL) //题目要求，负权边仅单向
        p[++top].dat = x, p[top].len = z, p[top].nxt = p[y].nxt, p[y].nxt = &p[top];
}
void SPFA(int x)
{ //DFS实现的SPFA，速度更快，但是可能爆栈
    vis[x] = true;
    for (edge_t *k = p[x].nxt; k != NULL; k = k->nxt)
    {
        if (dis[k->dat] > dis[x] + k->len)
        {
            if (vis[k->dat] || has)
            {
                has = true;
                break;
            }
            dis[k->dat] = dis[x] + k->len;
            SPFA(k->dat);
        }
    }
    vis[x] = false;
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d%d", &n, &m);
        top = n, has = false;
        //由于判断的是负环，所以dis数组无需初始化为无限大，清零就好了
        memset(vis, false, sizeof(vis));
        for (int i = 1; i <= n; i++)
            p[i].nxt = NULL;
        for (int i = 1, x, y, z; i <= m; i++)
        {
            scanf("%d%d%d", &x, &y, &z);
            add_edge(x, y, (ll_t)z);
        }
        for (int i = 1; i <= n; i++)
        {
            //这里无需清零dis数组，因为如果有负环总是会不断更新答案的
            SPFA(i);
            if (has)
                break;
        }
        has ? printf("YE5\n") : printf("N0\n");
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}