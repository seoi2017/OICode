//LuoGu-P1064
//tag:[01背包（动态规划）]
//Code By HYS.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 63
#define MX 32007
using namespace std;
struct good_t
{
    int v, w, v_1, w_1, v_2, w_2;
    good_t() : v(0), v_1(0), v_2(0) {}
} g[N];
int n, m, top, f[MX], o[N];
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    n /= 10;
    for (int i = 1, x, y, z; i <= m; i++)
    {
        scanf("%d%d%d", &x, &y, &z);
        x /= 10;
        if (!z)
            o[i] = ++top, g[o[i]].v = x, g[o[i]].w = x * y;
        else if (g[o[z]].v_1)
            g[o[z]].v_2 = x, g[o[z]].w_2 = x * y;
        else
            g[o[z]].v_1 = x, g[o[z]].w_1 = x * y;
    }
    for (int i = 1; i <= top; i++)
        for (int j = n; j >= 0; j--)
        {
            if (j >= g[i].v)
                f[j] = max(f[j], f[j - g[i].v] + g[i].w);
            if (g[i].v_1 && j >= (g[i].v + g[i].v_1))
                f[j] = max(f[j], f[j - (g[i].v + g[i].v_1)] + (g[i].w + g[i].w_1));
            if (g[i].v_2 && j >= (g[i].v + g[i].v_2))
                f[j] = max(f[j], f[j - (g[i].v + g[i].v_2)] + (g[i].w + g[i].w_2));
            if (g[i].v_1 && g[i].v_2 && j >= (g[i].v + g[i].v_1 + g[i].v_2))
                f[j] = max(f[j], f[j - (g[i].v + g[i].v_1 + g[i].v_2)] + (g[i].w + g[i].w_1 + g[i].w_2));
        }
    printf("%d\n", f[n] * 10);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}