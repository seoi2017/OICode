//LuoGu-P1910
//tag:[01背包（动态规划）]
//Code By HYS.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 1003
using namespace std;
struct people_t
{
    int a, b, c;
    people_t() : a(0), b(0), c(0) {}
} r[N];
int n, m, x, f[N][N];
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &m, &x);
    for (int i = 1; i <= n; i++)
        scanf("%d%d%d", &r[i].a, &r[i].b, &r[i].c);
    for (int i = 1; i <= n; i++)
        for (int j = m; j >= r[i].b; j--)
            for (int k = x; k >= r[i].c; k--)
                f[j][k] = max(f[j][k], f[j - r[i].b][k - r[i].c] + r[i].a);
    printf("%d\n", f[m][x]);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}