#include<bits/stdc++.h>
#define M 10005
using namespace std;
struct LCT{
	//在LCT中fa可以表示轻边，ch表示的是重边 
	int ch[M][2],val[M],fa[M];
	bool mark[M];
	int stk[M],top;
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
	void access(int x){//将x到根的路径转化为一条splay 
		for(int y=0;x;y=x,x=fa[x])
			splay(x),ch[x][1]=y;
	}
	void makeroot(int x){//将x转化为原树的根
		access(x);splay(x);
		mark[x]^=1;
	}
	int findroot(int x){//寻找x所在子树的根 
		access(x),splay(x),down(x);
		while(ch[x][0])down(x=ch[x][0]);
		splay(x);return x;	
	}
	void split(int x,int y){//将x--y的路径拉出来作为一个splay 
		makeroot(x);access(y);splay(y);	
	}
	void link(int x,int y){//连一条轻边 
		makeroot(x);
		if(findroot(y)!=x)fa[x]=y;	
	}
	void cut(int x,int y){//将x--y之间的边断开
		makeroot(x);
		if(findroot(y)==x&&fa[y]==x&&!ch[y][0])
			fa[y]=ch[x][1]=0;
	}
}Tr;
int n,m;
char S[15];
int main(){
	cin>>n>>m;
	for(int i=1,x,y;i<=m;i++){
		scanf("%s%d%d",S,&x,&y);
		if(S[0]=='Q'){
			puts(Tr.findroot(x)==Tr.findroot(y)?"Yes":"No");
		}
		else if(S[0]=='C'){
			Tr.link(x,y);
		}
		else Tr.cut(x,y);
	}
	return 0;	
}
