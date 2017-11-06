#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 100007
using namespace std;
struct node_t
{
    int dat, len, ind;
    node_t *l, *r;
    node_t(int x, int y, int z) : dat(x), len(y), ind(z), l(NULL), r(NULL) {}
} * p[N];
int n, m, f[N];
int root(int x)
{
    return f[x] == x ? x : root(f[x]); //不能路径压缩！不然下层节点找祖先都找到NULL去了！
}
node_t *marge(node_t *a, node_t *b)
{
    if (!a || !b)
        return !a ? b : a;
    if (a->dat > b->dat || (a->dat == b->dat && a->ind > b->ind))
        swap(a, b);
    a->r = marge(a->r, b);
    f[a->r->ind] = a->ind; //不能路径压缩！
    if (a->l ? a->l->len : 0 < a->r->len)
        swap(a->r, a->l);
    a->len = a->r ? a->r->len + 1 : 1;
    return a;
}
inline int erase(node_t *a)
{
    int ans = a->dat;
    f[a->ind] = 0;
    if (a->l)
        f[a->l->ind] = a->l->ind; //不能路径压缩！
    if (a->r)
        f[a->r->ind] = a->r->ind; //不能路径压缩！
    marge(a->l, a->r);
    return ans;
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1, x; i <= n; i++)
    {
        scanf("%d", &x);
        p[i] = new node_t(x, 1, i);
        f[i] = i;
    }
    for (int i = 1, c, x, y; i <= m; i++)
    {
        scanf("%d%d", &c, &x);
        int fx = root(x);
        if (c == 1)
        {
            scanf("%d", &y);
            int fy = root(y);
            if (!fx || !fy || fx == fy)
                continue;
            marge(p[fx], p[fy]);
        }
        else if (fx)
            printf("%d\n", erase(p[fx]));
        else
            printf("-1\n");
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}