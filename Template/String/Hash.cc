#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <map>
using namespace std;
const int prime[4] = {131313131, 19260817, 1000000007, 100000009};
const int seed = 131;
int cnt, n, m;
char c[2048];
map<int, bool> ind[4];
inline int hash(int t, char *str)
{
    int len = strlen(str), ans = 0;
    for (int i = 0; i < len; i++)
        ans = (ans * seed + str[i]) % prime[t];
    return ans;
}
inline bool judge(char *str)
{
    int ans = 0;
    for (int i = 0, j; i < 4; i++)
    {
        j = hash(i, str);
        if (ind[i].find(j) != ind[i].end())
            ans++;
        else
            ind[i][j] = true;
    }
    return ans == 4 ? true : false;
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++)
    {
        scanf("%s", c);
        if (!judge(c))
            cnt++;
    }
    printf("%d\n", cnt);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}