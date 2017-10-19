#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 10007
using namespace std;
struct q_t
{
    int l, r, id, lst;
    q_t(int l = 0, int r = 0, int id = 0, int lst = 0) : l(l), r(r), id(id), lst(lst) {}
} q[N];
struct c_t
{
    int x, y;
    c_t(int x = 0, int y = 0) : x(x), y(y) {}
} c[N];
int n, m, col[N], block[N], qid, cid, col_tot[N], ans[N], res;
char s[2];
inline bool cmp(const q_t &x, const q_t &y)
{
    if (block[x.l] == block[y.l])
        if (x.r == x.r)
            return x.lst < y.lst;
        else
            return x.r < y.r;
    else
        return x.l < y.l;
}
inline void change(int now, int x)
{
    if (c[now].x >= q[x].l && c[now].x <= q[x].r)
    {
        col_tot[col[c[now].x]]--;
        if (!col_tot[col[c[now].x]])
            res--;
        if (!col_tot[c[now].y])
            res++;
        col_tot[c[now].y]++;
    }
    swap(col[c[now].x], c[now].y);
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%d", &col[i]);
        block[i] = (i - 1) / sqrt(n) + 1;
    }
    for (int i = 1, x, y; i <= m; i++)
    {
        scanf("%s%d%d", s, &x, &y);
        if (s[0] == 'Q')
            q[++qid] = q_t(x, y, qid, cid);
        else
            c[++cid] = c_t(x, y);
    }
    sort(q + 1, q + 1 + qid, cmp);
    int l = 0, r = 0, now = 0;
    for (int i = 1; i <= qid; i++)
    {
        while (l < q[i].l)
        {
            col_tot[col[l]]--;
            if (!col_tot[col[l]])
                res--;
            l++;
        }
        while (l > q[i].l)
        {
            l--;
            if (!col_tot[col[l]])
                res++;
            col_tot[col[l]]++;
        }
        while (r > q[i].r)
        {
            col_tot[col[r]]--;
            if (!col_tot[col[r]])
                res--;
            r--;
        }
        while (r < q[i].r)
        {
            r++;
            if (!col_tot[col[r]])
                res++;
            col_tot[col[r]]++;
        }
        while (now < q[i].lst)
            now++, change(now, i);
        while (now > q[i].lst)
            change(now, i), now--;
        ans[q[i].id] = res;
    }
    for (int i = 1; i <= qid; i++)
        printf("%d\n", ans[i]);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}