#include<bits/stdc++.h>
#define M 200005
using namespace std;
struct LCT{
	int val[M],sz[M],fa[M],ch[M][2];
	bool mark[M];
	int stk[M],top;
	void up(int p){
		sz[p]=sz[ch[p][0]]+sz[ch[p][1]]+1;
	}
	void down(int p){
		if(mark[p]){
			mark[ch[p][0]]^=1;
			mark[ch[p][1]]^=1;
			swap(ch[p][0],ch[p][1]);
			mark[p]=0;
		}
	}
	bool isroot(int x){
		return (ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x);	
	}
	void rotate(int x){
		int y=fa[x],z=fa[y],k=ch[y][1]==x;
		down(y);down(x);
		if(!isroot(y))ch[z][ch[z][1]==y]=x;fa[x]=z;
		ch[y][k]=ch[x][!k];if(ch[x][!k])fa[ch[x][!k]]=y;
		ch[x][!k]=y;fa[y]=x;
		up(y);up(x);
	}
	void splay(int x){
		for(int y=x;;y=fa[y]){
			stk[++top]=y;
			if(isroot(y))break;
		}while(top)down(stk[top--]);
		while(!isroot(x)){
			int y=fa[x],z=fa[y];
			if(!isroot(y))
				(ch[y][1]==x&&ch[z][1]==y)?rotate(y):rotate(x);
			rotate(x);
		}
	}
	void access(int x){
		for(int y=0;x;y=x,x=fa[x])
			splay(x),ch[x][1]=y,up(x);	
	}
	void makeroot(int x){
		access(x);splay(x);
		mark[x]^=1;	
	}
	int findroot(int x){
		access(x);splay(x);down(x);
		while(ch[x][0])down(x=ch[x][0]);
		splay(x);return x;
	}
	void split(int x,int y){
		makeroot(x);access(y);splay(y);
	}
	void link(int x,int y){
		makeroot(x);
		if(findroot(y)!=x)fa[x]=y;
	}
	void cut(int x,int y){
		makeroot(x);
		if(findroot(y)==x&&fa[y]==x&&!ch[y][0]){
			fa[y]=ch[x][1]=0;
			up(x);
		}
	}
}Tr;
int n,m;
int A[M];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n+1;i++)Tr.sz[i]=1;
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1;i<=n;i++){
		if(i+A[i]<=n)Tr.link(i,i+A[i]);
		else Tr.link(i,n+1);
	}
	scanf("%d",&m);
	for(int i=1,op,x,y;i<=m;i++){
		scanf("%d",&op);
		if(op==1){
			scanf("%d",&x);x++;
			Tr.split(x,n+1);
			printf("%d\n",Tr.sz[n+1]);
		}
		else {
			scanf("%d%d",&x,&y);x++;
			if(x+A[x]<=n)Tr.cut(x,x+A[x]);
			else Tr.cut(x,n+1);
			A[x]=y;
			if(x+A[x]<=n)Tr.link(x,x+A[x]);
			else Tr.link(x,n+1);
		}
	}
	return 0;
}
