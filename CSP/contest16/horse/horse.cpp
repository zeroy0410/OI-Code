#include<stdio.h>
#include<algorithm>
#include<vector>
#include<iostream>
#define M 100005
#define LL long long
using namespace std;
int n,A[M],h[M],tt;
struct edge{
	int nxt,to,co;
}G[M<<1];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
int mark[20];
struct P10{
	LL res,ans,hv;
	struct node{
		int to,co;
		bool operator < (const node& res)const{
			return mark[to]<mark[res.to];
		}
	};
	vector<node>H[20];
	void dfs(int x,int f){
		hv+=A[x];
		for(int i=0;i<H[x].size();i++){
			int u=H[x][i].to,v=H[x][i].co;
			if(u==f)continue;
			if(hv<v)res+=v-hv,hv=0;
			else hv-=v;
			dfs(u,x);
			if(hv<v)res+=v-hv,hv=0;
			else hv-=v;
		}
	}
	void solve(){
		for(int i=1;i<=n;i++){
			H[i].clear();
			for(int j=h[i];j;j=G[j].nxt){
				int u=G[j].to,v=G[j].co;
				H[i].push_back((node){u,v});
			}
		}
		for(int i=1;i<=n;i++)mark[i]=i;
		LL ans=2e9;
		do{
			res=hv=0;
			for(int i=1;i<=n;i++)
				sort(H[i].begin(),H[i].end());
			dfs(1,0);
			ans=min(ans,res);
		}while(next_permutation(mark+1,mark+n+1));
		printf("%lld\n",ans);
	}
}p10;
LL Val[M];
struct P100{
	struct node{
		int to,co;
		bool operator < (const node& res)const{
			return Val[to]-2*co>Val[res.to]-2*res.co;
		}
	};
	vector<node>H[M];
	void dfs(int x,int f){
		Val[x]+=A[x];
		for(int i=0;i<H[x].size();i++){
			int u=H[x][i].to,v=H[x][i].co;
			if(u==f)continue;
			dfs(u,x);
			Val[x]+=Val[u];
			Val[x]-=2*v;
		}
	}
	LL hv,ans;
	void redfs(int x,int f){
		hv+=A[x];
		for(int i=0;i<H[x].size();i++){
			int u=H[x][i].to,v=H[x][i].co;
			if(u==f)continue;
			if(hv<v)ans+=v-hv,hv=0;
			else hv-=v;
			redfs(u,x);
			if(hv<v)ans+=v-hv,hv=0;
			else hv-=v;
		}
	}
	void solve(){
		for(int i=1;i<=n;i++){
			H[i].clear();
			for(int j=h[i];j;j=G[j].nxt){
				int u=G[j].to,v=G[j].co;
				H[i].push_back((node){u,v});
			}
		}
		dfs(1,0);
		for(int i=1;i<=n;i++)
			sort(H[i].begin(),H[i].end());
		ans=hv=0;
		redfs(1,0);
		for(int _=1;_<=900000/n;_++){
			LL tmp=ans;
			for(int i=1;i<=n;i++)
				random_shuffle(H[i].begin(),H[i].end());
			ans=hv=0;
			redfs(1,0);
			if(ans>tmp)ans=tmp;
		}
		printf("%lld\n",ans);
	}
}p100;
int main(){
	freopen("horse.in","r",stdin);
	freopen("horse.out","w",stdout);
	srand(19260817);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1,a,b,c;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		Add(a,b,c);Add(b,a,c);
	}
	p100.solve();
	return 0;
}
