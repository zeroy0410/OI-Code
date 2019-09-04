#include<bits/stdc++.h>
#define M 35
using namespace std;
int dxy[4][2]={1,0,0,1,-1,0,0,-1};
const double eps=1e-6;
int n,m,K,H,sx,sy,P[M],base;
char mp[M][M];
struct node{int x,y;};
vector<node>wk[M][M][M];
bool ca[M][M][M];
bool vis[M][M];
double po[M*M][5];
void dfs1(int x,int y,int a,int b,int st){
	vis[x][y]=1;
	for(int i=0;i<4;i++){
		int nx=x+dxy[i][0];
		int ny=y+dxy[i][1];
		if(nx<1||nx>n||ny<1||ny>m||vis[nx][ny])continue;
		if(mp[a][b]=='@')ca[nx][ny][st]=1;
		if(mp[nx][ny]<5){
			int c=mp[nx][ny];
			if(!(st&1<<c)){
				wk[a][b][st].push_back((node){nx,ny});
				continue;
			}
		}
		dfs1(nx,ny,a,b,st);
	}
}
void Init(){
	for(int i=0;i<=base;i++){
		memset(vis,0,sizeof(vis));
		for(int x=1;x<=n;x++)
			for(int y=1;y<=m;y++)
				if(mp[x][y]=='@')
					dfs1(x,y,x,y,i);
	}
	for(int i=0,ed=(1<<(K<<1))-1;i<=ed;i++){
		bool f=1;
		int s1=0,s2=0;
		for(int j=0;f&&j<K;j++){
			int t=(i>>(j*2))&3;
			if(t==3){f=0;break;}
			if(t){
				s1|=(t-1)<<j;
				s2|=1<<j;
			}
		}
		if(!f)continue;
		int t=base^s2;
		for(int j=0;j<K;j++){
			int sum=0,p=0;
			for(int s=t;;s=(s-1)&t){
				sum+=P[s^s1];
				if((s^s1)&(1<<j))p+=P[s^s1];
				if(s==0)break;
			}
			po[i][j]=p*1.0/sum;
		}
	}
}
bool mark[M][M][M*M][6];
double dp[M][M][M*M][6];
double dfs(int x,int y,int S,int ss,int hp){
	if(hp<=0)return 0;
	if(mp[x][y]=='@'||ca[x][y][ss])return 1;
	if(mark[x][y][S][hp])return dp[x][y][S][hp];
	mark[x][y][S][hp]=1;
	double ans=0;
	if(wk[x][y][ss].empty()){
		memset(vis,0,sizeof(vis));
		dfs1(x,y,x,y,ss);
	}
	for(int i=0;i<wk[x][y][ss].size();i++){
		int xx=wk[x][y][ss][i].x;
		int yy=wk[x][y][ss][i].y;
		int c=mp[xx][yy];
		double p=po[S][c],res;
		if(p>  eps)res+=p    *dfs(xx,yy,S|(2<<(c<<1)),ss,hp-1);
        if(p<1-eps)res+=(1-p)*dfs(xx,yy,S|(1<<(c<<1)),ss|(1<<c),hp);
        ans=max(ans,res);
	}
	return dp[x][y][S][hp]=ans;
}
int main(){
	scanf("%d%d%d%d",&n,&m,&K,&H);
	base=(1<<K)-1;
	for(int i=1;i<=n;i++){
		scanf("%s",mp[i]+1);
		for(int j=1;j<=m;j++){
			if(mp[i][j]>='A'&&mp[i][j]<='Z')mp[i][j]-='A';
			if(mp[i][j]=='$')sx=i,sy=j;
		}
	}
	for(int i=0;i<=base;i++)scanf("%d",&P[i]);
	Init();
	printf("%.3lf\n",dfs(sx,sy,0,0,H));
	return 0;
}
