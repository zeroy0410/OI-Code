#include<bits/stdc++.h>
#define M 100005
#pragma GCC optimize(3,"Ofast","inline")
using namespace std;
int n,m,h[M],tt,in[M],tmp[M];
struct edge{
	int nxt,to;
}G[M*25];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
bool mark[M];
queue<int>Q;
void del(int e,int mid){
	mark[e]=1;Q.push(e);
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		for(int i=h[x];i;i=G[i].nxt){
			int u=G[i].to;
			if(!mark[u]){
				tmp[u]--;
				if(tmp[u]<mid){
					mark[u]=1;
					Q.push(u);
				}
			}
		}
	}
}
bool check(int mid){
	for(int i=1;i<=n;i++)tmp[i]=in[i],mark[i]=0;
	for(int i=1;i<=n;i++){
		if(!mark[i]&&tmp[i]<mid)
			del(i,mid);
	}
	for(int i=1;i<=n;i++)
		if(!mark[i])return 1;
	return 0;
}
int main(){
	scanf("%d%d",&n,&m);
	int mx=0;
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
		in[a]++;in[b]++;
		mx=max(in[a],mx);
		mx=max(in[b],mx);
	}
	int l=0,r=mx,ans=-1;
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)){
			ans=mid;
			l=mid+1;
		}
		else r=mid-1;
	}
	printf("%d\n",ans);
	return 0;
}