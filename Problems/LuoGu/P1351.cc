//LuoGu-P1351
//tag:[树形DP（动态规划）]
//Code By HYS.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 200007
#define P 10007
using namespace std;
struct edge_t
{
    int dat;
    edge_t *nxt;
} p[(N << 1) + N];
int n, m, top, w[N], mxa, ans;
bool vis[N];
inline void add_edge(int x, int y)
{
    p[++top].dat = y, p[top].nxt = p[x].nxt, p[x].nxt = &p[top];
}
void DFS(int x, int old)
{
    vis[x] = true;
    int tmp = 0, mx1 = 0, mx2 = 0;
    for (edge_t *k = p[x].nxt; k != NULL; k = k->nxt)
    {
        if (k->dat == old)
            continue;
        if (w[k->dat] >= mx1)
        {
            swap(mx1, mx2);
            mx1 = w[k->dat];
        }
        else if (w[k->dat] > mx2)
            mx2 = w[k->dat];
        tmp = (tmp + w[k->dat]) % P;
        ans = (ans + w[k->dat] * w[old] * 2) % P;
        mxa = max(mxa, w[k->dat] * w[old]);
        if (!vis[k->dat])
            DFS(k->dat, x);
    }
    mxa = max(mxa, mx1 * mx2);
    for (edge_t *k = p[x].nxt; k != NULL; k = k->nxt)
    {
        if (k->dat == old)
            continue;
        ans = (ans + (tmp - w[k->dat]) * w[k->dat]) % P;
    }
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d", &n);
    top = n;
    for (int i = 1, x, y; i < n; i++)
    {
        scanf("%d%d", &x, &y);
        add_edge(x, y);
        add_edge(y, x);
    }
    for (int i = 1; i <= n; i++)
        scanf("%d", &w[i]);
    DFS(1, 0);
    printf("%d %d\n", mxa, (ans % P + P) % P); //妈卖批的狗血错误
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}