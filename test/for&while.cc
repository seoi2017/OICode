#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
int n,m,s;
int main(){
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++){
        register int t=1; 
        do printf("%d\n",t++);
        while(t<=m);
    }
    printf("%d\n",n+m);
    fclose(stdin);
    fclose(stdout);
    return 0;
}