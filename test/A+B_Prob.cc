#include<iostream>
#include<cstdio>
#include<cstdlib>
using namespace std;
int a,b;
int main(){
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
    scanf("%d%d",&a,&b);
    printf("%d\n",a+b);
    fclose(stdin);
    fclose(stdout);
    return 0;
}