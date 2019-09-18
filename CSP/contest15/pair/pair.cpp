#include<stdio.h>
#include<algorithm>
#include<string.h>
#pragma GCC optimize(3)
#define LL long long
#define M 500005
using namespace std;
const int mod=998244353;
int T,I,ct[20],tmp[20],n;
LL Pow[M],Val[M][10],ret[M],res[M];
char L[M],R[M];
void Init(){
    Pow[0]=1;
    for(int i=1;i<M;i++)Pow[i]=Pow[i-1]*10%mod;
    for(int i=1;i<M;i++){
        if(i>1){
            for(int j=1;j<=9;j++)
                Val[i][j]=Pow[i-2]*j*(i-1)%mod;
        }
    }
}
LL solve(char *S){
    n=strlen(S+1);LL ans=0;
    for(int i=1;i<=n;i++)S[i]-='0';
    memset(ct,0,sizeof(ct));
    res[0]=ret[n+1]=0;
    for(int i=1;i<=n;i++)res[i]=(res[i-1]*10+S[i])%mod;
    for(int i=n;i>=1;i--)ret[i]=(ret[i+1]+1LL*S[i]*Pow[n-i]%mod)%mod;
    for(int i=1;i<=n;i++){
        for(int j=0;j<=9;j++){
            ans=(ans+res[i-1]*Val[n-i+1][j]%mod)%mod;
            if(j<S[i])ans=(ans+Val[n-i+1][j])%mod;
        }tmp[10]=0;
        for(int j=9;j>=1;j--)tmp[j]=tmp[j+1]+ct[j];
        for(int j=0;j<S[i];j++)
            ans=(ans+tmp[j+1]*Pow[n-i]%mod)%mod;
        ans=(ans+tmp[S[i]+1]*(ret[i+1]+1)%mod)%mod;
        ct[S[i]]++;
        if(i<n){
            for(int k=0;k<=9;k++)
                ans=(ans+Val[n-i][k]*ct[k]*S[i+1])%mod;
        }
    }
    return ans;
}
int main(){
    Init();
    scanf("%d%d",&T,&I);
    while(T--){
        scanf("%s%s",L+1,R+1);
        int len=strlen(L+1);
        LL l=solve(L);
        LL r=solve(R);
        LL ans=((r-l)%mod+mod)%mod;
        memset(ct,0,sizeof(ct));
        for(int i=1;i<=len;i++){
            for(int j=L[i]+1;j<=9;j++)
                ans=(ans+ct[j])%mod;
            ct[L[i]]++;
        }
        printf("%lld\n",ans);
    }
    return 0;
}
