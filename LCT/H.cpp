#include<bits/stdc++.h>
#define M 200005
#define clr(x,y) memset(x,y,sizeof(x))
#define fi first
#define se second
using namespace std;
int n,m,q,ans[M];
struct LCT{
	int ch[M<<1][2],val[M<<1],fa[M<<1],mi[M<<1],stk[M<<1],top;
	bool mark[M<<1];
	int check(int a,int b){
		return val[a]>val[b]?b:a;	
	}
	void clear(){
		clr(ch,0);clr(val,0);clr(fa,0);clr(mi,0);
		clr(mark,0);
		val[0]=1e9;
		for(int i=1;i<=n+m;i++)mi[i]=i;
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
				(ch[y][1]==x&&ch[z][1]==y)?rotate(y):rotate(x);
			rotate(x);	
		}
	}
	void access(int x){
		for(int y=0;x;y=x,x=fa[x])
			splay(x),ch[x][1]=y,up(x);	
	}
	int findrt(int x){
		access(x),splay(x),down(x);
		while(ch[x][0])down(x=ch[x][0]);
		splay(x);return x;
	}
	void makert(int x){
		access(x);splay(x);rs(x);	
	}
	void Link(int x,int y){
		makert(x);fa[x]=y;access(x);
	}
	void Cut(int x,int y){
		makert(x);access(y);splay(y);
		ch[y][0]=fa[x]=0;up(y);
	}
	int query_mi(int x,int y){
		makert(x);access(y);splay(y);
		return mi[y];
	}
}Tr;
struct BIT{
	int C[M];
	void clear(){
		memset(C,0,sizeof(C));
	}
	void add(int x,int d){
		while(x<=n){C[x]+=d;x+=(x&-x);}
	}
	int sum(int x){
		int res=0;
		while(x)res+=C[x],x-=(x&-x);	
		return res;
	}
}TT;
struct que{
	int L,R,id;
	bool operator < (const que& res)const{
		return R<res.R;
	}
}Q[M];
typedef pair<int,int>pii;
pii edge[M];
int main(){
	while(~scanf("%d%d%d",&n,&m,&q)){
		TT.clear();Tr.clear();
		for(int i=1;i<=n;i++)Tr.val[i]=1e9;
		for(int i=0,a,b;i<m;i++){
			scanf("%d%d",&a,&b);
			if(a>b)swap(a,b);
			edge[i]=pii(b,a);
		}
		sort(edge,edge+m);
		for(int i=0;i<q;i++){
			scanf("%d%d",&Q[i].L,&Q[i].R);
			Q[i].id=i;	
		}
		sort(Q,Q+q);
		for(int i=0,j=0,tot=0;i<q;i++){
			while(j<m&&edge[j].fi<=Q[i].R){
				int u=edge[j].fi,v=edge[j].se,id=++j+n;
				Tr.val[id]=v;
				if(Tr.findrt(u)!=Tr.findrt(v)){
					Tr.Link(u,id);
					Tr.Link(v,id);
					TT.add(v,1);
					++tot;
				}
				else{
					int mi=Tr.query_mi(u,v);
					if(Tr.val[mi]<Tr.val[id]){
						Tr.Cut(mi,edge[mi-n-1].fi);
						Tr.Cut(mi,edge[mi-n-1].se);
						TT.add(edge[mi-n-1].se,-1);
						Tr.Link(u,id);
						Tr.Link(v,id);
						TT.add(v,1);
					}
				}
			}
			ans[Q[i].id]=n-(tot-TT.sum(Q[i].L-1));
		}
		for(int i=0;i<q;i++)
			printf("%d\n",ans[i]);
	}
	return 0;
}
