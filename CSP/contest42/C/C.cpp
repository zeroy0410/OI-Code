#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
const int mod=1e9+7;
int n,m,h[M],tt,A[M],in[M];
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b};
	h[a]=tt;
}
bool cmp(int a,int b){
	if(in[a]!=in[b])return in[a]>in[b];
	return a>b;
}
LL mark[M],tot[M];
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1,a,b;i<=m;i++){
		scanf("%d%d",&a,&b);
		Add(a,b);Add(b,a);
		in[a]++;in[b]++;
	}
	for(int a=1;a<=n;a++){
		for(int j=h[a];j;j=G[j].nxt){
			int b=G[j].to;
			if(!cmp(a,b))continue;
			for(int k=h[b];k;k=G[k].nxt){
				int c=G[k].to;
				if(!cmp(a,c))continue;
				mark[a]+=tot[c];mark[b]+=tot[c];mark[c]+=tot[c];++tot[c];
			}
		}
		for(int j=h[a];j;j=G[j].nxt){
			int b=G[j].to;
			if(!cmp(a,b))continue;
			for(int k=h[b];k;k=G[k].nxt){
				int c=G[k].to;
				if(!cmp(a,c))continue;
				mark[b]+=(--tot[c]);
			}
		}
	}
	LL ans=0;
	for(int i=1;i<=n;i++){
		ans=(ans+1LL*A[i]*mark[i]%mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
