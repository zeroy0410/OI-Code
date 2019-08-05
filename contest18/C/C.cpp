#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
const int inf=1061109567;
int n,q;
int A[8][M];
int dxy[4][2]={1,0,0,1,-1,0,0,-1};
struct P50{
	struct node{
		int x,y;LL ds;
		bool operator < (const node& res)const{
			return ds>res.ds;	
		}
	};
	priority_queue<node>Q;
	LL dis[8][M];
	bool vis[8][M];
	LL Dij(int sx,int sy,int ex,int ey){
		while(!Q.empty())Q.pop();
		for(int i=1;i<=6;i++)
			for(int j=1;j<=n;j++)
				dis[i][j]=1e18,vis[i][j]=0;
		dis[sx][sy]=A[sx][sy];
		Q.push((node){sx,sy,A[sx][sy]});
		while(!Q.empty()){
			node e=Q.top();Q.pop();	
			if(vis[e.x][e.y])continue;
			vis[e.x][e.y]=1;
			if(e.x==ex&&e.y==ey)return e.ds;
			for(int i=0;i<4;i++){
				int nx=e.x+dxy[i][0];
				int ny=e.y+dxy[i][1];
				if(nx>=1&&nx<=6&&ny>=1&&ny<=n&&dis[nx][ny]>e.ds+A[nx][ny]){
					dis[nx][ny]=e.ds+A[nx][ny];
					Q.push((node){nx,ny,dis[nx][ny]});
				}
			}
		}
	}
	void solve(){
		scanf("%d",&q);
		while(q--){
			int op,x,y,x1,y1,c;
			scanf("%d",&op);
			if(op==1){
				scanf("%d%d%d",&x,&y,&c);
				A[x][y]=c;
			}
			else {
				scanf("%d%d%d%d",&x,&y,&x1,&y1);
				printf("%lld\n",Dij(x,y,x1,y1));	
			}
		}
	}
}p50;
struct Pshui{
	struct node{int x,y;};
	node Q[8*M];
	int l,r;
	LL dis[8][M];
	bool vis[8][M];
	LL SPFA(int sx,int sy,int ex,int ey){
		for(int i=1;i<=6;i++)
			for(int j=1;j<=n;j++)
				dis[i][j]=1e18,vis[i][j]=0;
		dis[sx][sy]=A[sx][sy];
		l=1;r=1;
		Q[r++]=(node){sx,sy};
		while(l!=r){
			int x=Q[l].x,y=Q[l++].y;vis[x][y]=0;if(l==6*n+1)l=0;
			for(int i=0;i<4;i++){
				int nx=x+dxy[i][0];
				int ny=y+dxy[i][1];
				if(nx>=1&&nx<=6&&ny>=1&&ny<=n&&dis[nx][ny]>dis[x][y]+A[nx][ny]){
					dis[nx][ny]=dis[x][y]+A[nx][ny];
					if(!vis[nx][ny]){
						Q[r++]=(node){nx,ny};
						vis[nx][ny]=1;
						if(r==6*n+1)r=0;
					}
				}
			}
		}
		return dis[ex][ey];
	}
	void solve(){
		scanf("%d",&q);
		while(q--){
			int op,x,y,x1,y1,c;
			scanf("%d",&op);
			if(op==1){
				scanf("%d%d%d",&x,&y,&c);
				A[x][y]=c;
			}
			else {
				scanf("%d%d%d%d",&x,&y,&x1,&y1);
				printf("%lld\n",SPFA(x,y,x1,y1));	
			}
		}
	}
}pshui;
struct node{
	int ll[7][7],rr[7][7],lr[7][7];int l,r;
	void clear(){
		memset(ll,40,sizeof(ll));
		memset(rr,40,sizeof(rr));
		memset(lr,40,sizeof(lr));
	}
}tree[M<<2];
node operator+(node ls,node rs){
	static int lm[7][7],rm[7][7];
	memset(lm,40,sizeof(lm));
	memset(rm,40,sizeof(rm));
	node ans;ans.clear();
	for(int k=1;k<=6;k++)
		for(int i=1;i<=6;i++)
			for(int j=1;j<=6;j++){
				lm[i][j]=min(1LL*lm[i][j],1LL*ls.lr[i][k]+rs.ll[k][j]+ls.rr[j][j]);
				rm[i][j]=min(1LL*rm[i][j],1LL*rs.ll[i][i]+ls.rr[i][k]+rs.lr[k][j]);
			}
	for(int i=1;i<=6;i++)
		for(int j=1;j<=6;j++){
			ans.ll[i][j]=ls.ll[i][j];ans.rr[i][j]=rs.rr[i][j];ans.lr[i][j]=inf;
			for(int k=1;k<=6;k++){
				ans.ll[i][j]=min(ans.ll[i][j],lm[i][k]+ls.lr[j][k]-ls.rr[k][k]);
				ans.rr[i][j]=min(ans.rr[i][j],rm[k][i]+rs.lr[k][j]-rs.ll[k][k]);
				ans.lr[i][j]=min(ans.lr[i][j],ls.lr[i][k]+rs.lr[k][j]);
				ans.lr[i][j]=min(ans.lr[i][j],lm[i][k]+rm[k][j]-ls.rr[k][k]-rs.ll[k][k]);
			}
		}
	ans.l=ls.l;ans.r=rs.r;
	return ans;
}
#define fa tree[p]
#define lson tree[p<<1]
#define rson tree[p<<1|1]
void build(int l,int r,int p){
	fa.l=l;fa.r=r;
	if(l==r){
		int sum[7];sum[0]=0;
		for(int i=1;i<=6;i++)sum[i]=sum[i-1]+A[i][l];
		for(int i=1;i<=6;i++)
			for(int k=1;k<=6;k++)
				fa.ll[i][k]=fa.rr[i][k]=fa.lr[i][k]=sum[max(i,k)]-sum[min(i,k)-1];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,p<<1);
	build(mid+1,r,p<<1|1);
	fa=lson+rson;
}
void update(int x,int h,int d,int p){
	if(x==fa.l&&fa.l==fa.r){
		A[h][x]=d;
		int sum[7];sum[0]=0;
		for(int i=1;i<=6;i++)sum[i]=sum[i-1]+A[i][x];
		for(int i=1;i<=6;i++)
			for(int k=1;k<=6;k++)
				fa.ll[i][k]=fa.rr[i][k]=fa.lr[i][k]=sum[max(i,k)]-sum[min(i,k)-1];
		return;
	}
	int mid=(fa.l+fa.r)>>1;
	if(x<=mid)update(x,h,d,p<<1);
	else update(x,h,d,p<<1|1);
	fa=lson+rson;
}
node query(int l,int r,int p){
	if(fa.l==l&&fa.r==r)return fa;
	int mid=(fa.l+fa.r)>>1;
	if(r<=mid)return query(l,r,p<<1);
	else if(l>mid)return query(l,r,p<<1|1);
	node a=query(l,mid,p<<1),b=query(mid+1,r,p<<1|1);
	return a+b;
}
int Query(int sx,int sy,int ex,int ey){
	if(sy>ey){swap(sy,ey);swap(sx,ex);}
	node ls=query(1,sy,1);
	node md=query(sy,ey,1);
	node rs=query(ey,n,1);
	int ans=md.lr[sx][ex];
	for(int i=1;i<=6;i++)
		for(int j=1;j<=6;j++){
			ans=min(ans,md.ll[sx][i]+ls.rr[i][j]+md.lr[j][ex]-A[i][sy]-A[j][sy]);
			ans=min(ans,md.lr[sx][i]+rs.ll[i][j]+md.rr[j][ex]-A[i][ey]-A[j][ey]);
			ans=min(ans,ls.rr[sx][i]+md.lr[i][j]+rs.ll[j][ex]-A[i][sy]-A[j][ey]);
		}
	return ans;
}
void solve(){
	build(1,n,1);
	scanf("%d",&q);
	while(q--){
		int op,x,y,x1,y1,c;
		scanf("%d",&op);
		if(op==1){
			scanf("%d%d%d",&x,&y,&c);
			update(y,x,c,1);
		}
		else {
			scanf("%d%d%d%d",&x,&y,&x1,&y1);
			printf("%d\n",Query(x,y,x1,y1));	
		}
	}
}
int main(){
	freopen("shortest.in","r",stdin);
	freopen("shortest.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=6;i++){
		for(int j=1;j<=n;j++)
			scanf("%d",&A[i][j]);
	}
	solve();
	return 0;
}
