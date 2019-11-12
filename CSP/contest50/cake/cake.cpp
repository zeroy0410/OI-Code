#include<bits/stdc++.h>
#define M 500005
using namespace std;
int n,mp[505];
char S[15];
vector<int>A[4][4];
int G[4][4];
int zj[4],tid;
int ans=0;
bool mark[35];
int h[5],tt;
struct edge{
	int nxt,to,co,id;
}H[505];
void Add(int a,int b,int c,int d){
	H[++tt]=(edge){h[a],b,c,d};
	h[a]=tt;
}
void dfs(int x,int ds){
	ds+=zj[x];int tmp=zj[x];zj[x]=0;
	if(ds>ans)ans=ds;
	for(int i=h[x];i;i=H[i].nxt){
		int u=H[i].to,v=H[i].co,id=H[i].id;
		if(mark[id])continue;
		mark[id]=1;
		int tmp2=G[x][u];G[x][u]=G[u][x]=0;
		dfs(u,ds+tmp2+v);
		G[x][u]=G[u][x]=tmp2;
		mark[id]=0;
	}
	zj[x]=tmp;
}
int main(){
//	freopen("cake.in","r",stdin);
//	freopen("cake.out","w",stdout);
	mp['X']=0;mp['Y']=1;mp['Z']=2;mp['W']=3;
	scanf("%d",&n);
	for(int i=1,v,a,b;i<=n;i++){
		scanf("%d",&v);
		scanf("%s",S+1);a=mp[S[1]];
		scanf("%s",S+1);b=mp[S[1]];
		if(a>b)swap(a,b);
		if(a==b)zj[a]+=v;
		else A[a][b].push_back(v);
	}
	for(int i=0;i<4;i++)
		for(int j=i+1;j<4;j++){
			sort(A[i][j].begin(),A[i][j].end());
			int c=A[i][j].size();
			if(c>=2){
				if(!(c&1)){
					for(int k=2;k<c;k++){
						G[i][j]+=A[i][j][k];
						G[j][i]+=A[i][j][k];
					}
					Add(i,j,A[i][j][0],++tid);
					Add(j,i,A[i][j][0],tid);
					Add(i,j,A[i][j][1],++tid);
					Add(j,i,A[i][j][1],tid);
				}
				else {
					for(int k=1;k<c;k++){
						G[i][j]+=A[i][j][k];
						G[j][i]+=A[i][j][k];
					}
					Add(i,j,A[i][j][0],++tid);
					Add(j,i,A[i][j][0],tid);
				}
			}
			else {
				for(int k=0;k<c;k++)
					Add(i,j,A[i][j][k],++tid),
					Add(j,i,A[i][j][k],tid);
			}
		}
	for(int i=0;i<4;i++) dfs(i,0);
	printf("%d\n",ans);
	return 0;
}
