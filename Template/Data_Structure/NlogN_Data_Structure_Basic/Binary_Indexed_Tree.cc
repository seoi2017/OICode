#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 500007
using namespace std;
typedef long long ll_t;
int n, m;
ll_t c[N];
inline int lowbit(int x)
{
    return x & (-x);
}
inline void bit_add(int x, int s)
{
    for (int i = x; i <= n; i += lowbit(i))
        c[i] += (s * 1LL);
}
inline ll_t bit_sum(int x)
{
    ll_t ans = 0;
    for (int i = x; i > 0; i -= lowbit(i))
        ans += c[i];
    return ans;
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1, lt, t; i <= n; i++)
    {
        scanf("%d", &t);
        bit_add(i, t);        //[1]维护前缀和
        //bit_add(i, t - lt); //[2]维护差分前缀和
        lt = t;
    }
    for (int i = 1, t, tx, ty, tz; i <= m; i++)
    {
        scanf("%d%d", &t, &tx);
        switch (t)
        {
        case 1:
            scanf("%d", &ty);                        //[1]
            bit_add(tx, ty);                         //[1]在tx的位置加上ty，维护前缀和
            //scanf("%d%d", &ty, &tz);               //[2]
            //bit_add(tx, tz), bit_add(ty + 1, -tz); //[2]给[tx,ty]区间加，维护差分前缀和
            break;
        case 2:
            scanf("%d", &ty);                                    //[1]
            printf("%lld\n", bit_sum(ty) - bit_sum(tx - 1));     //[1]查询[tx,ty]的区间和
            //printf("%lld\n", bit_sum(tx));                     //[2]查询tx，由于维护的是差分前缀和，直接查询即可
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