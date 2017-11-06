//LuoGu-P2925
//tag:[01背包（动态规划）]
//Code By HYS.
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 50003
using namespace std;
int c, h, v[N], f[N];
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &c, &h);
    for (int i = 1; i <= h; i++)
        scanf("%d", &v[i]);
    for (int i = 1; i <= h; i++)
        for (int j = c; j >= v[i]; j--)
        {
            f[j] = max(f[j], f[j - v[i]] + v[i]);
            if (f[c] == c)
                goto end;
        }
end:
    printf("%d\n", f[c]);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}