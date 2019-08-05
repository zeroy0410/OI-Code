#include<bits/stdc++.h> 
#define LL long long
#define M 200005
using namespace std;
int n,fa[M],h[M],tot;
LL p[M],q[M],l[M],dis[M],ans[M];
int qq[M],stk[M],top;
struct edge{int nxt,to;}G[M<<1];
void Add(int a,int b){
	G[++tot]=(edge){h[a],b};
	h[a]=tot;
}
int sz[M],rt,mx[M],tt;
bool vis[M];
void dfsrt(int x,int f){
	sz[x]=1;mx[x]=0;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f||vis[u])continue;
		dfsrt(u,x);
		sz[x]+=sz[u];
		mx[x]=max(mx[x],sz[u]);
	}
	mx[x]=max(mx[x],tt-mx[x]);
	if(mx[x]<mx[rt])rt=x;
}
void dfssz(int x,int f){
	sz[x]=1;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f||vis[u])continue;
		dfssz(u,x);
		sz[x]+=sz[u];
	}
}
bool cmp(int a,int b){return l[a]>l[b];}
double calcK(int u,int v){return (double)(ans[u]-ans[v])/(dis[u]-dis[v]);}
void dfsqq(int x,int f){
	qq[++qq[0]]=x;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f||vis[u])continue;
		dfsqq(u,x);
	}
}
void solve(int x,int f){//f��ʾ���ڵ�ǰx��˵��fa[x]�����ϵ����ȵ�Ӱ���Ѿ�����ˣ�����Ҫ�ظ����� 
	dfssz(x,-1);//���¼���sz 
	vis[x]=1;
	if(x!=1&&!vis[fa[x]]){//����һ����֮ǰ����������Ҫ�ȼ������
		tt=sz[fa[x]];rt=0;
		dfsrt(fa[x],-1);
		solve(rt,f); 
	}
	qq[0]=0;dfsqq(x,fa[x]);
	sort(qq+1,qq+qq[0]+1,cmp);
	top=0;
	for(int i=1,now=fa[x];i<=qq[0];i++){//�õ�ǰ��ĸ��׸��µ�ǰ�������
		while(now!=fa[f]/*��֤�����������������֤���Ӷ�*/&&l[qq[i]]<=dis[now]){
			while(top>1&&calcK(stk[top-1],stk[top])<=calcK(stk[top],now))top--;
			stk[++top]=now;now=fa[now];
		}
		if(!top)continue;
		int l=1,r=top;
		while(l!=r){
			int mid=(l+r)>>1;
			if(calcK(stk[mid],stk[mid+1])<(double)p[qq[i]])r=mid;
			else l=mid+1;
		}
		int j=qq[i];
		ans[j]=min(ans[j],ans[stk[l]]+(dis[j]-dis[stk[l]])*p[j]+q[j]);
	}
	for(int i=1;i<=qq[0];i++){
		if(qq[i]!=x&&l[qq[i]]<=dis[x]){
			int j=qq[i];
			ans[j]=min(ans[j],ans[x]+(dis[j]-dis[x])*p[j]+q[j]);
		}
	}
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(!vis[u]&&u!=fa[x]){
			tt=sz[u];rt=0;
			dfsrt(u,x);
			solve(rt,u);
		}
	}
}
int t;
int main(){
	scanf("%d%d",&n,&t);
	mx[0]=1e9;
	memset(ans,0x3f,sizeof(ans));
	ans[1]=0;
	for(int i=2;i<=n;i++){
		LL ds;
		scanf("%d%lld%lld%lld%lld",&fa[i],&ds,&p[i],&q[i],&l[i]);
		Add(i,fa[i]);Add(fa[i],i);
		dis[i]=dis[fa[i]]+ds;
	}	
	for(int i=2;i<=n;i++)l[i]=dis[i]-l[i];
	tt=n;
	dfsrt(1,-1);
	solve(rt,1);
	for(int i=2;i<=n;i++)printf("%lld\n",ans[i]);
	return 0;
}
