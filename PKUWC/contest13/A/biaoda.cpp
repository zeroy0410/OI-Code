#include<bits/stdc++.h>
using namespace std;
#define A(x) (x<<1)
#define B(x) (x<<1|1)
const int N=4e6+10;
struct edge{int to,nxt;}e[N<<1];
int h[N];
void adde(int u,int v){static int tot=0;e[++tot]=(edge){v,h[u]};h[u]=tot;e[++tot]=(edge){u^1,h[v^1]};h[v^1]=tot;}
int n,id[N];
string s[N];
int tot=0,ch[N][2];
int tim=0,scc=0,dfn[N],low[N],st[N],bel[N],top=0;
bool in[N];
void dfs(int u,int fa){
	dfn[u]=low[u]=++tim;
	st[++top]=u;in[u]=1;
	for(int i=h[u];i;i=e[i].nxt){
		int v=e[i].to; if(v==fa) continue;
		if(!dfn[v]) dfs(v,u),low[u]=min(low[u],low[v]);
		else if(in[v]) low[u]=min(low[u],dfn[v]);
	}
	if(low[u]==dfn[u]){
		int v;++scc;
		do{v=st[top--];bel[v]=scc;in[v]=0;}while(u!=v);
	}
}
void insert(string s,int p){
	int u=0,f=0;
	for(int i=0;i<s.length();i++){
		int c=s[i]-'0';
		if(!ch[u][c]) ch[u][c]=++tot,adde(B(u),B(tot));
		f=u;u=ch[u][c];
	}
	++tot;
	adde(B(u),B(tot));
	adde(p,A(u));adde(p,B(tot));
	ch[f][ch[f][1]==u]=tot;
}
bool cmp(int a,int b) {return s[a].length()<s[b].length();}
int main(){
	cin>>n;tot=n;
	for(int i=1;i<=n;i++) cin>>s[i],id[i]=i;
	sort(id+1,id+n+1,cmp);
	for(int i=1;i<=n;i++) {
		int x=id[i],p;
		for(p=0;p<s[x].length();p++)
			if(s[x][p]=='?') {
				s[x][p]='0';insert(s[x],A(x));
				s[x][p]='1';insert(s[x],B(x));
				break;
			}
		if(p==s[x].length()) adde(B(x),A(x)),insert(s[x],A(x));
	}
	for(int i=0;i<=B(tot);i++) if(!dfn[i]) dfs(i,0);
	cout<<bel[A(1)]<<' '<<bel[B(1)]<<endl;
	for(int i=0;i<=tot;i++) if(bel[A(i)]==bel[B(i)]) return puts("NO"),0;
	puts("YES");
	return 0;
}

