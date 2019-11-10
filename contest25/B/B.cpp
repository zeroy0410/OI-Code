#include<bits/stdc++.h>
#define M 1005
#define LL long long
using namespace std;
bool mm1;
int n,T,sx,sy,ex,ey,h[M*M*4],tt;
struct edge{
	int nxt,to,co;
}G[M*M*4];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
struct node{int x1,y1,x2,y2;}A[M];
int B1[M<<1],B2[M<<1],c1,c2;
int mp[2][M<<1][M<<1];
int id[M<<1][M<<1];
bool mark[M<<1][M<<1];
int tot;
LL dis[M*M*4],inf;
bool vis[M*M*4];
queue<int>Q;
bool mm2;
LL SPFA(){
	while(!Q.empty())Q.pop();
	Q.push(id[sx][sy]);vis[id[sx][sy]]=1;
	memset(dis,0x3f,sizeof(dis));inf=dis[0];dis[id[sx][sy]]=0;
	while(!Q.empty()){
		int x=Q.front();Q.pop();vis[x]=0;
		for(int i=h[x];i;i=G[i].nxt){
			int u=G[i].to,c=G[i].co;
			if(dis[u]>dis[x]+c){
				dis[u]=dis[x]+c;
				if(!vis[u]){
					vis[u]=1;
					Q.push(u);
				}
			}
		}
	}
	return dis[id[ex][ey]];
}
void New(int x,int y){
	if(!mark[x][y]){
		id[x][y]=++tot;
		mark[x][y]=1;
	}
}
int main(){
	freopen("path.in","r",stdin);
	freopen("path.out","w",stdout);
	// printf("%lf\n",(&mm2-&mm1)/1024.0/1024);
	scanf("%d",&T);
	while(T--){
		tot=0;
		memset(h,0,sizeof(h));tt=0;
		memset(mark,0,sizeof(mark));
		memset(mp,0,sizeof(mp));c1=c2=0;
		scanf("%d%d%d%d",&sx,&sy,&ex,&ey);
		B1[++c1]=sx;B1[++c1]=ex;
		B2[++c2]=sy;B2[++c2]=ey;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%d%d%d%d",&A[i].x1,&A[i].y1,&A[i].x2,&A[i].y2);
			if(A[i].x1>A[i].x2)swap(A[i].x1,A[i].x2);
			if(A[i].y1>A[i].y2)swap(A[i].y1,A[i].y2);
			B1[++c1]=A[i].x1;B1[++c1]=A[i].x2;
			B2[++c2]=A[i].y2;B2[++c2]=A[i].y1;
		}
		sort(B1+1,B1+c1+1);sort(B2+1,B2+c2+1);
		c1=unique(B1+1,B1+c1+1)-B1-1;
		c2=unique(B2+1,B2+c2+1)-B2-1;
		sx=lower_bound(B1+1,B1+c1+1,sx)-B1;
		sy=lower_bound(B2+1,B2+c2+1,sy)-B2;
		ex=lower_bound(B1+1,B1+c1+1,ex)-B1;
		ey=lower_bound(B2+1,B2+c2+1,ey)-B2;
		New(sx,sy);New(ex,ey);
		for(int i=1;i<=n;i++){
			A[i].x1=lower_bound(B1+1,B1+c1+1,A[i].x1)-B1;
			A[i].y1=lower_bound(B2+1,B2+c2+1,A[i].y1)-B2;
			A[i].x2=lower_bound(B1+1,B1+c1+1,A[i].x2)-B1;
			A[i].y2=lower_bound(B2+1,B2+c2+1,A[i].y2)-B2;
			for(int j=A[i].x1;j<=A[i].x2;j++){
				mp[0][j][A[i].y1]=i,mp[0][j][A[i].y2]=-i;
				New(j,A[i].y1);New(j,A[i].y2);
				if(j>A[i].x1){
					Add(id[j][A[i].y1],id[j-1][A[i].y1],B1[j]-B1[j-1]);
					Add(id[j-1][A[i].y1],id[j][A[i].y1],B1[j]-B1[j-1]);
					Add(id[j][A[i].y2],id[j-1][A[i].y2],B1[j]-B1[j-1]);
					Add(id[j-1][A[i].y2],id[j][A[i].y2],B1[j]-B1[j-1]);
				}
			}
			for(int j=A[i].y1;j<=A[i].y2;j++){
				mp[1][A[i].x1][j]=i,mp[1][A[i].x2][j]=-i;
				New(A[i].x1,j);New(A[i].x2,j);
				if(j>A[i].y1){
					Add(id[A[i].x1][j],id[A[i].x1][j-1],B2[j]-B2[j-1]);
					Add(id[A[i].x1][j-1],id[A[i].x1][j],B2[j]-B2[j-1]);
					Add(id[A[i].x2][j],id[A[i].x2][j-1],B2[j]-B2[j-1]);
					Add(id[A[i].x2][j-1],id[A[i].x2][j],B2[j]-B2[j-1]);
				}
			}
		}
		int las=0;
		for(int i=1;i<=c1;i++){
			las=0;
			for(int j=1;j<=c2;j++){
				if(mp[0][i][j]>0){
					if(las!=0){
						Add(id[i][las],id[i][j],B2[j]-B2[las]);
						Add(id[i][j],id[i][las],B2[j]-B2[las]);
					}
				}
				if((i==sx&&j==sy)||(i==ex&&j==ey)){
					if(las!=0){
						Add(id[i][las],id[i][j],B2[j]-B2[las]);
						Add(id[i][j],id[i][las],B2[j]-B2[las]);
					}
					las=j;
				}
				if(mp[0][i][j]<0)las=j;
			}
		}
		for(int j=1;j<=c2;j++){
			las=0;
			for(int i=1;i<=c1;i++){
				if(mp[1][i][j]>0){
					if(las!=0){
						Add(id[las][j],id[i][j],B1[i]-B1[las]);
						Add(id[i][j],id[las][j],B1[i]-B1[las]);
					}
				}
				if((i==sx&&j==sy)||(i==ex&&j==ey)){
					if(las!=0){
						Add(id[las][j],id[i][j],B1[i]-B1[las]);
						Add(id[i][j],id[las][j],B1[i]-B1[las]);
					}
					las=i;
				}
				if(mp[1][i][j]<0)las=i;
			}
		}
		LL ans=SPFA();
		if(ans==inf)printf("No Path\n");
		else printf("%lld\n",ans);
	}
	return 0;
}
