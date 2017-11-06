#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <set>
using namespace std;
int n;
multiset<int> heap;
int main()
{
#ifdef LOCAL
    freopen("io/in", "r", stdin);
    freopen("io/out", "w", stdout);
#endif
    scanf("%d", &n);
    for (int c, x; n; n--)
    {
        scanf("%d", &c);
        switch (c)
        {
        case 1:
            scanf("%d", &x), heap.insert(x);
            break;
        case 2:
            printf("%d\n", *heap.begin());
            break;
        case 3:
            heap.erase(heap.begin());
            break;
        default:
            break;
        }
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}