#include<cstdio>
#include<cstring>
#include<algorithm>
#include<cmath>
#include<iostream>
#include<cstdlib>
#include<string>
#include<ctime>
#include<queue>
#include<climits>
using namespace std;
string ctrmmp;
bool an[10001];
int dist[10001],cur[10001],n,m,s,t,sum=0,v[100001];
int nedge=-1,p[100001],c[100001],C[100001],nex[100001],head[100001];
inline void addedge(int x,int y,int z){
	p[++nedge]=y;C[nedge]=c[nedge]=z;
	nex[nedge]=head[x];head[x]=nedge;
}
inline bool bfs(int s,int t){
	queue<int>q;q.push(s);
	memset(dist,-1,sizeof dist);dist[s]=1;
	while(!q.empty()){
		int now=q.front();q.pop();
		for(int k=head[now];k>-1;k=nex[k])if(c[k]&&dist[p[k]]==-1){
			dist[p[k]]=dist[now]+1;q.push(p[k]);
		}
	}
	return dist[t]>-1?1:0;
}
inline int dfs(int x,int low){
	if(x==t)return low;
	int a,used=0;
	for(int k=cur[x];k>-1;k=nex[k])if(c[k]&&dist[p[k]]==dist[x]+1){
		a=dfs(p[k],min(c[k],low-used));
		if(a)c[k]-=a,c[k^1]+=a,used+=a;
		if(c[k])cur[x]=k;
		if(used==low)break;
	}
	if(!used)dist[x]=-1;
	return used;
}
inline int dinic(){
	int flow=0;
	while(bfs(s,t)){
		for(int i=s;i<=t;i++)cur[i]=head[i];
		flow+=dfs(s,1e9);
	}
	return flow;
}
int main()
{
	memset(p,-1,sizeof p);memset(nex,-1,sizeof nex);
	memset(c,-1,sizeof c);memset(head,-1,sizeof head);
	scanf("%d%d",&n,&m);
	s=0;t=n+m+1;
	for(int i=1;i<=n;i++){
		int v;scanf("%d",&v);addedge(s,i,v);addedge(i,s,0);sum+=v;
		getline(cin,ctrmmp);ctrmmp+=' ';int l=ctrmmp.size();
		int k=0;
		for(int j=0;j<l;j++){
			if(ctrmmp[j]>='0'&&ctrmmp[j]<='9')k=k*10+ctrmmp[j]-'0';
			else if(k)addedge(i,n+k,1e9),addedge(n+k,i,0),k=0;
		}
	}
	for(int i=1;i<=m;i++){
		int x;scanf("%d",&x);
		addedge(n+i,t,x);addedge(t,n+i,0);
	}
	int ans=dinic();
	for(int k=head[t];k>-1;k=nex[k]){
		memcpy(c,C,sizeof(C));
		int rp=c[k^1];c[k^1]=0;
		if(ans-dinic()==rp)an[p[k]-n]=1;
	}
	for(int i=1;i<=n;i++){
		bool flag=1;
		for(int k=head[i];k>-1;k=nex[k])if(p[k]&&!an[p[k]-n]){flag=0;break;}
		if(flag)printf("%d ",i);
	}
	puts("");for(int i=1;i<=m;i++)if(an[i])printf("%d ",i);
	printf("\n%d",sum-ans);
	return 0;
}