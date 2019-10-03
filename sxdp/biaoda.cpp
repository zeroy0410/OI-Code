#include<bits/stdc++.h>
#define int long long
using namespace std;
const int MOD=1000000007;
int n,K,rt,head,tail,A[1010],ch[1010][2],Q[1010],dp[1010][1010],size[1010],frac[1001000],inv[1001000],infr[1001000];
int Quick_Pow(int a,int p){
    int res=1;
    while(p){
        if(p&1)res=res*a%MOD;
        a=a*a%MOD;
        p>>=1;
    }
    return res;
}
int C(int x,int y){
    if(x<y)return 0;
    return frac[x]*infr[y]%MOD*infr[x-y]%MOD;
}
void DFS(int x,int fa){
    dp[x][0]=1;
    size[x]=1;
    for(int i=0;i<=1;i++){
        int t=ch[x][i];
        if(t==0)continue;
        DFS(t,x);
        for(int i=min(K,size[x]);i>=0;i--){
            for(int j=min(K,size[t]);j>=1;j--){
                if(i+j>K)continue;
                if(i+j==0)continue;
                dp[x][i+j]=(dp[x][i+j]+dp[x][i]*dp[t][j]%MOD)%MOD;
            }
        }
        size[x]+=size[t];
    }
    int cha=A[x]-A[fa];
    for(int i=min(size[x],K);i>=0;i--){
        for(int j=size[x]-i;j>=1;j--){
            if(i+j>K)continue;
            if(i+j==0)continue;
            dp[x][i+j]=(dp[x][i+j]+dp[x][i]*C(size[x]-i,j)%MOD*C(cha,j)%MOD*frac[j]%MOD)%MOD;
        }
    }
}
void init(){
    frac[0]=infr[0]=1;
    for(int i=1;i<=1000010;i++)inv[i]=Quick_Pow(i,MOD-2);
    for(int i=1;i<=1000010;i++)frac[i]=frac[i-1]*i%MOD,infr[i]=infr[i-1]*inv[i]%MOD;
}
signed main() {
    init();
    scanf("%lld %lld",&n,&K);
    rt=1,head=1,tail=0;
    for(int i=1; i<=n; i++)scanf("%lld",&A[i]);
    for(int i=1; i<=n; i++) {
        int res=-1;
        while(head<=tail&&A[i]<=A[Q[tail]])res=Q[tail--];
        if(res!=-1) {
            if(rt==res)rt=i;
            ch[i][0]=res;
        }
        if(head<=tail)ch[Q[tail]][1]=i;
        Q[++tail]=i;
    }
    DFS(rt,0);
    printf("%lld\n",dp[rt][K]);
    return 0;
}
