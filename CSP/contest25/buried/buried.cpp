#include<bits/stdc++.h>
#define M 505
using namespace std;
const int mod=998244353;
int n,K,A[M],dfn[M],tot,fa[M];
vector<int>G[M];
bool cmp(int a,int b){
	return dfn[a]<dfn[b];
}
int wk[1000005];
bool mark[1000005];
struct P20{
	int Q[M],qcnt,ans;
	void solve(){
		ans=0;
		for(int i=1;i<1<<n;i++){
			qcnt=0;
			for(int j=0;j<n;j++)
				if(i&1<<j)Q[++qcnt]=j+1;
			bool fl=1;
			for(int j=1;j<=qcnt;j++){
				if(Q[j]!=1&&!(i&1<<(fa[Q[j]]-1))){
					fl=0;
					break;
				}
			}
			if(!fl)continue;
			sort(Q+1,Q+qcnt+1,cmp);
			int res=0;
			for(int i=1;i<=qcnt;i++)
				res=res*10+A[Q[i]];
			if(mark[res])ans++;
		}
		printf("%d\n",ans);
	}
}p20;
void dfs(int x,int f){
	dfn[x]=++tot;fa[x]=f;
	for(int i=0;i<G[x].size();i++){
		int u=G[x][i];
		if(u==f)continue;
		dfs(u,x);
	}
}
int get(int x){
	int res=0;
	while(x){
		res=max(res,x%K);
		x/=K;
	}
	return res;
}
int main(){
	freopen("buried.in","r",stdin);
	freopen("buried.out","w",stdout);
	scanf("%d%d",&n,&K);
	wk[1]=1;mark[1]=1;
	for(int i=2;i<=1000000;i++){
		wk[i]=wk[i-1]+get(wk[i-1]);
		if(wk[i]<1000000)mark[wk[i]]=1;
	}
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1,a,b;i<n;i++){
		scanf("%d%d",&a,&b);
		G[a].push_back(b);
		G[b].push_back(a);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)sort(G[i].begin(),G[i].end());
	p20.solve();
	return 0;
}
