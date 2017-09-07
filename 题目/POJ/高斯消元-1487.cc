//POJ-1487[Unaccepted]
//Tag:[高斯消元（线性代数）][DFS（搜索）][数学期望（离散数学）]
//Code By HYS.
//0ms,0.2MB(208KB),4125B
//WARNING:C++ Compiler Only(G++ Wrong Answer)
#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<cmath>
#include<algorithm>
#define MX 32
#define MX_STR 4096
#define eps 1e-6
using namespace std;
double mt[MX][MX],x[MX];
char str[MX_STR];
int n,cases=1,ans;
bool unline[MX];
inline int Gauss(){
    int i=1;
    memset(unline,0,sizeof(unline));
    for(int j=1;i<=n,j<=n;i++,j++){
        int index=i;
        for(int k=i+1;k<=n;k++)
            if(fabs(mt[k][j])-fabs(mt[index][j]/*>eps*/)>eps)index=k;//千万不要把比较运算符写括号里面去……（如注释所示）
        if(abs(mt[index][j])<eps){
            i--;
            continue;
        }
        if(index!=i)
            for(int k=j;k<=n+1;k++)
                swap(mt[index][k],mt[i][k]);
        for(int l=1;l<=n;l++)
            if(abs(mt[l][j])>eps && l!=i){
                double t=mt[l][j];
                for(int k=j;k<=n+1;k++)
                    mt[l][k]=mt[l][k]-t/mt[i][j]*mt[i][k];
                    //mt[l][k]=mt[l][k]*mt[i][j]-t*mt[i][k];楞乘会爆精度
            }
    }
    for(int k=i;k<=n;k++)
        if(fabs(mt[k][n+1])>eps)return -1;
    if(i-1<n){
        for(int j=i-1;j>=1;j--){
            int id,cnt=0;
            for(int k=1;k<=n;k++){
                if(fabs(mt[j][k])<eps)continue;
                if(unline[k])continue;
                cnt++;
                id=k;
            }
            if(cnt>1)continue;
            x[id]=mt[j][n+1]/mt[j][id];
            unline[id]=true;
        }
        return 1;  
    }
    for(int k=n;k>=1;k--)
        x[k]=mt[k][n+1]/mt[k][k];
    return 0;
}
void dfs(int x,int l,int r,double p){//括号序DFS构造方程
    int sons=0,ks=0;
    bool noks=true;
    for(int i=l;i<=r;i++){
        if(str[i]==' ')continue;
        sons++;
        if(str[i]=='('){
            noks=false,ks=1,i++;
            while(ks){
                if(str[i]=='(')ks++;
                else if(str[i]==')')ks--;
                i++;
            }
        }
        else while(str[i]!=' ' && str[i]!='(' && str[i]!=')' && i<=r)i++;
        i--;
    }
    p/=sons;
    if(noks){
        for(int i=l;i<=r;i++){
            if(str[i]>='a' && str[i]<='z')
                mt[x][str[i]-'a'+1]-=p;
            else if(str[i]!=' '){
                int tmp;
                sscanf(str+i,"%d",&tmp);
                mt[x][n+1]+=p*tmp;
                i++;
                while(str[i]!=' ' && i<=r)i++;
            }
        }
        return;
    }
    for(int i=l;i<=r;i++){
        if(str[i]==' ')continue;
        int st=i;
        if(str[i]=='('){
            ks=1,i++;
            while(ks){
                if(str[i]=='(')ks++;
                else if(str[i]==')')ks--;
                i++;
            }
            dfs(x,st+1,i-2,p);
        }
        if(str[i]>='a' && str[i]<='z')
            mt[x][str[i++]-'a'+1]-=p;
        else if(str[i]!=' ' && str[i]!='(' && str[i]!=')' && i<=r){
            int tmp;
            sscanf(str+i,"%d",&tmp);
            mt[x][n+1]+=p*tmp;
            i++;
            while(str[i]!=' ' && str[i]!='(' && str[i]!=')' && i<=r)i++;
            i++;
        }
        i--;
    }
}
inline void init(){
    memset(x,0,sizeof(x));
    memset(mt,0,sizeof(mt));
    for(int i=1,j=0,pos=0;i<=n;i++,j=0,pos=0){
        memset(str,0,sizeof(str));
        str[j]=getchar();
        while(str[j]!='\n')str[++j]=getchar();
        int k=j-1;
        while(str[k]==' ')k--;
        mt[str[0]-'a'+1][str[0]-'a'+1]=1.0;
        pos++;
        while(str[pos]==' ' || str[pos]=='=')pos++;
        dfs(i,pos+1,k-1,1.0);
    }
}
int main(){
#ifdef LOCAL
    freopen("io/in","r",stdin);
    freopen("io/out","w",stdout);
#endif
    while(scanf("%d",&n)&&n){
        getchar(),init();
        ans=Gauss();
        printf("Game %d\n",cases++);
        for(int i=1;i<=n;i++){
            printf("Expected score for %c ",'a'+i-1);
            if(ans<0 ||(ans>0 && !unline[i]))printf("undefined\n");
            else printf("= %.3lf\n",x[i]);
        }
        printf("\n");//格式注意
    }
#ifdef LOCAL
    fclose(stdin);
    fclose(stdout);
#endif
    return 0;
}