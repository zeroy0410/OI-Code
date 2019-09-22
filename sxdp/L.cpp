#include<stdio.h>
#include<iostream>
#include<string.h>
#include<algorithm>
#pragma GCC optimize(2)
#define M 5005
using namespace std;
int n,h[M],tt;
struct edge{
	int nxt,to,co;
}G[M<<1];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
int aa[M],bb[M],cc[M];
int ans=2e9,ign;
int mx[M][2];
inline void Add(int* T,int d){
	if(d>T[0]){T[1]=T[0];T[0]=d;}
	else if(d>T[1])T[1]=d;
}
int zj,fa[M];
void dfs(int x){
	mx[x][0]=mx[x][1]=0;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to,c=G[i].co;
		if(x==aa[ign]&&u==bb[ign]||x==bb[ign]&&u==aa[ign])continue;
		if(u==fa[x])continue;
		fa[u]=x;
		dfs(u);
		Add(mx[x],mx[u][0]+c);
	}
	zj=max(zj,mx[x][0]+mx[x][1]);
}
int mi;
void redfs(int x){
	if(mx[x][0]<mi)mi=mx[x][0];
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to,c=G[i].co;
		if(x==aa[ign]&&u==bb[ign]||x==bb[ign]&&u==aa[ign])continue;
		if(u==fa[x])continue;
		fa[u]=x;
		int tmp=mx[x][0];
		if(mx[u][0]+c==mx[x][0])tmp=mx[x][1];
		Add(mx[u],tmp+c);
		redfs(u);
	}
}
int solve(){
	mi=2e9,zj=0;
	fa[aa[ign]]=0;dfs(aa[ign]);redfs(aa[ign]);
	int tmp=mi;mi=2e9;
	int tmp2=zj;zj=0;
	fa[bb[ign]]=0;dfs(bb[ign]);redfs(bb[ign]);
	return max(tmp+mi+cc[ign],max(zj,tmp2));
}
int main(){
	scanf("%d",&n);
	for(int i=1,a,b,c;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		Add(a,b,c);Add(b,a,c);
		aa[i]=a;bb[i]=b;cc[i]=c;
	}
	for(int i=1;i<n;i++){
		ign=i;
		ans=min(ans,solve());
	}
	printf("%d\n",ans);
	return 0;
}
