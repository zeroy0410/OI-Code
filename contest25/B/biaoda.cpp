#include<bits/stdc++.h>
#define FOR(i,x,y) for(int i=(x),i##END=(y);i<=i##END;++i)
#define DOR(i,x,y) for(int i=(x),i##END=(y);i>=i##END;--i)
template<typename T,typename _T>inline bool chk_min(T &x,const _T y){return y<x?x=y,1:0;}
template<typename T,typename _T>inline bool chk_max(T &x,const _T y){return x<y?x=y,1:0;}
typedef long long ll;
const int dx[4]={0,-1,0,1};
const int dy[4]={1,0,-1,0};
const int N=1005;
template<const int N,const int M,typename T>struct LinkedList
{
	int head[N],nxt[M],tot;T to[M];
	LinkedList(){clear();}
	T &operator [](const int x){return to[x];}
	void clear(){memset(head,-1,sizeof(head)),tot=0;}
	void add(int u,T v){to[tot]=v,nxt[tot]=head[u],head[u]=tot++;}
	#define EOR(i,G,u) for(int i=G.head[u];~i;i=G.nxt[i])
};
struct edge{int to,cost;};
LinkedList<N*12,N*12*4,edge>G;
int X1[N],Y1[N],X2[N],Y2[N];
int hs[N*2][N*2];
bool proh[N*2][N*2][4];
int discX[N*2],X;
int discY[N*2],Y;
int sx,sy,tx,ty;
int n,tot;

struct node
{
	int at,path;
	bool operator <(const node &_)const{return path>_.path;}
};
int dis[N*12];
std::priority_queue<node>Q;
int dijkstra(int s,int t)
{
	printf("tot=%d\n",tot);
	FOR(i,1,tot)dis[i]=1e9;
	dis[s]=0;
	while(!Q.empty())Q.pop();
	Q.push((node){s,0});
	while(!Q.empty())
	{
		node now=Q.top();Q.pop();
		int u=now.at;
		if(now.path>dis[u])continue;
		EOR(i,G,u)
		{
			int v=G[i].to,w=G[i].cost;
			if(chk_min(dis[v],dis[u]+w))
				Q.push((node){v,dis[v]});
		}
	}
	return dis[t];
}

void _seek(int x,int y,int d,int sx,int sy)
{
	if(x<1||x>X||y<1||y>Y)return;
	if(hs[x][y]==-1)_seek(x+dx[d],y+dy[d],d,sx,sy);
	else if(!hs[x][y])hs[x][y]=++tot;
}
void seek(int sx,int sy,int d)	//寻找第一个不是-1的点，是0则给其标号
{
	_seek(sx+dx[d],sy+dy[d],d,sx,sy);
}

int get_dis(int X1,int Y1,int X2,int Y2)
{
	return std::abs(discX[X1]-discX[X2])+std::abs(discY[Y1]-discY[Y2]);
}
void _reseek(int x,int y,int d,int sx,int sy)
{
	if(x<1||x>X||y<1||y>Y)return;
	if(hs[x][y]>0)G.add(hs[sx][sy],(edge){hs[x][y],get_dis(sx,sy,x,y)});
	else _reseek(x+dx[d],y+dy[d],d,sx,sy);
}
void reseek(int sx,int sy,int d)	//寻找第一个大于零的点，并向其连边
{
	_reseek(sx+dx[d],sy+dy[d],d,sx,sy);
}

int main()
{
	// freopen("14.in","r",stdin);
	//freopen("path.out","w",stdout);
	int T;
	scanf("%d",&T);
	while(T--)
	{
		G.clear();
		scanf("%d%d%d%d%d",&sx,&sy,&tx,&ty,&n);
		FOR(i,1,n)
		{
			scanf("%d%d%d%d",&X1[i],&Y1[i],&X2[i],&Y2[i]);
			if(X1[i]>X2[i])std::swap(X1[i],X2[i]);
			if(Y1[i]>Y2[i])std::swap(Y1[i],Y2[i]);
		}

		X=0;
		discX[++X]=sx,discX[++X]=tx;
		FOR(i,1,n)discX[++X]=X1[i],discX[++X]=X2[i];
		std::sort(discX+1,discX+1+X);
		X=std::unique(discX+1,discX+1+X)-discX-1;
		sx=std::lower_bound(discX+1,discX+1+X,sx)-discX;
		tx=std::lower_bound(discX+1,discX+1+X,tx)-discX;
		FOR(i,1,n)
		{
			X1[i]=std::lower_bound(discX+1,discX+1+X,X1[i])-discX;
			X2[i]=std::lower_bound(discX+1,discX+1+X,X2[i])-discX;
		}

		Y=0;
		discY[++Y]=sy,discY[++Y]=ty;
		FOR(i,1,n)discY[++Y]=Y1[i],discY[++Y]=Y2[i];
		std::sort(discY+1,discY+1+Y);
		Y=std::unique(discY+1,discY+1+Y)-discY-1;
		sy=std::lower_bound(discY+1,discY+1+Y,sy)-discY;
		ty=std::lower_bound(discY+1,discY+1+Y,ty)-discY;
		FOR(i,1,n)
		{
			Y1[i]=std::lower_bound(discY+1,discY+1+Y,Y1[i])-discY;
			Y2[i]=std::lower_bound(discY+1,discY+1+Y,Y2[i])-discY;
		}

		FOR(i,1,X)FOR(j,1,Y)
		{
			hs[i][j]=-1;
			FOR(d,0,3)proh[i][j][d]=0;
		}
		tot=0;
		hs[sx][sy]=++tot,hs[tx][ty]=++tot;
		FOR(i,1,n)
		{
			FOR(x,X1[i],X2[i])FOR(y,Y1[i],Y2[i])if(hs[x][y]==-1)hs[x][y]=0;
			if(!hs[X1[i]][Y1[i]])hs[X1[i]][Y1[i]]=++tot;
			if(!hs[X1[i]][Y2[i]])hs[X1[i]][Y2[i]]=++tot;
			if(!hs[X2[i]][Y1[i]])hs[X2[i]][Y1[i]]=++tot;
			if(!hs[X2[i]][Y2[i]])hs[X2[i]][Y2[i]]=++tot;
			FOR(x,X1[i]+1,X2[i]-1)proh[x][Y1[i]][0]=1,proh[x][Y2[i]][2]=1;
			FOR(y,Y1[i]+1,Y2[i]-1)proh[X1[i]][y][3]=1,proh[X2[i]][y][1]=1;
		}

		FOR(d,0,3)if(!proh[sx][sy][d])seek(sx,sy,d);
		FOR(d,0,3)if(!proh[tx][ty][d])seek(tx,ty,d);
		FOR(i,1,n)
		{
			seek(X1[i],Y1[i],1),seek(X1[i],Y1[i],2);
			seek(X1[i],Y2[i],0),seek(X1[i],Y2[i],1);
			seek(X2[i],Y1[i],2),seek(X2[i],Y1[i],3);
			seek(X2[i],Y2[i],0),seek(X2[i],Y2[i],3);
		}

		FOR(x,1,X)FOR(y,1,Y)if(hs[x][y])
		{
			FOR(d,0,3)if(!proh[x][y][d])
				reseek(x,y,d);
		}

		int res=dijkstra(1,2);
		if(res>=1e8)puts("No Path");
		else printf("%d\n",res);
	}
	return 0;
}
