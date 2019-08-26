#include<bits/stdc++.h>
#define M 200005
#define LL long long
using namespace std;
const int mod=998244353;
int n,K,m,A[M];
struct P0{
    LL dp[M][2];
    LL calc(int l,int r,bool f){
        if(r==l+1)return 1;
        if(A[l]!=A[r])dp[l+1][0]=K-2,dp[l+1][1]=1;
        else dp[l+1][0]=K-1,dp[l+1][1]=0;
		if(A[l]==0&&A[r]==0)dp[l+1][0]++;
        for(int i=l+2;i<r;i++){
            dp[i][0]=(dp[i-1][0]*(K-2)%mod+dp[i-1][1]*(K-1)%mod)%mod;
            dp[i][1]=dp[i-1][0];
        }
        if(!f)return dp[r-1][0];
        return (dp[r-1][0]+dp[r-1][1])%mod;
    }
    LL solve(){
        for(int i=2;i<=n;i++)
            if(A[i]==A[i-1]&&A[i]!=0){
                return 0;
            }
        LL ans=1;
        int st=0;
        for(int i=1;i<=n;i++)
            if(A[i]!=0){st=i;break;}
        if(st>1){
            dp[1][0]=K-1;dp[1][1]=1;
            for(int i=2;i<st;i++){
                dp[i][0]=(dp[i-1][0]*(K-2)%mod+dp[i-1][1]*(K-1)%mod)%mod;
                dp[i][1]=dp[i-1][0];
            }
            ans=ans*dp[st-1][0]%mod;
        }
        int las=st;
        for(int i=st+1;i<=n;i++){
            if(A[i]!=0){
                ans=ans*calc(las,i,0)%mod;
                las=i;
            }
        }
        if(las<n)ans=ans*calc(las,n+1,1)%mod;
		return ans;
    }
}p0;
struct P1{
	int tmp[M];
	void solve(){
		int tn=n,i,j;
		for(i=1;i<=n;i++)tmp[i]=A[i];
		for(i=1,j=1;i<=tn;i+=2,j++)A[j]=tmp[i];
		n=j-1;
		LL ans=p0.solve();
		for(i=2,j=1;i<=tn;i+=2,j++)A[j]=tmp[i];
		n=j-1;
		A[0]=A[n+1]=0;
		ans=ans*p0.solve()%mod;
		printf("%lld\n",ans);
	}
}p1;
int main(){
    scanf("%d%d%d",&n,&K,&m);
    for(int i=1;i<=n;i++)
        scanf("%d",&A[i]);
    if(m==0)printf("%lld\n",p0.solve());
	else p1.solve();
    return 0;
}
