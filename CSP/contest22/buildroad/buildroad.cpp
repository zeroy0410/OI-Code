#include<cstdio>
#include<string.h>
#include<algorithm>
#define LL long long
using namespace std;
int n,m,S,tt,base,inf;
LL dp[13][1<<13],cnt[13][1<<13];
int ct[1<<13],G[13][13],mx[1<<13];;
LL dfs(int x,int s){
	if(s==(1<<x))return cnt[x][s]=1,0;
	if(dp[x][s]!=-1)return dp[x][s];
	LL res=1e18;
	int tmp=s^(1<<x)^mx[s^(1<<x)];
	for(int i=tmp;;i=(i-1)&tmp){
		i|=mx[s^(1<<x)];
		for(int j=0;j<n;j++){
			if(!(i&1<<j))continue;
			if(G[x][j]==inf)continue;
			LL now=dfs(x,s^i)+dfs(j,i)+S*((s^i)!=(1<<x)||(s==base))+1LL*ct[i]*G[x][j];
			if(now<res)res=now,cnt[x][s]=cnt[x][s^i]*cnt[j][i];
			else if(now==res)cnt[x][s]+=cnt[x][s^i]*cnt[j][i];
		}
		i^=mx[s^(1<<x)];
		if(i==0)break;
	}
	return dp[x][s]=res;
}
int main(){
	scanf("%d%d%d",&n,&m,&S);base=(1<<n)-1;
	memset(dp,-1,sizeof(dp));
	memset(cnt,0,sizeof(cnt));
	for(int i=1;i<=base;i++)ct[i]=ct[i>>1]+(i&1);
	for(int i=0;i<=base;i++)
		for(int j=0;j<n;j++)
			if(i&1<<j)mx[i]=1<<j;
	memset(G,60,sizeof(G));inf=G[0][0];
	for(int i=1,a,b,c;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		a--;b--;
		G[a][b]=G[b][a]=min(G[a][b],c);
	}
	LL ans=1e18,tot=0;
	for(int i=0;i<n;i++){
		LL res=dfs(i,base);
		if(res<ans)ans=res,tot=cnt[i][base];
		else if(res==ans)tot+=cnt[i][base];
	}
	printf("%lld %lld\n",ans+S,tot);
	return 0;
}
