#include<bits/stdc++.h>
using namespace std;
int dp[15][15][1<<10];
int n,m,A[15][15],tt,inf;
char mp[15][15];
struct node{int x,y,s;}fr[15][15][1<<10];
queue<node>Q;
bool vis[15][15];
int dxy[4][2]={1,0,0,1,-1,0,0,-1};
void Spfa(int S){
	while(!Q.empty()){
		node e=Q.front();Q.pop();vis[e.x][e.y]=0;
		for(int i=0;i<4;i++){
			int x=e.x+dxy[i][0];
			int y=e.y+dxy[i][1];
			if(x>=1&&x<=n&&y>=1&&y<=m)
				if(dp[x][y][S]>dp[e.x][e.y][S]+A[x][y]){
					dp[x][y][S]=dp[e.x][e.y][S]+A[x][y];
					fr[x][y][S]=(node){e.x,e.y,S};
					if(!vis[x][y]){
						Q.push((node){x,y});
						vis[x][y]=1;
					}
				}
		}
	}
}
void dfs(int x,int y,int S){
	if(!S)return;
	if(mp[x][y]=='_')mp[x][y]='o';
	node nxt=fr[x][y][S];
	dfs(nxt.x,nxt.y,nxt.s);
	if(nxt.x==x&&nxt.y==y)
		dfs(nxt.x,nxt.y,S^nxt.s);
}
int main(){
	freopen("visit.in","r",stdin);
	freopen("visit.out","w",stdout);
	scanf("%d%d",&n,&m);
	memset(dp,60,sizeof(dp));inf=dp[0][0][0];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%d",&A[i][j]);
			mp[i][j]=A[i][j]?'_':'x';
			if(!A[i][j]){dp[i][j][1<<tt]=0;tt++;}
		}
	for(int S=1;S<1<<tt;S++){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				for(int s=(S-1)&S;s;s=(s-1)&S){
					if(dp[i][j][S]>dp[i][j][s]+dp[i][j][S^s]-A[i][j]){
						dp[i][j][S]=dp[i][j][s]+dp[i][j][S^s]-A[i][j];
						fr[i][j][S]=(node){i,j,s};
					}
				}
				if(dp[i][j][S]<inf)Q.push((node){i,j}),vis[i][j]=1;
			}
		Spfa(S);
	}
	int sx,sy;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!A[i][j]){sx=i;sy=j;break;}
	printf("%d\n",dp[sx][sy][(1<<tt)-1]);
	dfs(sx,sy,(1<<tt)-1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++)
			printf("%c",mp[i][j]);
		putchar('\n');
	}
	return 0;
}
