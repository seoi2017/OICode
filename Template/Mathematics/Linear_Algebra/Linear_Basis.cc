#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#define N 64
using namespace std;
typedef unsigned long long ull_t;
class LB_t
{
  private:
    ull_t s[N], m[N];

  public:
    LB_t()
    {
        memset(m, 0, sizeof(m));
        for (int i = 0; i < N; i++) //ULL只有64位，所以1右移最多63位，再多就出去了，会导致WA
            m[i] = (1ULL << i);
    }
    inline bool insert(ull_t x)
    {
        for (int i = N - 1; i >= 0; i--) //与上面同理
            if (x & (1ULL << i))
                if (!s[i])
                {
                    s[i] = x;
                    break;
                }
                else
                    x ^= s[i];
        return x > 0;
    }
    inline ull_t query()
    {
        ull_t ans = 0ULL;
        for (int i = N - 1; i >= 0; i--) //与上面同理
            if ((ans ^ s[i]) > ans)
                ans ^= s[i];
        return ans;
    }
} basis;
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    int n;
    ull_t t;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        scanf("%llu", &t);
        basis.insert(t);
    }
    printf("%llu\n", basis.query());
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}