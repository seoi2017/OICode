#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 33000007
using namespace std;
char c[N], s[N];
int len[N], n;
inline int Manacher(char *str)
{
    int res = 0, mx = 0, id;
    for (int i = 1; i < n; i++)
    {
        if (i < mx)
            len[i] = min(len[2 * id - i], len[id] + id - i);
        else
            len[i] = 1;
        while (str[i + len[i]] == str[i - len[i]])
            len[i]++;
        if (len[i] + i > mx)
            mx = len[i] + i, id = i;
    }
    for (int i = 0; i < n; i++)
        res = max(res, len[i]); //取得最长回文子串长度
    return res - 1;             //由len数组的性质，减一即为答案
}
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%s", c);
    //从原字符串c中预处理出新字符串s
    s[0] = s[1] = '#';
    n = strlen(c);
    for (int i = 0; i < n; i++)
        s[i * 2 + 2] = c[i], s[i * 2 + 3] = '#';
    n = n * 2 + 2, s[n] = '\0';
    //预处理完成，开始Manacher算法
    printf("%d\n", Manacher(s));
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}