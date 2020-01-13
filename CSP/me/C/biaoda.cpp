#include<bits/stdc++.h>
using namespace std;
#define N 20007
#define mem(x) memset(x,0,sizeof(x))
int hd[N],pre[N],to[N],num,fa[N],sz[N],d[N],p[N],ver;
bool in[N],out[N];
void adde(int x,int y)
{
	num++;pre[num]=hd[x];hd[x]=num;to[num]=y;
}
int find(int x)
{
	return fa[x]==x?x:fa[x]=find(fa[x]);
}
void merge(int x,int y)
{
	int u=find(x),v=find(y);
	fa[u]=v,sz[v]+=sz[u];
	out[x]=in[y]=1;
}
bool check(int x,int y,int l)
{
	if(in[y]||out[x])return false;
	int u=find(x),v=find(y);
	if(u==v&&sz[u]!=l)return false;
	return true;
}
void dfs1(int v,int f)
{
	if(f!=v&&check(f,v,d[v]+1))ver=min(ver,v);
	for(int i=hd[v];i;i=pre[i])
	{
		int u=to[i];
		if(i==f)continue;
		if(check(f,i,d[v]+1))
		{
			dfs1(u,i^1);
		}
	}
}
bool dfs2(int v,int f,int p)
{
	if(v==p)
	{
		merge(f,v);
		return true;
	}
	for(int i=hd[v];i;i=pre[i])
	{
		int u=to[i];
		if(i==f)continue;
		if(dfs2(u,i^1,p))
		{
			merge(f,i);
			return true;
		}
	}
	return false;
}
int main()
{
	int t,n;
	scanf("%d",&t);
	while(t--)
	{
		scanf("%d",&n);
		mem(hd),mem(in),mem(out),mem(d);
		num=(n+1)/2*2+1;
		for(int i=1;i<=n;i++)
			scanf("%d",&p[i]);
		for(int i=1;i<n;i++)
		{
			int x,y;
			scanf("%d%d",&x,&y);
			d[x]++,d[y]++;
			adde(x,y),adde(y,x);
		}
		for(int i=1;i<=num;i++)
			fa[i]=i,sz[i]=1;
		for(int i=1;i<=n;i++)
		{
			int v=p[i];
			ver=n+1;
			dfs1(v,v);
			dfs2(v,v,ver);
			printf("%d ",ver);
		}
		printf("\n");
	}
	return 0;
}
