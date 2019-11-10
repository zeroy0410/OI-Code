#include<bits/stdc++.h>
#define M 20005
using namespace std;
int A[M],n,m,h[M],tt,in[M];
struct edge{
	int nxt,to;
}G[M<<1];
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
int ans2[M];
int main(){
//	freopen("plane.in","r",stdin);
//	freopen("plane.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,x;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		Add(b,a);in[a]++;
	}
	for(int i=1;i<=n;i++)
		if(!in[i])Q.push((node){i});
	while(!Q.empty()){
		node e=Q.top();Q.pop();
		ans[++acnt]=e.x;ans2[e.x]=acnt+Q.size(); 
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
		printf("%d ",n-ans2[i]+1);
	puts("");
	return 0;
}
