#include<bits/stdc++.h>
#define M 1000005
const int mod=998244353;
using namespace std;
int n,m,h[M],tt,h2[M],tt2;
struct edge{
	int nxt,to,co;
}G[M],H[M];
void Add(int a,int b,int c){
	G[++tt]=(edge){h[a],b,c};
	h[a]=tt;
}
void Add2(int a,int b,int c){
	H[++tt2]=(edge){h2[a],b,c};
	h2[a]=tt2;
}
int in[M];
queue<int>Q;
int q[M],qc;
int ans[M];
struct node{
	int x,len;
}dp[M];
int main(){
	freopen("number.in","r",stdin);
	freopen("number.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1,a,b,c;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		Add(b,a,c);Add2(a,b,c);in[a]++;
	}
	for(int i=1;i<=n;i++)
		if(in[i]==0)Q.push(i);
	while(!Q.empty()){
		int e=Q.front();Q.pop();
		q[++qc]=e;
		for(int i=h[e];i;i=G[i].nxt){
			int u=G[i].to;
			in[u]--;
			if(in[u]==0)Q.push(u);
		}
	}
	memset(ans,-1,sizeof(ans));
	for(int i=1;i<=qc;i++){
		int x=q[i];
		int las=0;
		dp[x].len=0;dp[x].x=0;
		for(int j=h2[x];j;j=H[j].nxt){
			int u=H[j].to,co=H[j].co;
			if(dp[u].len+1>dp[x].len){
				dp[x].len=dp[u].len+1;
				dp[x].x=(1LL*dp[u].x*29+co)%mod;
				las=co;
			}
			else if(dp[u].len+1==dp[x].len&&co<las){
				dp[x].len=dp[u].len+1;
				dp[x].x=(1LL*dp[u].x*29+co)%mod;
				las=co;
			}
		}
		ans[x]=dp[x].x;
	}
	for(int i=1;i<=n;i++){
		if(ans[i]==-1)puts("Infinity");
		else printf("%d\n",1LL*ans[i]*29%mod);
	}
	return 0;
}
