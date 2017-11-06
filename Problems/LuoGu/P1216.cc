//LuoGu-P1216
//tag:[简单动归（动态规划）]
//Code By HYS.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 1003
using namespace std;
int r, ans, a[N][N], f[N][N];
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d", &r);
    for (int i = 1; i <= r; i++)
        for (int j = 1; j <= i; j++)
        {
            scanf("%d", &a[i][j]);
            f[i][j] = max(f[i - 1][j], f[i - 1][j - 1]) + a[i][j];
            if (i == r)
                ans = max(ans, f[i][j]);
        }
    printf("%d\n", ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}