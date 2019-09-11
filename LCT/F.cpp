#include<bits/stdc++.h>
#define M 50005 
#define clr(x,y) memset(x,y,sizeof(x))
#define tomax(x,y) if(x<y)x=y
#define tomin(x,y) if(x>y)x=y 
#define max4(x,y,z,w) max(max(x,y),max(z,w))
#define min3(x,y,z) min(min(x,y),z)
#define max3(x,y,z) max(max(x,y),z)
#define INF 0x3f3f3f3f
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
	int ch[M][2],val[M],add[M],mx[2][M],mxx[M],mii[M],fa[M];
	bool mark[M];
	int stk[M],top;
	void reset(int x,int y){
		if(!x)return;
		val[x]+=y;add[x]+=y;
		mxx[x]+=y;mii[x]+=y;
	}
	void rs(int p){
		if(!p)return;
		mark[p]^=1;
		swap(ch[p][0],ch[p][1]);
		swap(mx[0][p],mx[1][p]);
	}
	void clear(){
		clr(ch,0);clr(val,0);clr(add,0);clr(mx,0);
		clr(mark,0);clr(mii,67);clr(mxx,0);clr(fa,0);
	}
	void up(int p){
        mxx[p]=max(max(mxx[ch[p][0]],mxx[ch[p][1]]),val[p]);
        mii[p]=min(min(mii[ch[p][0]],mii[ch[p][1]]),val[p]);
        mx[0][p]=mx[1][p]=0;
        if(ch[p][0]){
            tomax(mx[0][p],val[p]-mii[ch[p][0]]);
            tomax(mx[1][p],mxx[ch[p][0]]-val[p]);
            tomax(mx[0][p],mx[0][ch[p][0]]);
            tomax(mx[1][p],mx[1][ch[p][0]]);
        }
        if(ch[p][1]){
            tomax(mx[1][p],val[p]-mii[ch[p][1]]);
            tomax(mx[0][p],mxx[ch[p][1]]-val[p]);
            tomax(mx[0][p],mx[0][ch[p][1]]);
            tomax(mx[1][p],mx[1][ch[p][1]]);                
        }
        if(ch[p][0]&&ch[p][1]){
            tomax(mx[0][p],mxx[ch[p][1]]-mii[ch[p][0]]);
            tomax(mx[1][p],mxx[ch[p][0]]-mii[ch[p][1]]);
        }
    }
	void down(int p){
		if(mark[p]){
			rs(ch[p][0]);rs(ch[p][1]);
			mark[p]=0;
		}
		if(add[p]){
			reset(ch[p][0],add[p]);
			reset(ch[p][1],add[p]);
			add[p]=0;
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
				(ch[z][1]==y&&ch[y][1]==x)?rotate(y):rotate(x);
			rotate(x);
		}
	}
	void Print(int p){
		down(p);
		if(ch[p][0])Print(ch[p][0]);
		printf("%d %d %d %d %d\n",ch[p][0],ch[p][1],val[p],mx[0][p],mx[1][p]);
		if(ch[p][1])Print(ch[p][1]);
	}
	void access(int x){//将x到根的路径转化为一条splay 
		for(int y=0;x;y=x,x=fa[x])
			splay(x),ch[x][1]=y,up(x);
	}
	void makeroot(int x){//将x转化为原树的根
		access(x);splay(x);
		rs(x);
	}
	int findroot(int x){//寻找x所在子树的根 
		access(x),splay(x),down(x);
		while(ch[x][0])down(x=ch[x][0]);
		splay(x);return x;	
	}
	void split(int x,int y){//将x--y的路径拉出来作为一个splay 
		makeroot(x);access(y);splay(y);	
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
int T,n,Q;
int main(){
	scanf("%d",&T);
	while(T--){
		Tr.clear();clr(h,0);tot=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)scanf("%d",&Tr.val[i]),Tr.mxx[i]=Tr.mii[i]=Tr.val[i];
		for(int i=1,a,b;i<n;i++){
			scanf("%d%d",&a,&b);
			Add(a,b);Add(b,a);
		}
		dfs(1,0);
		scanf("%d",&Q);
		for(int _=1,a,b,v;_<=Q;_++){
			scanf("%d%d%d",&a,&b,&v);Tr.split(a,b);
//			Tr.Print(b);
			printf("%d\n",Tr.mx[0][b]);
			Tr.reset(b,v);
		}
	}
	return 0;
}
