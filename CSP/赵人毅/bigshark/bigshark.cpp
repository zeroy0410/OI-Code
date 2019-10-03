#include<bits/stdc++.h>
#define M 20035
#define LL long long
using namespace std;
const int P=1e9;
struct Bignum{
	LL a[1005];
	int len;
	Bignum(){
		memset(a,0,sizeof(a));
		len=1;
	}
	Bignum operator * (Bignum res){
		Bignum ans;
		for(int i=0;i<len;i++)
			for(int j=0;j<res.len;j++){
				ans.a[i+j]+=a[i]*res.a[j];
				if(ans.a[i+j]>=P){
					ans.a[i+j+1]+=ans.a[i+j]/P;
					ans.a[i+j]%=P;
				}
			}
		ans.len=len+res.len;
		if(ans.a[ans.len])ans.len++;
		return ans;
	}
	Bignum operator + (Bignum res){
		Bignum ans;
		ans.len=max(len,res.len);
		for(int i=0;i<ans.len;i++){
			ans.a[i]+=a[i]+res.a[i];
			if(ans.a[i]>=P){
				ans.a[i+1]+=ans.a[i]/P;
				ans.a[i]%=P;
			}
		}
		if(ans.a[ans.len])ans.len++;
		return ans;
	}
	Bignum operator - (Bignum res){
		Bignum ans;
		ans.len=len;
		for(int i=0;i<len;i++)ans.a[i]=a[i];
		for(int i=0;i<res.len;i++){
			if(ans.a[i]<res.a[i])ans.a[i]+=P,ans.a[i+1]--;
			ans.a[i]-=res.a[i];
		}
		while(ans.len&&ans.a[ans.len-1]==0)ans.len--;
		if(ans.len==0)ans.len=1;
		return ans;
	}
	bool operator < (Bignum res)const{
		int len=max(res.len,len);
		for(int i=len-1;i>=0;i--){
			if(a[i]<res.a[i])return 1;
			if(a[i]>res.a[i])return 0;
		}
		return 0;
	}
}dp[M],ans,kk,sz[M],p;
int n,K,h[M],tt,rt;
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
void dfs(int x,int f){
	sz[x].a[0]=1;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x);
		dp[x]=dp[x]+(dp[u]+sz[u])*kk;
		sz[x].a[0]+=sz[u].a[0];
	}
}
void redfs(int x,int f){
	if(f){
		p.a[0]=n-sz[x].a[0];
		dp[x]=dp[x]+(dp[f]+p-(dp[x]+sz[x])*kk)*kk;
		sz[x].a[0]=n;
	}
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		redfs(u,x);
	}
}
int main(){
	scanf("%d%d",&n,&K);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
	}kk.a[0]=K;
	dfs(1,0);redfs(1,0);ans=dp[1];rt=1;
	for(int i=2;i<=n;i++)if(dp[i]<ans)ans=dp[i],rt=i;
	printf("%d\n",rt);
	return 0;
}
