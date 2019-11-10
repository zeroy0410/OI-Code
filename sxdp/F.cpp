#include<stdio.h>
#include<algorithm>
#define LL long long
#define M 200005
using namespace std;
int n,h[M],tt;
struct edge{
	int nxt,to,co;
}G[M<<1];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
LL mx[M][3],ans;
void Update(int x,LL d){
	if(d>mx[x][0]){
		mx[x][2]=mx[x][1];
		mx[x][1]=mx[x][0];
		mx[x][0]=d;
	}
	else if(d>mx[x][1]){
		mx[x][2]=mx[x][1];
		mx[x][1]=d;
	}
	else if(d>mx[x][2])
		mx[x][2]=d;
}
void dfs(int x,int f){
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to,v=G[i].co;
		if(u==f)continue;
		dfs(u,x);
		Update(x,mx[u][0]+v);
	}
}
void redfs(int x,int f,LL d){
	Update(x,d);
	ans=max(ans,mx[x][2]+mx[x][1]+mx[x][1]+mx[x][0]);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to,v=G[i].co;
		if(u==f)continue;
		LL tmp=mx[x][0];
		if(mx[x][0]==mx[u][0]+v)tmp=mx[x][1];
		redfs(u,x,tmp+v);
	}
}
int main(){
	ans=0;
	scanf("%d%*d",&n);
	for(int i=1,a,b,c;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		Add(a,b,c);Add(b,a,c);
	}
	dfs(1,0);
	redfs(1,0,0);
	printf("%lld\n",ans);
	return 0;
}
