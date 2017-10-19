#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 100007
using namespace std;
typedef long long ll_t;
struct node_t
{
    ll_t s, lzy;
    int l, r, size;
    node_t *lc, *rc;
    inline void pushup()
    {
        this->s = this->lc->s + this->rc->s;
    }
};
class seg_t
{
  private:
    node_t seg[N << 2];
    int top;
    inline void pushdown(node_t *now)
    {
        if (now->lzy == 0LL)
            return;
        now->lc->lzy += now->lzy;
        now->rc->lzy += now->lzy;
        //下面这里不能乘各自子节点的lazy标记，因为子节点的lazy标记可能不为零
        now->lc->s += now->lzy * now->lc->size;
        now->rc->s += now->lzy * now->rc->size;
        now->lzy = 0LL;
    }

  public:
    node_t *root;
    seg_t()
    {
        this->root = NULL, this->top = 0;
    }
    inline node_t *build(int l, int r)
    {
        node_t *now = &this->seg[++top];
        now->l = l, now->r = r, now->lzy = 0LL;
        if (l == r)
        {
            scanf("%lld", &now->s);
            now->size = 1;
        }
        else
        {
            int mid = (l + r) >> 1;
            now->lc = build(l, mid);
            now->rc = build(mid + 1, r);
            now->pushup();
            now->size = now->lc->size + now->rc->size;
        }
        return now;
    }
    void update(node_t *now, int l, int r, ll_t x)
    {
        if (l <= now->l && now->r <= r)
        {
            now->lzy += x, now->s += x * now->size;
            return;
        }
        pushdown(now);
        int mid = (now->l + now->r) >> 1; //必须是本节点的范围，不要用参数算
        if (l <= mid)
            update(now->lc, l, r, x);
        if (r > mid)
            update(now->rc, l, r, x);
        now->pushup();
    }
    ll_t query(node_t *now, int l, int r)
    {
        if (l <= now->l && now->r <= r)
            return now->s;
        pushdown(now);
        int mid = (now->l + now->r) >> 1; //必须是本节点的范围，不要用参数算
        ll_t ans = 0LL;
        if (l <= mid)
            ans += query(now->lc, l, r);
        if (r > mid)
            ans += query(now->rc, l, r);
        return ans;
    }
} tree;
int n, m;
ll_t k;
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    tree.root = tree.build(1, n);
    for (int i = 1, c, x, y; i <= m; i++)
    {
        scanf("%d%d%d", &c, &x, &y);
        switch (c)
        {
        case 1:
            scanf("%lld", &k);
            tree.update(tree.root, x, y, k);
            break;
        case 2:
            printf("%lld\n", tree.query(tree.root, x, y));
            break;
        default:
            break;
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}