#include<cstdio>
#include<algorithm>
#define M 1055
using namespace std;
int n,m;
int gh[M][15],pt[M][15],f[M][M],vis[15];
void dfs(int x,int y){
	for(int i=0;i<=1<<y;i++) f[x][i]=0;
	if(!y){
		for(int i=1;i<=n;i++) 
			if(vis[i])f[x][1]+=gh[x][i]; 
			else f[x][0]+=pt[x][i];
		return;
	}
	vis[y]=0,dfs(x<<1,y-1),dfs(x<<1|1,y-1);
	for(int i=0;i<=1<<(y-1);i++) 
		for(int j=0;j<=1<<(y-1);j++) 
			f[x][i+j]=max(f[x][i+j],f[x<<1][i]+f[x<<1|1][j]);
	vis[y]=1,dfs(x<<1,y-1),dfs(x<<1|1,y-1);
	for(int i=0;i<=1<<(y-1);i++) 
		for(int j=0;j<=1<<(y-1);j++)
			f[x][i+j]=max(f[x][i+j],f[x<<1][i]+f[x<<1|1][j]);
}
int main(){
	int ans=0;
	scanf("%d%d",&n,&m);n--;
	for(int i=0;i<(1<<n);i++) 
		for(int j=1;j<=n;j++)
			scanf("%d",&gh[i+(1<<n)][j]);
	for(int i=0;i<(1<<n);i++) 
		for(int j=1;j<=n;j++)
			scanf("%d",&pt[i+(1<<n)][j]);
	dfs(1,n);
	for(int i=0;i<=m;++i)ans=max(ans,f[1][i]);
	printf("%d\n",ans);
	return 0;
}
