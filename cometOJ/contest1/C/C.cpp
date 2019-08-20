#include<bits/stdc++.h>
#define M 200005
#define LL long long
using namespace std;
int n,h[M],tt;
struct edge{
	int nxt,to;
	LL co;
}G[M<<1];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
LL mx[M][3],zj[M][3],tmp[M][3];
LL dp[M],ans=0;
void update(LL* x,LL y){
	if(y>x[0]){x[2]=x[1];x[1]=x[0];x[0]=y;}
	else if(y>x[1]){x[2]=x[1];x[1]=y;}
	else if(y>x[2]){x[2]=y;}
} 
void dfs(int x,int f){
	mx[x][0]=mx[x][1]=mx[x][2]=0;
	bool fl=1;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to,c=G[i].co;
		if(u==f)continue;
		dfs(u,x);
		update(mx[x],mx[u][0]+c);
		dp[x]=max(dp[x],dp[u]);
		update(zj[x],dp[u]);
		fl=0;
	}
	if(fl)mx[x][0]=0;
	dp[x]=max(dp[x],mx[x][0]+mx[x][1]);
}
void dfs2(int x,int f,LL y){
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;LL c=G[i].co;
		if(u==f)continue;
		LL res=mx[x][0];
		if(res-c==mx[u][0])res=mx[x][1];
		res=max(res,y);
		dfs2(u,x,res+c);
	}
	update(mx[x],y);
}
void redfs(int x,int f,LL ds){
	update(zj[x],ds);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;LL c=G[i].co;
		if(u==f)continue;
		LL res=zj[x][0];
		if(dp[u]==zj[x][0])res=zj[x][1];
		res=max(res,ds);
		if(mx[x][0]==tmp[u][0]+c)res=max(res,mx[x][1]+mx[x][2]);
		else if(mx[x][1]==tmp[u][0]+c)res=max(res,mx[x][0]+mx[x][2]);
		else res=max(res,mx[x][0]+mx[x][1]);
		ans=max(ans,dp[u]*res);
		redfs(u,x,res);
	}
}
int main(){
	scanf("%d",&n);
	for(int i=1,a,b;i<n;i++){
		LL c;
		scanf("%d%d%lld",&a,&b,&c);
		Add(a,b,c);
		Add(b,a,c);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++){tmp[i][0]=mx[i][0];tmp[i][1]=mx[i][1];tmp[i][2]=mx[i][2];}
	dfs2(1,0,0);
	redfs(1,0,0);
	for(int i=1;i<=tt;i++)G[i].co=-G[i].co;
	memset(dp,0,sizeof(dp));
	memset(zj,0,sizeof(zj));
	memset(mx,0,sizeof(mx));
	dfs(1,0);
	for(int i=1;i<=n;i++){tmp[i][0]=mx[i][0];tmp[i][1]=mx[i][1];tmp[i][2]=mx[i][2];}
	dfs2(1,0,0);
	redfs(1,0,0);
	printf("%lld\n",ans);
	return 0;
}