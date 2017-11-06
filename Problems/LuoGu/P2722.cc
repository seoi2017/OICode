//LuoGu-P2722
//tag:[完全背包（动态规划）]
//Code By HYS.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 10007
using namespace std;
int v, n, f[N], w[N], c[N];
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &v, &n);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &w[i], &c[i]);
    for (int i = 1; i <= n; i++)
        for (int j = c[i]; j <= v; j++)
            f[j] = max(f[j], f[j - c[i]] + w[i]);
    printf("%d\n", f[v]);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}