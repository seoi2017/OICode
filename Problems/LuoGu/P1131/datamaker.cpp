#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<ctime>
using namespace std;
const int N=500000;
int n,s,fa[N];
inline int random(int x)
{
	return rand()%x+1;
}
inline int findfa(int x)
{
	return fa[x]==x?x:fa[x]=findfa(fa[x]);
}
int main()
{
	srand(time(NULL)*time(NULL));
	n=random(N),s=random(n);
	printf("%d\n%d\n",n,s);
	for(int i=1;i<=n;++i)
		fa[i]=i;
	int cnt=0;
	while(cnt<n-1)
	{
		int x=random(n),y=random(n);
		int fx=findfa(x),fy=findfa(y);
		if(fx==fy)
			continue;
		fa[fy]=fx;
		printf("%d %d %d\n",x,y,random(N));
		cnt++;
	}
	//system("pause");
	return 0;
}
