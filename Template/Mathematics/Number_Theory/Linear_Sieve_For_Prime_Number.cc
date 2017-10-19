#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 10000007
using namespace std;
bool vis[N];
int prime[N], tot, n, m;
inline void solve(int x)
{
    for (int i = 2; i <= x; i++)
    {
        if (!vis[i])
            prime[++tot] = i;
        for (int j = 1; (j <= tot && i * prime[j] <= x); j++)
        {
            vis[i * prime[j]] = true;
            if (!(i % prime[j]))
                break;
        }
    }
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    solve(n);
    for (int i = 1, q; i <= m; i++)
    {
        scanf("%d", &q);
        int l = 1, r = tot + 1;
        while (l < (r - 1))
        {
            int mid = (l + r) >> 1;
            if (prime[mid] > q)
                r = mid;
            else
                l = mid;
        }
        prime[l] == q ? printf("Yes\n") : printf("No\n");
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}