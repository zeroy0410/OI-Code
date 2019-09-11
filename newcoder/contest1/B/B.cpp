#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
int n;
LL A[M];
struct P40{
	LL dp[1<<17][17];
	void solve(){
		for(int i=0;i<1<<n;i++)
			for(int j=0;j<n;j++)
				dp[i][j]=9e18;
		for(int i=0;i<n;i++)scanf("%lld",&A[i]);
		for(int i=0;i<n;i++)dp[1<<i][i]=0;
		for(int i=0;i<1<<n;i++){
			for(int j=0;j<n;j++){
				if(i&1<<j){
					for(int k=0;k<n;k++){
						if(i&1<<k)continue;
						dp[i|(1<<k)][k]=min(dp[i|(1<<k)][k],max(dp[i][j],(A[j]^A[k])));
					}
				}
			}
		}
		LL ans=9e18;
		for(int i=0;i<n;i++)
			ans=min(ans,dp[(1<<n)-1][i]);
		printf("%lld\n",ans);
	}
}p40;
struct P100{
	int Q[M],st,L1,R1,L2,R2,qc;
	int tmp[M],tc;
	LL ans;
	void dfs(int dep,int l1,int r1,int l2,int r2,LL res){
		if(dep<0){ans=min(res,ans);return;}
		int tl1,tr1,tl2,tr2;
		tc=l1-1;
		for(int i=l1;i<=r1;i++)
			if(A[Q[i]]&1LL<<dep)tmp[++tc]=Q[i];
		tl1=l1;tr1=tc;tl2=tc+1;
		for(int i=l1;i<=r1;i++)
			if(!(A[Q[i]]&1LL<<dep))tmp[++tc]=Q[i];
		tr2=tc;
		for(int i=l1;i<=r1;i++)Q[i]=tmp[i];
		int tll1,trr1,tll2,trr2;
		tc=l2-1;
		for(int i=l2;i<=r2;i++)
			if(A[Q[i]]&1LL<<dep)tmp[++tc]=Q[i];
		tll1=l2;trr1=tc;tll2=tc+1;
		for(int i=l2;i<=r2;i++)
			if(!(A[Q[i]]&1LL<<dep))tmp[++tc]=Q[i];
		trr2=tc;
		for(int i=l2;i<=r2;i++)Q[i]=tmp[i];
		// cout<<dep<<' '<<res<<endl;
		// for(int i=l1;i<=r1;i++)
		// 	printf("%lld ",A[Q[i]]);
		// puts("");
		// for(int i=l2;i<=r2;i++)
		// 	printf("%lld ",A[Q[i]]);
		// puts("");
		// puts("");
		bool fl=0;
		if(tl1<=tr1&&tll1<=trr1){fl=1;dfs(dep-1,tl1,tr1,tll1,trr1,res);}
		if(tl2<=tr2&&tll2<=trr2){fl=1;dfs(dep-1,tl2,tr2,tll2,trr2,res);}
		if(!fl){
			if(tl1<=tr1&&tll2<=trr2)dfs(dep-1,tl1,tr1,tll2,trr2,res+(1LL<<dep));
			if(tl2<=tr2&&tll1<=trr1)dfs(dep-1,tl2,tr2,tll1,trr1,res+(1LL<<dep));
		}
	}
	void solve(){
		qc=0;st=-1;ans=9e18;
		for(int i=1;i<=n;i++)scanf("%lld",&A[i]);
		for(int i=59;i>=0;i--){
			int res=0;
			for(int j=1;j<=n;j++)if(A[j]&1LL<<i)res++;
			if(res!=n&&res!=0){
				st=i;
				for(int j=1;j<=n;j++)
					if(A[j]&1LL<<i)Q[++qc]=j;
				L1=1;R1=qc;L2=qc+1;
				for(int j=1;j<=n;j++)
					if(!(A[j]&1LL<<i))Q[++qc]=j;
				R2=qc;
				break;
			}
		}
		if(st==-1){puts("0");return;}
		dfs(st-1,L1,R1,L2,R2,1LL<<st);
		printf("%lld\n",ans);
	}
}p100;
int main(){
	scanf("%d",&n);
	if(n<=17)p40.solve();
	else p100.solve();
	return 0;
}