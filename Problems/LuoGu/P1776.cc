//LuoGu-P1776
//tag:[多重背包（动态规划）]
//Code By HYS.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 1000007
#define M 40007
using namespace std;
struct good_t
{
    int c, w;
} g[N];
int n, m, top, f[M];
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1, x, y, z; i <= n; i++)
    {
        scanf("%d%d%d", &x, &y, &z);
        for (int k = 1; k <= z; k <<= 1)
            g[++top].w = k * x, g[top].c = k * y, z -= k;
        if (z)
            g[++top].w = z * x, g[top].c = z * y;
    }
    for (int i = 1; i <= top; i++)
        for (int j = m; j >= g[i].c; j--)
            f[j] = max(f[j], f[j - g[i].c] + g[i].w);
    printf("%d\n", f[m]);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}