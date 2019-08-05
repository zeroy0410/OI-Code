#include<bits/stdc++.h>
#define M 50005
using namespace std;
int f[M];
struct LCT{
	int ch[M][2],fa[M];
	bool mark[M];
	int stk[M],top;
	void clear(){
		memset(ch,0,sizeof(ch));
		memset(fa,0,sizeof(fa));
		memset(mark,0,sizeof(mark));	
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
		return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;	
	}
	void rotate(int x){
		int y=fa[x],z=fa[y],k=ch[y][1]==x;
		down(y);down(x);
		if(!isroot(y))ch[z][ch[z][1]==y]=x;fa[x]=z;
		ch[y][k]=ch[x][!k];if(ch[x][!k])fa[ch[x][!k]]=y;
		ch[x][!k]=y;fa[y]=x;
	}
	void splay(int x){
		for(int y=x;;y=fa[y]){
			stk[++top]=y;
			if(isroot(y))break;
		}while(top)down(stk[top--]);
		while(!isroot(x)){
			int y=fa[x],z=fa[y];
			if(!isroot(y))
				(ch[z][1]==y&&ch[y][1]==x)?rotate(y):rotate(x);
			rotate(x);
		}
	}
	void access(int x){
		for(int y=0;x;y=x,x=fa[x])
			splay(x),ch[x][1]=y;	
	}
	int findroot(int x){
		access(x);splay(x);down(x);
		while(ch[x][0])down(x=ch[x][0]);
		return x;
	}
	void cut(int x){
		access(f[x]);splay(x);fa[x]=0;
	}
	void link(int x,int y){
		cut(x);
		if(!y)return;
		if(findroot(y)!=x)fa[x]=y,f[x]=y;
		else splay(x),fa[x]=f[x];
	}
}Tr; 
int n,m;
char S[15];
int main(){
	bool fs=1;
	while(~scanf("%d",&n)){
		if(!fs)puts("");
		fs=0;
		Tr.clear();
		for(int i=1;i<=n;i++){
			scanf("%d",&f[i]);
			Tr.fa[i]=f[i];
		}
		scanf("%d",&m);
		for(int i=1,x,y;i<=m;i++){
			scanf("%s",S);
			if(S[0]=='Q'){
				scanf("%d",&x);
				printf("%d\n",Tr.findroot(x));
			}
			else {
				scanf("%d%d",&x,&y);
				Tr.link(x,y);
			}
		}
	}
	return 0;
}
