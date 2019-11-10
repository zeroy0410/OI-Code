#include<bits/stdc++.h>
#define M 100005
#define clr(x,y) memset(x,y,sizeof(x))
using namespace std;
struct LCT{
	//在LCT中fa可以表示轻边，ch表示的是重边 
	int ch[M][2],val[M],fa[M],mx[M];
	bool mark[M];
	int stk[M],top;
	void clear(){
		clr(ch,0);clr(val,0);clr(fa,0);clr(mx,0);clr(mark,0);
	}
	void up(int p){
		mx[p]=max(max(mx[ch[p][0]],mx[ch[p][1]]),val[p]);	
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
	void access(int x){//将x到根的路径转化为一条splay 
		for(int y=0;x;y=x,x=fa[x])
			splay(x),ch[x][1]=y,up(x);
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
}Tr;
int T,n;
int h[M],A[M],tot;
int mp[M],ln[M],fa[M][20],dep[M]; 
struct edge{
	int nxt,to,bh;
}G[M<<1];
void Add(int a,int b,int c){
	G[++tot]=(edge){h[a],b,c};
	h[a]=tot;
}
void dfs(int x,int f,int bh,int d){
	mp[bh]=x;ln[x]=bh;fa[x][0]=f;dep[x]=d;
	for(int i=h[x];i;i=G[i].nxt){
		int u=G[i].to,b=G[i].bh;
		if(u==f)continue;
		dfs(u,x,b,d+1);
	}
}
struct node{
	int a,b;
	bool op;
};
node LCA(int a,int b){
	int lb=b;
	int step=dep[b]-dep[a];
	for(int i=16;i>=0;i--)
		if(step&1<<i)b=fa[b][i];
	if(a==b){
		step--;
		for(int i=16;i>=0;i--)
			if(step&1<<i)lb=fa[lb][i];
		return (node){lb,lb,0};
	}
	for(int i=16;i>=0;i--)
		if(fa[a][i]!=fa[b][i])
			a=fa[a][i],b=fa[b][i];
	return (node){a,b,1};
}
char S[25];
int AA[M],BB[M];
int main(){
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	cin>>T;
	while(T--){
		scanf("%d",&n);
		clr(h,0);tot=0;Tr.clear();
		for(int i=1,a,b,c;i<n;i++){
			scanf("%d%d%d",&a,&b,&c);
			Add(a,b,i);Add(b,a,i);
			AA[i]=a;BB[i]=b;
			A[i]=c;	
		}
		dfs(1,0,0,0);
		for(int i=1;i<=n;i++)Tr.val[i]=A[ln[i]];
		for(int i=1;i<n;i++)Tr.link(AA[i],BB[i]);
		for(int j=1;j<=16;j++)
			for(int i=1;i<=n;i++)
				fa[i][j]=fa[fa[i][j-1]][j-1];
		while(scanf("%s",S)&&S[0]!='D'){
			if(S[0]=='C'){
				int i,ti;
				scanf("%d%d",&i,&ti);
				Tr.makeroot(mp[i]);
				Tr.val[mp[i]]=ti;
				Tr.up(mp[i]);
			}
			else {
				int a,b,mx=0;
				scanf("%d%d",&a,&b);
				if(dep[a]>dep[b])swap(a,b);
				if(a==b){printf("0\n");continue;}
				node e=LCA(a,b);
				if(e.op){
					Tr.split(a,e.a);
					mx=Tr.mx[e.a];
				}
				Tr.split(b,e.b);
//				cout<<"haha: "<<a<<' '<<e.a<<endl;
//				cout<<"haha: "<<b<<' '<<e.b<<endl;
//				cout<<mx<<endl;
				mx=max(mx,Tr.mx[e.b]);
				printf("%d\n",mx);
			}
		}
	}
	return 0;
}
