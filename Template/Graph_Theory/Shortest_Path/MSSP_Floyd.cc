#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 107
using namespace std;
int n, m, f[N][N], a[N * N];
inline void Floyd()
{
    memset(f, 0x3F, sizeof(f));
    for (int i = 1; i <= n; ++i)
    {
        f[i][i] = 0;
        for (int j = 1; j <= n; ++j)
            scanf("%d", &f[i][j]);
    }
    for (int k = 1; k <= n; ++k)
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= n; ++j)
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
}
inline long long solve()
{
    long long ans = 0LL;
    a[0] = 1;
    for (int i = 1; i <= m; ++i)
        ans += 1LL * f[a[i - 1]][a[i]];
    return ans;
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; ++i)
        scanf("%d", &a[i]);
    Floyd();
    printf("%lld\n", solve());
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}