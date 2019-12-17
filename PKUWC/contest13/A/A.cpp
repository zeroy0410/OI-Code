#include<bits/stdc++.h>
#define M 4000005
#define fish(x) (x<<1)
#define ifsh(x) (x<<1|1)
using namespace std;
int n,h[M],tt=1;
string S[M];
bool cmp(string a,string b){return a.length()<b.length();}
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tt]=(edge){h[a],b}; h[a]=tt;
	G[++tt]=(edge){h[b^1],(a^1)}; h[b^1]=tt;
}
//2-SAT
int dfn[M],low[M],tot,stk[M],top,Cnt,be[M];
bool vis[M];
int T;
void tarjan(int x){
	dfn[x]=low[x]=++tot;
	vis[x]=1;stk[++top]=x;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(!dfn[u]){tarjan(u);low[x]=min(low[x],low[u]);}
		else if(vis[u])low[x]=min(low[x],dfn[u]);
	}
	if(dfn[x]==low[x]){
		++Cnt;int y;
		do{
			y=stk[top--];
			be[y]=Cnt;
			vis[y]=0;
		}while(y!=x);
	}
}
struct Trie{
	int ch[M][2];
	void Insert(string s,int p){
		int u=0,f=0;
		for(int i=0;i<s.length();i++){
			int c=s[i]-'0';
			if(!ch[u][c]){
				ch[u][c]=++T;
				Add(ifsh(u),ifsh(T));
			}
			f=u;u=ch[u][c];
		}
		++T;
		Add(ifsh(u),ifsh(T));
		Add(p,fish(u));Add(p,ifsh(T));
		ch[f][ch[f][1]==u]=T;
	}
}Tr;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)cin>>S[i];
	sort(S+1,S+n+1,cmp);T=n;
	for(int i=1;i<=n;i++){
		bool fl=1;
		for(int j=0;j<S[i].length();j++){
			if(S[i][j]=='?'){
				S[i][j]='0';Tr.Insert(S[i],fish(i));
				S[i][j]='1';Tr.Insert(S[i],ifsh(i));
				fl=0;break;
			}
		}
		if(fl){Add(ifsh(i),fish(i));Tr.Insert(S[i],fish(i));}
	}
	for(int i=1;i<=ifsh(T);i++)if(!dfn[i])tarjan(i);
	bool fl=1;
	for(int i=1;i<=T;i++)
		if(be[fish(i)]==be[ifsh(i)]){
			fl=0;
			break;
		}
	puts(fl?"YES":"NO");
	return 0;
}
