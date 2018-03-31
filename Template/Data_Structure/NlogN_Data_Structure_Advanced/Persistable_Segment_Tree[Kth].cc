//区间第K大
//时间、空间复杂度仍有较大优化空间
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 200007
#define mid ((l + r) / 2)
using namespace std;
int n, m, ori[N];
struct num_t
{
    int id, dat;
} c[N];
inline bool cmp1(const num_t &x, const num_t &y)
{
    return x.dat < y.dat;
}
inline bool cmp2(const num_t &x, const num_t &y)
{
    return x.id < y.id;
}
struct node_t
{
    int s;
    node_t *lc, *rc;
};
class seg_t
{
  private:
    node_t seg[N * 60];
    int top, ver;

  public:
    node_t *root[N];
    node_t *build(int l, int r)
    {
        node_t *now = &seg[++top];
        now->s = 0;
        if (l != r)
        {
            now->lc = build(l, mid);
            now->rc = build(mid + 1, r);
        }
        return now;
    }
    inline void build()
    {
        root[ver] = build(1, n);
    }
    seg_t()
    {
        this->top = 0;
        this->ver = 0;
    }
    node_t *insert(node_t *old, int num, int l, int r)
    {
        node_t *now = &seg[++top];
        now->lc = old->lc, now->rc = old->rc;
        now->s = old->s + 1;
        if (l < r)
        {
            if (num <= mid)
                now->lc = insert(old->lc, num, l, mid);
            else
                now->rc = insert(old->rc, num, mid + 1, r);
        }
        return now;
    }
    inline void insert(int num)
    {
        node_t *fresh_ver = insert(root[ver], num, 1, n);
        root[++ver] = fresh_ver;
    }
    int query(node_t *lt, node_t *rt, int l, int r, int k)
    {
        if (l == r)
            return l;
        int t = rt->lc->s - lt->lc->s;
        if (t >= k)
            return query(lt->lc, rt->lc, l, mid, k);
        else
            return query(lt->rc, rt->rc, mid + 1, r, k - t);
    }
} tree;
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d", &c[i].dat);
        c[i].id = i;
    }
    sort(c + 1, c + 1 + n, cmp1);
    for (int i = 1; i <= n; ++i)
    {
        ori[i] = c[i].dat;
        c[i].dat = i;
    }
    sort(c + 1, c + 1 + n, cmp2);
    tree.build();
    for (int i = 1; i <= n; ++i)
        tree.insert(c[i].dat);
    for (int i = 1, l, r, k; i <= m; ++i)
    {
        scanf("%d%d%d", &l, &r, &k);
        printf("%d\n", ori[tree.query(tree.root[l - 1], tree.root[r], 1, n, k)]);
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}