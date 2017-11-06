//LuoGu-P2871
//tag:[01背包（动态规划）]
//Code By HYS.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 20007
using namespace std;
int n, v, c[N], w[N], f[N];
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &v);
    for (int i = 1; i <= n; i++)
        scanf("%d%d", &c[i], &w[i]);
    for (int i = 1; i <= n; i++)
        for (int j = v; j >= c[i]; j--)
            f[j] = max(f[j], f[j - c[i]] + w[i]);
    printf("%d\n", f[v]);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}