#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 1000007
#define M 1007
using namespace std;
char n[N], m[M];
int nxt[N];
inline void find_next(char *str)
{
    int len = strlen(str);
    nxt[0] = -1;
    for (int i = 1, now; i < len; i++)
    {
        now = nxt[i - 1];
        while (now >= 0 && str[now + 1] != str[i])
            now = nxt[now];
        if (str[i] == str[now + 1])
            nxt[i] = now + 1;
        else
            nxt[i] = -1;
    }
}
inline void KMP(char *str, char *c)
{
    int slen = strlen(str), clen = strlen(c);
    int sptr = 0, cptr = 0;
    while (sptr < slen)
    {
        if (cptr == clen)
        {
            printf("%d\n", sptr - clen + 1);
        }
        if (str[sptr] == c[cptr])
            sptr++, cptr++;
        else
        {
            if (cptr == 0)
                sptr++;
            else
                cptr = nxt[cptr - 1] + 1;
        }
    }
    if (cptr == clen)
        printf("%d\n", sptr - clen + 1);
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    memset(nxt, -1, sizeof(nxt));
    scanf("%s%s", n, m);
    find_next(m);
    KMP(n, m);
    for (int i = 0; i < strlen(m); i++)
        printf("%d ", nxt[i] + 1);
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}