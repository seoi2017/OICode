#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 100007
#define M 100007
using namespace std;
struct edge_t
{
    int dat;
    edge_t *nxt;
} p[N + (M * 2)];
int n, m, low[N], dfn[N], top, cnt, ans;
bool cut[N];
inline void add_edge(int x, int y)
{
    p[++top].dat = y, p[top].nxt = p[x].nxt, p[x].nxt = &p[top];
    p[++top].dat = x, p[top].nxt = p[y].nxt, p[y].nxt = &p[top];
}
void Tarjan(int x, int lst)
{
    int tot = 0;
    low[x] = dfn[x] = ++cnt;
    for (edge_t *k = p[x].nxt; k != NULL; k = k->nxt)
    {
        int y = k->dat;
        if (!dfn[y])
        {
            Tarjan(y, lst);
            low[x] = min(low[x], low[y]);
            if (low[y] == dfn[x] && x != lst) //不是根，但y最多连接到x，即删掉x后y断开连接，为割点
                cut[x] = true;                //不能在这里更新ans，可能会有重复
            if (x == lst)
                tot++;
        }
        low[x] = min(low[x], dfn[y]);
    }
    if (x == lst && tot >= 2) //是根，且有两个以上子节点，为割点
        cut[lst] = true;      //不能在这里更新ans，可能会有重复
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    top = n;
    for (int i = 1, x, y; i <= m; i++)
    {
        scanf("%d%d", &x, &y);
        add_edge(x, y);
    }
    for (int i = 1; i <= n; i++)
        if (!dfn[i]) //由于可能不连通，每个点都需要查询一遍
            Tarjan(i, i);
    for (int i = 1; i <= n; i++)
        if (cut[i])
            ans++;
    printf("%d\n", ans);
    for (int i = 1; i <= n; i++)
        if (cut[i])
            printf("%d ", i);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}