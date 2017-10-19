#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 100007
using namespace std;
typedef long long ll_t;
int n, m, p;
struct node_t
{
    int l, r, size;
    ll_t lm, la, s;
    node_t *lc, *rc;
    inline void pushup()
    {
        this->s = (this->lc->s + this->rc->s) % p;
    }
};
class seg_t
{
  private:
    node_t seg[N << 2];
    int top;
    inline void pushdown(node_t *now, node_t *lson, node_t *rson)
    {
        if (now->lm == 1 && now->la == 0)
            return;
        lson->lm = lson->lm * now->lm % p;
        rson->lm = rson->lm * now->lm % p;
        lson->la = (lson->la * now->lm + now->la) % p;
        rson->la = (rson->la * now->lm + now->la) % p;
        lson->s = (lson->s * now->lm + lson->size * now->la) % p;
        rson->s = (rson->s * now->lm + rson->size * now->la) % p;
        now->lm = 1, now->la = 0;
    }

  public:
    node_t *root;
    seg_t()
    {
        this->root = NULL, this->top = 0;
    }
    node_t *build(int l, int r)
    {
        node_t *now = &this->seg[++top];
        now->l = l, now->r = r, now->lm = 1LL, now->la = 0LL;
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
    void add_update(node_t *now, int l, int r, ll_t v)
    {
        if (l <= now->l && now->r <= r)
        {
            now->la = (now->la + v) % p;
            now->s = (now->s + now->size * v) % p;
            return;
        }
        pushdown(now, now->lc, now->rc);
        int mid = (now->l + now->r) >> 1;
        if (l <= mid)
            add_update(now->lc, l, r, v); //这里是加法更新，不要写成乘法的
        if (r > mid)
            add_update(now->rc, l, r, v);
        now->pushup();
    }
    void mul_update(node_t *now, int l, int r, ll_t v)
    {
        if (l <= now->l && now->r <= r)
        {
            now->la = (now->la * v) % p;
            now->lm = (now->lm * v) % p;
            now->s = (now->s * v) % p;
            return;
        }
        pushdown(now, now->lc, now->rc);
        int mid = (now->l + now->r) >> 1;
        if (l <= mid)
            mul_update(now->lc, l, r, v); //这里是乘法更新，不要写成加法的
        if (r > mid)
            mul_update(now->rc, l, r, v);
        now->pushup();
    }
    ll_t query(node_t *now, int l, int r)
    {
        if (l <= now->l && now->r <= r)
            return now->s;
        pushdown(now, now->lc, now->rc);
        int mid = (now->l + now->r) >> 1;
        ll_t ans = 0LL;
        if (l <= mid)
            ans = ans + query(now->lc, l, r); //先不要取模，因为一个数肯定大不过p
        if (r > mid)
            ans = (ans + query(now->rc, l, r)) % p; //这里再取模，因为两个数就可能大于p了
        now->pushup();
        return ans;
    }
} tree;
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &p);
    tree.root = tree.build(1, n);
    for (int i = 1, c, x, y, z; i <= m; i++)
    {
        scanf("%d%d%d", &c, &x, &y);
        switch (c)
        {
        case 1:
            scanf("%d", &z);
            tree.mul_update(tree.root, x, y, (ll_t)z); //1和2谁加谁乘搞清楚，不要在这种细节上浪费时间
            break;
        case 2:
            scanf("%d", &z);
            tree.add_update(tree.root, x, y, (ll_t)z);
            break;
        default:
            printf("%lld\n", tree.query(tree.root, x, y));
            break;
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}