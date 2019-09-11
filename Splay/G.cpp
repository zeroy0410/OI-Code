#include<bits/stdc++.h>
#define M 500005
using namespace std;
int n,m,ct;
struct Splay{
	int ch[M][2],val[M],rt,tt,sz[M],fa[M];
	bool mark[M];
	int stk[M],top;
	void down(int p){
		if(mark[p]){
			swap(ch[p][0],ch[p][1]);
			mark[ch[p][0]]^=1;
			mark[ch[p][1]]^=1;
			mark[p]=0;
		}
	}
	void Print(int p){
		down(p);
		if(ch[p][0])Print(ch[p][0]);
		if(val[p]>=1&&val[p]<=n){
			printf("%d",val[p]);
			if(ct)printf(" ");					
			ct--;
		}
		if(ch[p][1])Print(ch[p][1]);
	}
	void up(int p){
		sz[p]=sz[ch[p][0]]+sz[ch[p][1]]+1;
	}
	void build(int &x,int f,int L,int R){
		if(L>R)return;
		int mid=(L+R)>>1;
		x=++tt;
		ch[x][0]=ch[x][1]=0;
		fa[x]=f;
		val[x]=mid;
		sz[x]=1;mark[x]=0;
		build(ch[x][0],x,L,mid-1);
		build(ch[x][1],x,mid+1,R);
		up(x);
	}
	void clear(){
		ch[0][0]=ch[0][1]=0;
		rt=tt=0;
	}
	void rotate(int x){
		int y=fa[x],z=fa[y],k=(ch[y][1]==x);
		down(y);down(x);
		if(z)ch[z][y==ch[z][1]]=x;fa[x]=z;
		ch[y][k]=ch[x][!k];if(ch[x][!k])fa[ch[x][!k]]=y;
		ch[x][!k]=y;fa[y]=x;
		up(y);up(x);
	}
	void splay(int x,int w){
		for(int y=x;;y=fa[y]){
			stk[++top]=y;
			if(y==w)break;
		}while(top)down(stk[top--]);
		while(fa[x]!=w){
			int y=fa[x],z=fa[y];
			if(z!=w)(y==ch[z][1]&&x==ch[y][1])?rotate(y):rotate(x);
			rotate(x);
		}
		if(!w)rt=x;
	}
	int find(int x){
		x++;
		int u=rt;
		while(1){
			down(u);
			if(sz[ch[u][0]]+1==x)return u;
			else if(sz[ch[u][0]]>=x)u=ch[u][0];
			else x-=sz[ch[u][0]]+1,u=ch[u][1];
		}
		return u;
	}
	void reserve(int l,int r){
		int L=find(l-1),R=find(r+1);
		splay(L,0);
		splay(R,rt);
		mark[ch[R][0]]^=1;
	}
	void cut_to(int l,int r,int p){
		int L=find(l-1),R=find(r+1);
		splay(L,0);splay(R,rt);
		int tmp=ch[R][0];
		fa[tmp]=0;ch[R][0]=0;
		up(R);up(L);
		L=find(p);R=find(p+1);
		splay(L,0);splay(R,rt);
		fa[tmp]=R;ch[R][0]=tmp;
		up(R);up(L);
	}
}Tr;
char S[15];
int main(){
	while(scanf("%d%d",&n,&m)&&!(n==-1&&m==-1)){
		ct=n-1;
		Tr.clear();
		Tr.build(Tr.rt,0,0,n+1);
		for(int i=1,l,r,p;i<=m;i++){
			scanf("%s",S);
			if(S[0]=='C'){
				scanf("%d%d%d",&l,&r,&p);
				Tr.cut_to(l,r,p);
			}
			else {
				scanf("%d%d",&l,&r);
				Tr.reserve(l,r);
			}
		}
	  	Tr.Print(Tr.rt);
		printf("\n");
	}
	return 0;
}
