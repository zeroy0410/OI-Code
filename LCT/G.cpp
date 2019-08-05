#include<bits/stdc++.h>
#define M 100005
#define clr(x,y) memset(x,y,sizeof(y))
#define LL long long
using namespace std;
int n;
LL ans[M],res=0;
vector<int>son[M];
void Init(){
	son[1].push_back(0);
	for(int i=1;i<M;i++)
		for(int j=i+i;j<M;j+=i)
			son[j].push_back(i);
}
struct LCT{
	int ch[M<<1][2],val[M<<1],fa[M<<1],mi[M<<1],S[M<<1],E[M<<1];
	bool mark[M<<1];
	int stk[M<<1],top;
	int wk[M<<1];
	void clear(){
		clr(ch,0);clr(val,0);clr(fa,0);clr(mi,0);
		clr(mark,0);val[0]=1e9;	
	}
	int check(int a,int b){
		if(val[a]>val[b])return b;
		return a;	
	}
	void rs(int p){
		if(!p)return;
		mark[p]^=1;
		swap(ch[p][0],ch[p][1]);
	}
	void down(int p){
		if(mark[p]){
			rs(ch[p][0]);rs(ch[p][1]);
			mark[p]=0;	
		}
	}
	void up(int p){
		mi[p]=check(mi[ch[p][0]],mi[ch[p][1]]);
		mi[p]=check(mi[p],p);
	}
	bool isrt(int x){
		return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;	
	}
	void rotate(int x){
		int y=fa[x],z=fa[y],k=ch[y][1]==x;
		if(!isrt(y))ch[z][ch[z][1]==y]=x;fa[x]=z;
		ch[y][k]=ch[x][!k];if(ch[x][!k])fa[ch[x][!k]]=y;
		ch[x][!k]=y;fa[y]=x;
		up(y);up(x);
	}
void splay(int x){
		for(int y=x;;y=fa[y]){
			stk[++top]=y;
			if(isrt(y))break;
		}while(top)down(stk[top--]);
		while(!isrt(x)){
			int y=fa[x],z=fa[y];
			if(!isrt(y))
				(ch[z][1]==y&&ch[y][1]==x)?rotate(y):rotate(x);
			rotate(x);
		}
	}
	void access(int x){
		for(int y=0;x;y=x,x=fa[x])
			splay(x),ch[x][1]=y,up(x);
	}
	void makeroot(int x){
		access(x);splay(x);rs(x);
	}
	int findroot(int x){
		access(x),splay(x),down(x);
		while(ch[x][0])down(x=ch[x][0]);
		splay(x);return x;
	}
	void split(int x,int y){
		makeroot(x);access(y);splay(x);	
	}
	void add(int x,int y){
		makeroot(x);
		if(!val[1])exit(0);
		splay(x);fa[x]=y;	
	}
	void rm(int x,int y){
		makeroot(x);access(y);splay(x);	
		ch[x][1]=fa[y]=0;
		up(x);
	}
	void Link(int x,int y){
		int z=wk[wk[0]--];
		val[z]=y;res+=y;S[z]=x;E[z]=y;
		add(z,y);add(x,z);
	}
	void Cut(int x){
		int s=S[x],e=E[x];
		res-=val[x];
		rm(s,x);rm(e,x);
		wk[++wk[0]]=x;
	}
	void solve(){
		for(int i=0;i<=n;i++)val[i]=2e9;
		for(int i=1;i<=(wk[0]=n);i++)wk[i]=i+n;
		ans[1]=0;
		for(int i=2;i<=n;i++){
			int sz=son[i].size();
			Link(i,son[i][sz-1]);
			for(int j=0;j<sz-1;j++){
				int y=son[i][j];
				split(i,y);
				Cut(mi[i]);
				Link(i,y);
			}
			ans[i]=res;
		}
	}
}Tr;
int main(){
	Init();n=1e5;
	Tr.solve();
	while(~scanf("%d",&n))printf("%d\n",ans[n]);
	return 0;
}
