#include<bits/stdc++.h>
#define M 4000005
using namespace std;
int n;
struct Splay{
	int ch[M][2],sz[M],rt,tt,fa[M];
	char val[M];
	int stk[M],top;
	bool mark[M];
	void Print(int p){
		down(p);
		if(ch[p][0])Print(ch[p][0]);
		printf("%c",val[p]);
		if(ch[p][1])Print(ch[p][1]);	
	}
	void clear(){
		rt=tt=0;
		ch[0][0]=ch[0][1]=0;
		++tt;
		sz[tt]=2;val[tt]='a';mark[tt]=0;
		++tt;
		sz[tt]=1;val[tt]='a';mark[tt]=0;
		fa[2]=1;
		ch[1][1]=tt;rt=1;
	}
	void down(int p){
		if(mark[p]){
			swap(ch[p][0],ch[p][1]);
			mark[ch[p][0]]^=1;
			mark[ch[p][1]]^=1;
			mark[p]=0;
		}
	}
	void up(int p){
		sz[p]=sz[ch[p][0]]+sz[ch[p][1]]+1;
	}
	void build(int &p,int f,char* S,int l,int r){
		if(l>r)return;
		int mid=(l+r)>>1;
		p=++tt;
		val[p]=S[mid];
		fa[p]=f;sz[p]=1;mark[p]=0;
		build(ch[p][0],p,S,l,mid-1);
		build(ch[p][1],p,S,mid+1,r);
		up(p);
	}
	void Insert(int l,char *S){
		int L=find(l),R=find(l+1);
		splay(L,0);splay(R,L);
		down(L);down(R);
		int len=strlen(S);
		build(ch[R][0],R,S,0,len-1);
		up(R);up(L);
	}
	void rotate(int x){
		int y=fa[x],z=fa[y],k=ch[y][1]==x;
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
	void remove(int l,int r){
		int L=find(l-1),R=find(r+1);
		splay(L,0);splay(R,rt);
		down(L);down(R);
		ch[R][0]=0;
		up(R);up(L);
	}
	void reserve(int l,int r){
		int L=find(l-1),R=find(r+1);
		splay(L,0);splay(R,rt);
		mark[ch[R][0]]^=1;	
	}
}Tr;
char S[M];
char rd[25];
int cur=0;
int main(){
	scanf("%d",&n);
	cur=0;
	Tr.clear();
	while(n--){
		scanf("%s",rd);
		if(rd[0]=='M'){
			int x;scanf("%d",&x);
			cur=x;
		}
		else if(rd[0]=='I'){
			int x;scanf("%d",&x);
			getchar();
			for(int i=0;i<x;i++)S[i]=getchar();
			S[x]='\0';
			Tr.Insert(cur,S);
		}
		else if(rd[0]=='D'){
			int x;scanf("%d",&x);
			Tr.remove(cur+1,cur+x);	
		}
		else if(rd[0]=='R'){
			int x;scanf("%d",&x);
			Tr.reserve(cur+1,cur+x);					
		}
		else if(rd[0]=='G'){
			int x=Tr.find(cur+1);
			printf("%c\n",Tr.val[x]);	
		}
		else if(rd[0]=='P')cur--;
		else if(rd[0]=='N')cur++;
//		Tr.Print(Tr.rt);
//		puts("");
	}
	return 0;
}
