#include <bits/stdc++.h>    
using namespace std; 

#define ll long long

const int maxn = 50010;

struct node{
	int id;
	int score;
	bool operator<(const node& other)const{
		if(score!=other.score)return score<other.score;
		return id<other.id;
	}
	node(int id,int score):id(id),score(score){
	}
	node(){
	}
};

bitset<maxn> bs[6][250];
node a[6][maxn];
bitset<maxn> ans;

int main(){
	int t;
	cin>>t;
	while(t--){
		int n,m;
		cin>>n>>m;
		
		for(int j=1;j<=n;j++){
			for(int i=1;i<=5;i++){
				scanf("%d",&a[i][j].score);
				a[i][j].id=j;
			}
		}
		for(int i=1;i<=5;i++)sort(a[i]+1,a[i]+n+1);
		
		int SQRT = sqrt(n);
		for(int i=1;i<=5;i++){
			for(int div=1;(div-1)*SQRT<n;div++){
				bs[i][div].reset();
				bs[i][div]=bs[i][div-1];
				int start=(div-1)*SQRT;
				for(int j=1;j<=SQRT;j++){
					if(start+j>n)break;
					bs[i][div].set(a[i][start+j].id);
				}
			}
		}
		int q;
		cin>>q;
		int Last=0;
		while(q--){
			int b[6];
			for(int i=1;i<=5;i++){
				scanf("%d",&b[i]);
				b[i]^=Last;
			}
			
			ans.reset();
			int tmp = lower_bound(a[1]+1,a[1]+n+1, node(n+1,b[1]) )-(a[1]+1);
			tmp=tmp/SQRT;			
			ans = bs[1][tmp];
			for(int j=tmp*SQRT+1;a[1][j].score<=b[1]&&j<=n;j++){
				ans.set(a[1][j].id);
			}
			for(int i=2;i<=5;i++){
				tmp = lower_bound(a[i]+1,a[i]+n+1, node(n+1,b[i]) )-(a[i]+1);
				tmp=tmp/SQRT;
				bitset<maxn> tbs = bs[i][tmp];
				for(int j=tmp*SQRT+1;a[i][j].score<=b[i]&&j<=n;j++){
					tbs.set(a[i][j].id);
				}
				ans &= tbs;
			}
			int re=ans.count();
			Last=re;
			printf("%d\n",re);
		}
	}
	return 0;
}