//POJ-1681[Accepted]
//Tag:[高斯消元（线性代数）]
//Code By HYS.
//16ms,1.0MB(952KB),2876B
#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<cmath>
#include<cstring>
#define INF 0x3f3f3f3f
#define MX 16*16
using namespace std;
int T,n,mt[MX][MX],len,freeyuan[MX],t=0;
char c;
int x[MX];//临时增广列向量
inline int Gauss(){
    int index,res;
    for(int i=1;i<=len;i++){
        index=i;//重要步骤，切记
        for(int j=i+1;j<=len;j++)
            if(mt[j][i]>mt[i][i])index=j;
        if(mt[index][i]==0){
            freeyuan[++t]=i;//找到自由元
            continue;
        }
        if(index!=i)
            for(int j=1;j<=len+1;j++)
                swap(mt[i][j],mt[index][j]);
        for(int j=1;j<=len;j++)
            if(mt[j][i] && i!=j)//重要步骤，切记
                for(int k=1;k<=len+1;k++)
                    mt[j][k]^=mt[i][k];
    }
    for(int i=len-t+1;i<=len;i++)
        if(mt[i][len+1])return 1;//对于所有系数全为0的方程，如果等号右侧不为0则无解
    return 0;//有唯一解或有自由元
}
inline int FreeYuan(){//异或方程枚举自由元
    int res=INF;
    int s=(1<<t);
    memset(x,0,sizeof(x));
    for(int i=0;i<s;i++){//二进制枚举所有可能的情况
        int cnt=0;
        for(int j=1;j<=t;j++)//对于每一个自由元赋值
            if(x[freeyuan[j]]=(bool)(i&(1<<(j-1))))cnt++;//赋值为1的自由元最终对答案肯定有1的贡献
            //至于为什么是1<<(j-1)，因为统共有效的二进制位有t位，而若右移t位实为移动到了第t+1位，造成WA
            //但是这题数据太水，不减一竟然能过，但到了POJ1753就过不了了，必须减一
        for(int j=len-t;j>=1;j--){//从最下面一行没有自由元的方程向上消元
            int tmp=mt[j][len+1];//暂存当前方程的增广值
            for(int k=j+1;k<=len;k++){
                //由于临时增广值数组x在j+1位之后的值都已得到，所以下面这句话是有效的
                tmp^=(mt[j][k]&x[k]);
                /*
                可能上面那句话不好理解，等效代码如下：
                if(mt[j][k]){
                    tmp^=x[k];
                }
                */
            }
            if(x[j]=tmp)cnt++;//保存增广值到临时数组的同时，若为1则答案+1
        }
        res=min(res,cnt);
    }
    return res;
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    scanf("%d",&T);
    while(T--){
        scanf("%d",&n);
        len=n*n,t=0;
        memset(mt,0,sizeof(mt));
        for(int i=1;i<=n;i++){
            scanf("\n");
            for(int j=1;j<=n;j++){
                scanf("%c",&c);
                if(c=='y')mt[(i-1)*n+j][len+1]=0;
                else mt[(i-1)*n+j][len+1]=1;
            }
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                register int now=(i-1)*n+j;
                mt[now][now]=1;//自己对自己有影响
                if(j-1>0)mt[now][now-1]=1;//对左侧有影响
                if(j+1<=n)mt[now][now+1]=1;//对右侧有影响
                if(i-1>0)mt[now][now-n]=1;//对上方有影响
                if(i+1<=n)mt[now][now+n]=1;//对下方有影响
            }
        }
        if(Gauss())printf("inf\n");
        else printf("%d\n",FreeYuan());
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}