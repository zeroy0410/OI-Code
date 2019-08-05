#include<bits/stdc++.h>
#define M 300005
#define clr(x,y) memset(x,y,sizeof(x))
using namespace std;
int h[M],tot;
struct edge{
	int nxt,to;
}G[M<<1];
void Add(int a,int b){
	G[++tot]=(edge){h[a],b};
	h[a]=tot;
}
struct LCT{
	int mx[M],ch[M][2],val[M],add[M],fa[M];
	bool mark[M];
	int stk[M],top;
	void clear(){
		clr(mx,0);clr(ch,0);clr(val,0);
		clr(add,0);clr(mark,0);clr(fa,0);
	}
	void down(int p){
		if(mark[p]){
			mark[ch[p][0]]^=1;
			mark[ch[p][1]]^=1;
			swap(ch[p][0],ch[p][1]);
			mark[p]=0;
		}
		if(add[p]){
			if(ch[p][0]){
				mx[ch[p][0]]+=add[p];
				val[ch[p][0]]+=add[p];
				add[ch[p][0]]+=add[p];
			}
			if(ch[p][1]){
				mx[ch[p][1]]+=add[p];
				val[ch[p][1]]+=add[p];
				add[ch[p][1]]+=add[p];
			}
			add[p]=0;
		}
	}
	void up(int p){
		mx[p]=max(max(mx[ch[p][0]],mx[ch[p][1]]),val[p]);	
	}
	bool isrt(int x){
		return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
	}
	void rotate(int x){
		int y=fa[x],z=fa[y],k=ch[y][1]==x;
		down(y);down(x);
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
	void makert(int x){
		access(x);splay(x);
		mark[x]^=1;	
	}
	int findrt(int x){
		access(x);splay(x);down(x);
		while(ch[x][0])down(x=ch[x][0]);
		splay(x);return x;
	}
	void link(int x,int y){
		makert(x);fa[x]=y;
	}
	void cut(int x,int y){
		makert(x);access(y);splay(y);
		fa[ch[y][0]]=0;ch[y][0]=0;up(y);
	}
	void split(int x,int y){
		makert(x);access(y);splay(y);	
	}
}Tr;
void dfs(int x,int f){
	Tr.fa[x]=f;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to;
		if(u==f)continue;
		dfs(u,x);
	}
}
int n,m;
int main(){
	while(~scanf("%d",&n)){
		Tr.clear();tot=0;
		memset(h,0,sizeof(h));
		for(int i=1,a,b;i<n;i++){
			scanf("%d%d",&a,&b);
			Add(a,b);Add(b,a);
		}
		for(int i=1;i<=n;i++)
			scanf("%d",&Tr.val[i]),Tr.mx[i]=Tr.val[i];
		dfs(1,0);
		scanf("%d",&m);
		for(int i=1,op,x,y,w;i<=m;i++){
			scanf("%d",&op);
			if(op==1){
				scanf("%d%d",&x,&y);
				if(Tr.findrt(y)==Tr.findrt(x)){puts("-1");continue;}
				Tr.link(x,y);
			}
			else if(op==2){
				scanf("%d%d",&x,&y);
				if(x==y||Tr.findrt(x)!=Tr.findrt(y)){puts("-1");continue;}
				Tr.cut(x,y);
			}
			else if(op==3){
				scanf("%d%d%d",&w,&x,&y);
				if(Tr.findrt(y)!=Tr.findrt(x)){puts("-1");continue;}
				Tr.split(x,y);
				Tr.add[y]+=w;
				Tr.mx[y]+=w;
				Tr.val[y]+=w;
			}
			else {
				scanf("%d%d",&x,&y);
				if(Tr.findrt(y)!=Tr.findrt(x)){puts("-1");continue;}
				Tr.split(x,y);
				printf("%d\n",Tr.mx[y]);
			}
		}
		puts("");
	}
	return 0;
}
