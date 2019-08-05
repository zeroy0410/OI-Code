#include<bits/stdc++.h>
#define M 2005
using namespace std;
int A[M],n,m,h[M],tt,in[M],tmp[M];
struct edge{
	int nxt,to;
}G[M<<4];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
struct node{
	int x;
	bool operator < (const node& res)const{
		return A[x]<A[res.x];
	}
};
priority_queue<node>Q;
int ans[M],acnt=0;
int calc(int x){
	while(!Q.empty())Q.pop();
	for(int i=1;i<=n;i++){
		in[i]=tmp[i]; 
		if(!in[i]&&i!=x)Q.push((node){i});	
	} 
	int c=n+1;
	while(!Q.empty()){
		c--;
		int e=Q.top().x;Q.pop();
		if(A[e]<c)return c;
		for(int i=h[e];i;i=G[i].nxt){
			int u=G[i].to;
			in[u]--;
			if(!in[u]&&u!=x)
				Q.push((node){u});
		}
	}
	return c-1;
}
int main(){
	freopen("plane.in","r",stdin);
	freopen("plane.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,x;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		Add(b,a);in[a]++;
	}
	for(int i=1;i<=n;i++)tmp[i]=in[i];
	for(int i=1;i<=n;i++)
		if(!in[i])Q.push((node){i});
	while(!Q.empty()){
		node e=Q.top();Q.pop();
		ans[++acnt]=e.x; 
		for(int i=h[e.x];i;i=G[i].nxt){
			int u=G[i].to;
			in[u]--;
			if(!in[u])
				Q.push((node){u});
		}
	}
	for(int i=acnt;i;i--) 
		printf("%d ",ans[i]);
	puts("");
	for(int i=1;i<=n;i++)
		printf("%d ",calc(i));
	return 0;
}