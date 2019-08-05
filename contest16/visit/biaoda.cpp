#include<bits/stdc++.h>
#define M 11
using namespace std;
const int rx[]={1,-1,0,0};
const int ry[]={0,0,1,-1};
int n,m,tot;
int A[M][M];
char mp[M][M];
int dis[M][M][1<<10|5];
struct from{
	int x,y,s;
}fr[M][M][1<<10|5];
struct Poi{
	int x,y;
};
queue<Poi>Q;
bool Min(int &x,int y){
	if(y<x)return x=y,1;
	return 0;
}
bool vis[M][M];
void spfa(int s){
	while(!Q.empty()){
		Poi v=Q.front();Q.pop();
		vis[v.x][v.y]=0;
		for(int i=0;i<4;i++){
			Poi u=v;u.x+=rx[i],u.y+=ry[i];
			if(u.x&&u.x<=n&&u.y&&u.y<=m)
				if(Min(dis[u.x][u.y][s],dis[v.x][v.y][s]+A[u.x][u.y])){
					fr[u.x][u.y][s]=(from){v.x,v.y,s};
					if(!vis[u.x][u.y]){
						Q.push((Poi){u.x,u.y});
						vis[u.x][u.y]=1;
					}
				}
		}
	}
}
void dfs(int x,int y,int s){
	if(!s)return;
	if(mp[x][y]=='_')mp[x][y]='o';
	from t=fr[x][y][s];
	dfs(t.x,t.y,t.s);
	if(x==t.x&&y==t.y)
		dfs(t.x,t.y,t.s^s);
}
int main(){
	freopen("visit.in","r",stdin);
	freopen("visit.out","w",stdout);
	memset(dis,127,sizeof(dis));
	int oo=dis[0][0][0];
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%d",&A[i][j]);
			mp[i][j]=A[i][j]?'_':'x';
			if(!A[i][j])dis[i][j][1<<(tot++)]=0;
		}
	int base=(1<<tot)-1;
	for(int S=1;S<=base;S++){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				for(int s=(S-1)&S;s;s=(s-1)&S)
					if(Min(dis[i][j][S],dis[i][j][s]+dis[i][j][S^s]-A[i][j]))
						fr[i][j][S]=(from){i,j,s};		
				if(dis[i][j][S]<oo)Q.push((Poi){i,j}),vis[i][j]=1;
			}
		spfa(S);
	}
	int sx=0,sy=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(!A[i][j]){
				sx=i,sy=j;
				break;
			}
	printf("%d\n",dis[sx][sy][base]);
	dfs(sx,sy,base);
	for(int i=1;i<=n;i++,putchar('\n'))
		for(int j=1;j<=m;j++)
			putchar(mp[i][j]);
	return 0;
}