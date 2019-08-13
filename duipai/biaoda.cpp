#include<iostream>
#include<cstdio>
#include<cstdlib>
#include<algorithm>
#include<map>
#include<queue>
#include<cstring>
using namespace std;
const int N=5e5+10;
struct edge{int next,to,w,cost;}a[N];
int n,k,rk[N],B[N],l[N],r[N],dis[N],vis[N];
int pe[N],px[N],cnt=1,head[N],Ans,S,T,cc;
map<int,int> Map;
queue<int> Q;
void link(int x,int y,int w,int cost)
{
	a[++cnt]=(edge){head[x],y,w, cost};head[x]=cnt;
	a[++cnt]=(edge){head[y],x,0,-cost};head[y]=cnt;
}
int SPFA()
{
	memset(dis,-63,sizeof(dis));
	Q.push(S);dis[S]=0;vis[S]=1;
	while(!Q.empty())
	{
		int x=Q.front();
		for(int i=head[x];i;i=a[i].next)
		{
			int R=a[i].to;
			if(!a[i].w||dis[R]>=dis[x]+a[i].cost) continue;
			dis[R]=dis[x]+a[i].cost;
			pe[R]=i;px[R]=x;
			if(!vis[R]) Q.push(R);
		}
		vis[x]=0;Q.pop();
	}
	return dis[T]!=dis[0];
}
int main()
{
    freopen("data.in","r",stdin);
    freopen("2.ans","w",stdout);
	cin>>n>>k;
	for(int i=1;i<=n;i++)
	{
		cin>>l[i]>>r[i],B[++cc]=l[i],B[++cc]=r[i];
		if(l[i]>r[i]) swap(l[i],r[i]);
	}
	sort(B+1,B+cc+1);
	cc=unique(B+1,B+cc+1)-B-1;
	for(int i=1;i<=cc;i++) rk[i]=B[i],Map[B[i]]=i;
	for(int i=1;i<=n;i++) l[i]=Map[l[i]],r[i]=Map[r[i]];
	for(int i=1;i<cc;i++) link(i,i+1,k,0);
	for(int i=1;i<=n;i++) link(l[i],r[i],1,rk[r[i]]-rk[l[i]]);
	S=cc+1;T=S+1;link(S,1,k,0);link(cc,T,k,0);
	while(SPFA())
	{
		int flow=1e9;
		for(int x=T;x!=S;x=px[x]) flow=min(flow,a[pe[x]].w);
		for(int x=T;x!=S;x=px[x]) a[pe[x]].w-=flow,a[pe[x]^1].w+=flow;
		Ans+=flow*dis[T];
	}
	cout<<Ans<<endl;
}