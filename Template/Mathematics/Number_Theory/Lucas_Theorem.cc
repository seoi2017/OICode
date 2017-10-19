#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 100007
using namespace std;
typedef long long ll_t;
int fac[N], inv[N];
inline int expow(int n, int m, int p)
{
    int ans = 1;
    while (m)
    {
        if (m & 1)
            ans = (ll_t)ans * n % p;
        n = (ll_t)n * n % p;
        m >>= 1;
    }
    return ans;
}
inline int C(int m, int n, int p)
{
    if (m > n)
        return 0;
    return (ll_t)fac[n] * expow(fac[m], p - 2, p) % p * expow(fac[n - m], p - 2, p) % p; //逆元详见欧拉定理
}
/*
乘法逆元的若干求法：
1、线性递推
2、欧拉函数+快速幂
3、扩展欧几里得
4、威尔逊定理（专用于递推阶乘逆元）
还有P不是质数的……
*/
int Lucas(int m, int n, int p)
{
    if (!m)
        return 1;
    return (ll_t)Lucas(m / p, n / p, p) * C(m % p, n % p, p) % p;
}
int T;
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d", &T);
    for (int n, m, p; T; T--)
    {
        scanf("%d%d%d", &n, &m, &p);
        fac[0] = 1;
        for (int i = 1; i <= p; i++)
            fac[i] = (ll_t)fac[i - 1] * i % p;
        printf("%d\n", Lucas(m, n + m, p));
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}