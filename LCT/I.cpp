#include<bits/stdc++.h>
#define M 200005
using namespace std;
int n,m,A[M];
struct LCT{
	int ch[M][2],fa[M];
	bool isrt(int x){return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;}
	void rotate(int x){
		int y=fa[x],z=fa[y],k=ch[y][1]==x;
		if(!isrt(y))ch[z][ch[z][1]==y]=x;fa[x]=z;
		ch[y][k]=ch[x][!k];fa[ch[x][!k]]=y;
		ch[x][!k]=y;fa[y]=x;
	}
	void splay(int x){
		while(!isrt(x)){
			int y=fa[x],z=fa[y];
			if(!isrt(y))
				(ch[z][1]==y^ch[y][1]==x)?rotate(x):rotate(y);
			rotate(x);
		}
	}
	void access(int x){
		for(int y=0;x;y=x,x=fa[x])splay(x),ch[x][1]=y;	
	}
	int findrt(int x){
		access(x),splay(x);
		while(ch[x][0])x=ch[x][0];
		return x;
	}
	void Link(int x){
		if(!A[x])return;
		if(findrt(A[x])==x)return;
		access(x);splay(x);fa[x]=A[x];
	}
	void Cut(int x){
		if(!A[x])return;
		int p=findrt(A[x]);if(p==x)return;
		access(x);access(A[x]);splay(x);fa[x]=0;
		if(A[p])Link(p);
	}
	void query(int x){
		x=findrt(x);
		if(A[x])puts("-1");
		else printf("%d\n",x);
	}
}Tr;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]),Tr.Link(i);
	while(m--){
		int op,x;
		scanf("%d%d",&op,&x);
		if(op==1){
			Tr.Cut(x);
			scanf("%d",&A[x]);
			Tr.Link(x);
		}
		else Tr.query(x);
	}
	return 0;
}
