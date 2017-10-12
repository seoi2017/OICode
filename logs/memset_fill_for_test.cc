#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cstring>
#include<cmath>
#include<ctime>
#define N 300000000
using namespace std;
int a[N];
int main(){
#ifdef LOCAL
    freopen("io/out","w",stdout);
#endif
    time_t now;
    for(int i=1;i<=10;i++){
        now=clock();
        fill(a,a+N,0);
        cout<<"fill function test No."<<i<<":"<<clock()-now<<"ms"<<endl;
    }
    for(int i=1;i<=10;i++){
        now=clock();
        memset(a,0,sizeof(a));
        cout<<"memset function test No."<<i<<":"<<clock()-now<<"ms"<<endl;
    }
    for(int i=1;i<=10;i++){
        now=clock();
        for(int j=0;j<N;j++)a[j]=0;
        cout<<"for filling test No."<<i<<":"<<clock()-now<<"ms"<<endl;
    }
#ifdef LOCAL
    fclose(stdout);
#endif
    return 0;
}