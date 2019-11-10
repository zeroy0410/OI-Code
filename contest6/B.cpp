#include<bits/stdc++.h>
#define M 50005
#define clr(x,y) memset(x,y,sizeof(x))
using namespace std;
int n,m,h[M],tot;
int mxa,mxb;
struct edge{
	int nxt,to,A,B;
}G[M<<2];
void Add(int a,int b,int A,int B){
	G[++tot]=(edge){h[a],b,A,B};
	h[a]=tot;
}
struct Edge{
	int u,v,A,B;
	bool operator < (const Edge& res) const{
		return A<res.A;
	}
}H[M<<1];
int ecnt;
struct P100{
	struct LCT{
		int ch[M<<1][2],val[M<<1],fa[M<<1],mx[M<<1],S[M<<1],E[M<<1];
		bool mark[M<<1];
		int stk[M<<1],top;
		int wk[M<<1];
		int ans;
		void clear(){
			clr(ch,0);clr(val,0);clr(fa,0);clr(mx,0);
			clr(mark,0);val[0]=-2e9;	
		}
		int check(int a,int b){
			if(val[a]<val[b])return b;
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
			mx[p]=check(mx[ch[p][0]],mx[ch[p][1]]);
			mx[p]=check(mx[p],p);
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
					(ch[z][1]==y^ch[y][1]==x)?rotate(x):rotate(y);
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
		void Link(int x,int y,int B){
			int z=wk[wk[0]--];
			val[z]=B;S[z]=x;E[z]=y;
			add(z,y);add(x,z);
		}
		void Cut(int x){
			int s=S[x],e=E[x];
			rm(s,x);rm(e,x);
			wk[++wk[0]]=x;
		}
		void solve(){
			clear();
			for(int i=0;i<=n;i++)val[i]=-2e9;
			for(int i=1;i<=(wk[0]=n);i++)wk[i]=i+n;
			ans=2e9;
			int A=0,B;
			for(int i=1;i<=ecnt;i++){
				A=H[i].A;B=H[i].B;
				int u=H[i].u,v=H[i].v;
				if(findroot(u)==findroot(v)){
					split(u,v);
					if(val[mx[u]]>B){
						Cut(mx[u]);
						Link(u,v,B);
					}
				}
				else {Link(u,v,B);}
				if(findroot(1)==findroot(n)){
					split(1,n);
					ans=min(ans,A+val[mx[1]]);
				}
			}
			if(ans==2e9)puts("-1");
			else printf("%d\n",ans);
		}
	}Tr;
	void solve(){
		ecnt=0;
		for(int i=1;i<=n;i++){
			for(int j=h[i];j;j=G[j].nxt){
				int u=G[j].to,A=G[j].A,B=G[j].B;
				if(u>i){
					H[++ecnt]=(Edge){i,u,A,B};	
				}
			}
		}
		sort(H+1,H+ecnt+1);
		Tr.solve();
	}
}p100;
int main(){
	freopen("forest.in","r",stdin);
	freopen("forest.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int a,b,A,B;
		scanf("%d%d%d%d",&a,&b,&A,&B);
		if(a==b)continue;
		Add(a,b,A,B);Add(b,a,A,B);
		mxa=max(mxa,A);mxb=max(mxb,B);
	}
	p100.solve();
	return 0;
}
