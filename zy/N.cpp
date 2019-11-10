#include<stdio.h>
#include<bitset>
#include<vector>
#define M 3005
using namespace std;
int T,n,m,tot;
bitset<M>G[M],tmp;
int s[M][3];
struct P1{
	void solve(){
		tot=0;
		for(int i=1;i<=n;i++){
			for(int j=1;j<=i;j++){
				if(!G[i][j])continue;
				tmp=G[i]&G[j];
				if(tmp.count()){
					for(int q=1;q<=j;q++){
						if(tmp[q]){
							++tot;
							s[tot][0]=i;s[tot][1]=j;s[tot][2]=q;
						}
					}
				}
			}
		}
	}
}p1;
struct P2{
	bool check(int x,int y){
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				if(s[x][i]==s[y][j])
					return 1;
		return 0;
	}
	vector<int>E[M];
	int ans;
	bool mark[M];
	void dfs(int x,int c,int las){
		if(x>tot){ans=max(ans,c);return;}
		if(c+las/2<=ans)return;
		if(mark[x]){dfs(x+1,c,las);return;}
		bool fl=0;
		for(int i=0;i<E[x].size();i++){
			int u=E[x][i];
			if(mark[u])continue;
			fl=1;
			mark[u]=1;
			dfs(x+1,c+1,las-2);
			mark[u]=0;
		}
		if(!fl)dfs(x+1,c,las-1);
	}
	void solve(){
		for(int i=1;i<=tot;i++)E[i].clear();
		for(int i=1;i<=tot;i++)
			for(int j=i+1;j<=tot;j++)
				if(check(i,j))
					E[i].push_back(j);
		ans=0;
		dfs(1,0,n);
		printf("%d\n",tot-ans);
	}
}p2;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)G[i].reset();
		for(int i=1,a,b;i<=m;i++){
			scanf("%d%d",&a,&b);
			if(a<b)swap(a,b);
			G[a][b]=1;
		}
		p1.solve();
		p2.solve();
	}
	return 0;
}
