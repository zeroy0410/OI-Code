#include<bits/stdc++.h>
#define M 500005
using namespace std;
int n,m,h[M],tt,tmp[M],in[M];
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
struct P19{
	int ans[2005],acnt;
	queue<int>Q;
	bool check(int now){
		for(int i=1;i<=n;i++)in[i]=tmp[i];
		for(int i=h[now];i;i=G[i].nxt){
			int u=G[i].to;
			in[u]--;
		}
		for(int i=1;i<=n;i++)
			if(in[i]==0)Q.push(i);
		int ct=0;
		while(!Q.empty()){
			int x=Q.front();Q.pop();
			ct++;
			for(int i=h[x];i;i=G[i].nxt){
				int u=G[i].to;
				if(u==now)continue;
				in[u]--;
				if(!in[u])Q.push(u);
			}
		}
		return ct==n-1;
	}
	void solve(){
		acnt=0;
		for(int i=1;i<=n;i++)
			if(check(i))
				ans[++acnt]=i;
		printf("%d\n",acnt);
		for(int i=1;i<=acnt;i++){
			printf("%d",ans[i]);
			if(i==acnt)puts("");
			else printf(" ");
		}
	}
}p19;
int fa[M];
int getfa(int x){
	return fa[x]==x?x:fa[x]=getfa(fa[x]);
}
struct P28{
	queue<int>Q;
	bool mark[M];
	void solve(){
		int las=-1;
		for(int i=1;i<=n;i++){
			int rt=getfa(i);
			if(las==-1)las=rt;
			else if(las!=rt){
				puts("0");
				return;
			}
		}
		for(int i=1;i<=n;i++)in[i]=tmp[i];
		for(int i=1;i<=n;i++)
			if(in[i]==0)Q.push(i);
		int ct=0;
		while(!Q.empty()){
			int x=Q.front();Q.pop();
			mark[x]=1;ct++;
			for(int i=h[x];i;i=G[i].nxt){
				int u=G[i].to;
				in[u]--;
				if(!in[u])Q.push(u);
			}
		}
		printf("%d\n",n-ct);
		for(int i=1;i<=n;i++)
			if(!mark[i])printf("%d ",i);
		puts("");
	}
}p28;
struct P42{
	int ret[M],ans[M],ac;
	void solve(){
		int mx=0;
		for(int i=1;i<=n;i++){
			for(int j=h[i];j;j=G[j].nxt){
				int u=G[j].to;
				if(u<i){
					ret[u]++;
					ret[i+1]--;
					mx++;
				}
			}
		}
		for(int i=1;i<=n;i++)ret[i]+=ret[i-1];
		ac=0;
		for(int i=1;i<=n;i++)
			if(ret[i]==mx)
				ans[++ac]=i;
		printf("%d\n",ac);
		for(int i=1;i<=ac;i++)
			printf("%d ",ans[i]);
		puts("");
	}
}p42;
int main(){
//	freopen("reality.in","r",stdin);
//	freopen("reality.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)fa[i]=i;
	bool fl28=(n==m);
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		if(a!=i)fl28=0;
		fa[getfa(a)]=getfa(b);
		Add(a,b);tmp[b]++;
	}
	p42.solve();
	return 0;
}
