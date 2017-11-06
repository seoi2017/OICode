//LuoGu-P2639
//tag:[背包（动态规划）]
//Code By HYS.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 50007
using namespace std;
int n, v, c[N], f[N], ans;
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &v, &n);
    for (int i = 1; i <= n; i++)
        scanf("%d", &c[i]);
    for (int i = 1; i <= n; i++)
        for (int j = v; j >= c[i]; j--)
            f[j] = max(f[j - c[i]] + c[i], f[j]);
    printf("%d\n", f[v]);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}