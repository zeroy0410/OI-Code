#include<bits/stdc++.h>
#define M 500006
#pragma GCC optimize(2)
#define mo 998244353
using namespace std;
int T,id,Pow[M],dp[M][11],sum[M],mem[12],num[M];
char A[M];
int Deal(){
    memset(mem,0,sizeof(mem));
    int ans=0;
    int n=strlen(A+1);
    num[n+1]=1;
    for(int i=n;i>=1;i--)num[i]=(num[i+1]+1ll*Pow[n-i]*(A[i]-'0'))%mo;
    for(int i=1;i<=n;i++){
        for(int j=0;j<10;j++){
            ans=(1ll*dp[n-i+1][j]*mem[j]*(A[i]-'0')+1ll*Pow[n-i]*min(A[i]-'0',j)*mem[j]+ans)%mo;
            if(j>A[i]-'0')ans=(1ll*num[i+1]*mem[j]+ans)%mo;
            else if(j<A[i]-'0')ans=(0ll+dp[n-i+1][j]+sum[n-i]+ans)%mo;
        }
        mem[A[i]-'0']++;
    }
    return ans;
}
struct ll {
    void Solve_100(){
        while(T--){
            scanf("%s",A+1);
            int now=strlen(A+1);
            A[now]--;
            while(A[now]<'0'&&now>0){
                A[now-1]--;
                A[now]+=10;
                now--;
            }
            int ans=0;
            if(now>0)ans=-Deal();
            scanf("%s",A+1);
            ans+=Deal();
            printf("%d\n",(ans+mo)%mo);
        }
    }
} ans;
int main() {
    scanf("%d%d",&T,&id);
    Pow[0]=1;
    for(int i=1;i<=M-6;i++)Pow[i]=1ll*Pow[i-1]*10%mo;
    for(int i=2;i<=M-6;i++){
        sum[i]=10ll*sum[i-1]%mo;
        for(int j=0;j<10;j++){
            dp[i][j]=(1ll*dp[i-1][j]*10+1ll*Pow[i-2]*j)%mo;
            sum[i]+=dp[i][j];
            sum[i]=sum[i]>=mo?sum[i]-mo:sum[i];
        }
    }
    ans.Solve_100();
    return 0;
}
