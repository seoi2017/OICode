//LuoGu-P2347
//tag:[多重背包（动态规划）]
//Code By HYS.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 7
#define MX 1000
using namespace std;
int s[N], c[N] = {0, 1, 2, 3, 5, 10, 20}, ans;
bool f[MX + 1];
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    for (int i = 1; i <= 6; i++)
        scanf("%d", &s[i]);
    f[0] = true;
    for (int i = 1; i <= 6; i++)
        for (int j = 1; j <= s[i]; j++)
            for (int k = MX; k >= 0; k--)
                if (f[k] && k + c[i] <= MX)
                    f[k + c[i]] = true;
    for (int i = 1; i <= MX; i++)
        if (f[i])
            ans++;
    printf("Total=%d\n", ans);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}