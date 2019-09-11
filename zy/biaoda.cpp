#include<stdio.h>
#include<bitset>
using namespace std;
const int M=3005;
int n,m;
bitset<M>E[M],tmp;
int Tc[45][3],tcc;
namespace Subtask1
{
	void Solve()
	{
		tcc=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<i;j++)
			{
				if(!E[i][j])continue;
				tmp=E[i]&E[j];
				if(tmp.count())
				{
					for(int q=1;q<j;q++)
						if(tmp[q])
						{
							++tcc;
							Tc[tcc][0]=i;Tc[tcc][1]=j;Tc[tcc][2]=q;
						}
				}
			}
	}
};

namespace Subtask2
{
	bool Public(int x,int y)
	{
		return Tc[x][0]==Tc[y][0] ||
			Tc[x][0]==Tc[y][1] ||
			Tc[x][0]==Tc[y][2] ||
			Tc[x][1]==Tc[y][0] ||
			Tc[x][1]==Tc[y][1] ||
			Tc[x][1]==Tc[y][2] ||
			Tc[x][2]==Tc[y][0] ||
			Tc[x][2]==Tc[y][1] ||
			Tc[x][2]==Tc[y][2];
	}
	int Out[45][3],Deg[45];
	int ans;
	bool Mk[45];
	void dfs(int d,int c,int las)
	{
		if(d>tcc){ans=max(ans,c);return;}
		if(c+las/2<=ans)return;
		if(Mk[d])return dfs(d+1,c,las);
		bool f=false;
		for(int i=0;i<Deg[d];i++)
		{
			int v=Out[d][i];
			if(Mk[v])continue;
			f=true;
			Mk[v]=true;dfs(d+1,c+1,las-2);Mk[v]=false;
		}
		if(!f)dfs(d+1,c,las-1);
	}
	void Solve()
	{
		for(int i=1;i<=tcc;i++)Deg[i]=0;
		for(int i=1;i<=tcc;i++)
			for(int j=i+1;j<=tcc;j++)
				if(i!=j && Public(i,j))
					Out[i][Deg[i]++]=j;
		ans=0;
		dfs(1,0,n);
		printf("%d\n",tcc-ans);
	}
};

int main()
{
	int T;scanf("%d",&T);
	while(T--)
	{
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++)E[i].reset();
		for(int i=1;i<=m;i++)
		{
			int u,v;scanf("%d%d",&u,&v);if(u>v)swap(u,v);
			E[v][u]=1;
		}
		Subtask1::Solve();
		Subtask2::Solve();
	}
	return 0;
}
