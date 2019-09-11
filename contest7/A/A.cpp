#include<bits/stdc++.h>
#define M 1000005
#define LL long long
#define clr(x,y) memset(x,y,sizeof(x))
using namespace std;
const int mod=1e9+7;
int h[M],tot;
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tot]=(edge){h[a],b};
	h[a]=tot;	
}
int n;
void get_nxt(char *S,int *nxt){
	nxt[1]=nxt[2]=1;
	int len=strlen(S+1);
	for(int i=2;i<=len;i++){
		int j=nxt[i];
		while(j>1&&S[i]!=S[j])j=nxt[j];
		if(S[i]==S[j])j++;
		nxt[i+1]=j;	
	}
}
char S[M];
int nxt[M],f[M],ans[M];
struct BIT{
	int C[M];
	void add(int x,int d){
		x++;
		while(x<M){
			C[x]+=d;
			x+=(x&-x);	
		}
	}
	int sum(int x){
		x++;int res=0;
		while(x){
			res+=C[x];
			x-=(x&-x);
		}
		return res;
	}
}Tr;
void dfs(int x){
	ans[x]=Tr.sum(x/2);
	Tr.add(x,1);
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		dfs(u);
	}
	Tr.add(x,-1);
}
int main(){
	freopen("zoo.in","r",stdin);
	freopen("zoo.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		clr(h,0);tot=0;
		scanf("%s",S+1);
		get_nxt(S,nxt);
		int len=strlen(S+1);
		for(int i=1;i<=len;i++)f[i]=nxt[i+1]-1;
		for(int i=1;i<=len;i++)Add(f[i],i);
		dfs(0);
		int res=1;
		for(int i=1;i<=len;i++)res=1LL*res*ans[i]%mod;
		S[len+1]=0;
		printf("%d\n",res);
	}
	return 0;
}
