#include<bits/stdc++.h>
#define M 100005
using namespace std;
const int P=1e4+7;
int inv[M],Ifa[M];
int n;
struct node{
	int k,b;
	node operator + (const node& res)const{
		return (node){k*res.k%P,(res.k*b%P+res.b)%P};
	}
}val[M],sum[M];
struct LCT{
	int ch[M][2],fa[M];
	void up(int p){
		sum[p]=sum[ch[p][0]]+val[p]+sum[ch[p][1]];
	}
	void create(int x,node d){
		ch[x][0]=ch[x][1]=fa[x]=0;
		val[x]=sum[x]=d;
	}
	bool isrt(int x){
		return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
	}
	void rotate(int x){
		int y=fa[x],z=fa[y],k=ch[y][1]==x;
		if(!isrt(y))ch[z][ch[z][1]==y]=x;fa[x]=z;
		ch[y][k]=ch[x][!k];fa[ch[x][!k]]=y;
		ch[x][!k]=y;fa[y]=x;
		up(y);up(x);
	}
	void splay(int x){
		while(!isrt(x)){
			int y=fa[x],z=fa[y];
			if(!isrt(y))
				(ch[y][1]==x^ch[z][1]==y)?rotate(x):rotate(y);
			rotate(x);
		}
	}
	void access(int x){
		for(int y=0;x;y=x,x=fa[x])
			splay(x),ch[x][1]=y,up(x);
	}
	int findrt(int x){
		access(x);splay(x);
		while(ch[x][0])x=ch[x][0];
		splay(x);return x;
	}
	bool link(int x,int y){
		splay(x);
		if(findrt(y)==x)return 0;
		fa[x]=y;
		return 1;
	}
	bool cut(int x){
		access(x),splay(x);
		if(!ch[x][0])return 0;
		fa[ch[x][0]]=0;ch[x][0]=0;
		up(x);
		return 1;
	}
	void update(int x,node d){
		val[x]=sum[x]=d;
		up(x);
		splay(x);
	}
	node query(int x){
		access(x),splay(x);
		return sum[x];
	}
	void Link(int x,int y){
		if(!link(x,y))Ifa[x]=y;
	}
	void Cut(int x){
		int y=findrt(x);
		if(!cut(x)){Ifa[x]=0;return;}
		if(link(y,Ifa[y]))Ifa[y]=0;
	}
	int solve(int x){
		int y=findrt(x),z=Ifa[y];
		node f=query(z);
		if(f.k==1)return f.b==0?-2:-1;
		int vl=f.b*inv[(P+1-f.k)%P]%P;
		f=query(x);
		return (f.k*vl+f.b)%P;
	}
}Tr;
int main(){
	inv[0]=inv[1]=1;
	for(int i=2;i<=P-1;i++)inv[i]=(P-P/i)*inv[P%i]%P;
	scanf("%d",&n);
	for(int i=0;i<=n;i++)Tr.create(i,(node){1,0});
	for(int i=1;i<=n;i++){
		int k,p,b;
		scanf("%d%d%d",&k,&p,&b);
		Tr.update(i,(node){k,b});
		Tr.Link(i,p);
	}
	int q;
	scanf("%d",&q);
	while(q--){
		char op[5];int a,k,p,b;
		scanf("%s",op);
		if(op[0]=='A'){
			scanf("%d",&a);
			printf("%d\n",Tr.solve(a));
		}
		else {
			scanf("%d%d%d%d",&a,&k,&p,&b);
			Tr.update(a,(node){k,b});
			Tr.Cut(a);
			Tr.Link(a,p);
		}
	}
	return 0;
}
