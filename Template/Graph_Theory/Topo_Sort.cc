#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <queue>
#define N 10007
#define M 500007
using namespace std;
struct edge_t
{
    int dat, len;
    edge_t *nxt;
} p[N + M];
int n, m, top, ind[N];
inline void add_edge(int x, int y, int z)
{
    p[++top].dat = y, p[top].len = z, p[top].nxt = p[x].nxt, p[x].nxt = &p[top];
}
queue<int> Q;
inline void toposort()
{
    for (int i = 1; i <= n; ++i)
        for (int j = 1; j <= n; ++j)
            if (ind[j] == 0)
            {
                Q.push(j);
                for (edge_t *k = p[j].nxt; k != NULL; k = k->nxt)
                    --ind[k->dat];
                --ind[j];
                break;
            }
    while (!Q.empty())
    {
        printf("%d ", Q.front());
        Q.pop();
    }
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    top = n;
    for (int i = 1, x, y, z; i <= m; ++i)
    {
        scanf("%d%d%d", &x, &y, &z);
        add_edge(x, y, z);
        ++ind[y];
    }
    toposort();
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}