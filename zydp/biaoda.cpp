#include<bits/stdc++.h>
#define ll long long 
using namespace std;
const int N=4098,M=20,K=100006;
const ll mod=1e9+1;
int n,p,flag[N],book[K],num[M],f[M][N];
ll ans=1,sum;
void build(int x){
    p=1,sum=0;memset(f,0,sizeof(f));memset(num,0,sizeof(num));
    for(int i=x;i<=n;i<<=1,++p)for(int j=i;j<=n;j*=3)++num[p],book[j]=1;
    for(int i=0;i<(1<<num[1]);++i)f[1][i]=flag[i];
    for(int i=2;i<p;++i)
        for(int j=0;j<(1<<num[i-1]);++j)
            for(int k=0;k<(1<<num[i]);++k)
                if(flag[j]&&flag[k]&&!(j&k))f[i][k]=(f[i][k]+f[i-1][j])%mod;
    for(int i=0;i<(1<<num[p-1]);++i)sum=(sum+f[p-1][i])%mod;
    ans=ans*sum%mod;
}
int main(){
	scanf("%d",&n);
    for(int i=0;i<=2048;++i)flag[i]=((i<<1)&i)?0:1;
    for(int i=1;i<=n;++i)if(!book[i])build(i);
    printf("%lld\n",ans);
    return 0;
}
