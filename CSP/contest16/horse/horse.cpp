#include<stdio.h>
#include<algorithm>
#include<vector>
#include<iostream>
#define M 100005
#define LL long long
using namespace std;
int n,A[M],h[M],tt;
struct edge{int nxt,to,co;}G[M<<1];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
struct node{LL v,w;};
bool cmp0(node a,node b){return a.w+a.v<b.w+b.v;}
bool cmp1(node a,node b){return a.v<b.v;}
LL dp[M],ned[M];
vector<node>wk[2][M];
bool check(LL mid,int x){
	for(int i=0;i<wk[1][x].size();i++){
		if(wk[1][x][i].v<=mid)mid+=wk[1][x][i].w;
		else return 0;
	}
	for(int i=0;i<wk[0][x].size();i++)mid+=wk[0][x][i].w;
	if(mid<0)return 0;
	for(int i=0;i<wk[0][x].size();i++){
		mid-=wk[0][x][i].w;
		if(mid<wk[0][x][i].v)return 0;
	}
	return 1;
}
void dfs(int x,int f){
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to,v=G[i].co;
		if(u==f)continue;
		dfs(u,x);
		LL tmp=-dp[u]+A[u]-2*v;
		wk[tmp>=0][x].push_back((node){ned[u]+v,tmp});
	}
	sort(wk[0][x].begin(),wk[0][x].end(),cmp0);
	sort(wk[1][x].begin(),wk[1][x].end(),cmp1);
	LL l=0,r=2e14,ans=-1;
	while(l<=r){
		LL mid=(l+r)>>1;
		if(check(mid,x)){ans=mid;r=mid-1;}
		else l=mid+1;
	}
	ned[x]=ans-A[x];
	LL tmp=ans;
	for(int i=0;i<wk[1][x].size();i++){if(wk[1][x][i].v<=tmp)tmp+=wk[1][x][i].w;}
	for(int i=0;i<wk[0][x].size();i++)tmp+=wk[0][x][i].w;
	dp[x]=ans-tmp;
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1,a,b,c;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		Add(a,b,c);Add(b,a,c);
	}
	dfs(1,0);
	printf("%lld\n",ned[1]);
	return 0;
}
