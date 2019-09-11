#include<bits/stdc++.h>
#define M 300005
#define LL long long
#define clr(x,y) memset(x,y,sizeof(x))
using namespace std;
const LL P=1e9+7;
int ch[M][2],fa[M],stk[M],top;
LL sum[M],val[M];
bool mark[M];
void reset(int x){
	val[x]=sum[x]=ch[x][0]=ch[x][1]=fa[x]=mark[x]=0;
}
void rs(int p){
	if(!p)return;
	mark[p]^=1;
	swap(ch[p][0],ch[p][1]);
}
struct que{int op,u,v;}Q[M];
struct edge{int nxt,to;}G[M<<1];
int h[M],tot;
int T,n,q,ans[M];
void Add(int a,int b){
	G[++tot]=(edge){h[a],b};h[a]=tot;
}
void down(int p){
	if(mark[p]){
		rs(ch[p][0]);rs(ch[p][1]);
		mark[p]=0;
	}
}
void up(int p){
	sum[p]=val[p]*sum[ch[p][0]]%P*sum[ch[p][1]]%P;
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
	for(int y=x;;y=fa[y]){
		stk[++top]=y;
		if(isrt(y))break;
	}while(top)down(stk[top--]);
	while(!isrt(x)){
		int y=fa[x],z=fa[y];
		if(!isrt(y))
			(ch[y][1]==x)^(ch[z][1]==y)?rotate(x):rotate(y);
		rotate(x);
	}
}
void access(int x){
	for(int y=0;x;y=x,x=fa[x])
		splay(x),ch[x][1]=y,up(x);
}
void makert(int x){
	access(x);splay(x);rs(x);
}
int findrt(int x){
	access(x);splay(x);down(x);
	while(ch[x][0])down(x=ch[x][0]);
	splay(x);return x;	
}
bool Link(int x,int y){
	makert(x);
	if(x==y||findrt(y)==x)return 0;
	fa[x]=y;return 1;
}
bool Cut(int x,int y){
    makert(x);
    if(x==y||findrt(x)!=findrt(y))return 0;
    if(fa[y]==x&&!ch[y][0]){
        fa[y]=ch[x][1]=0;up(x);
        return 1;
    }else return 0;
}
bool split(int x,int y){
	makert(x);
	if(findrt(y)!=x)return 0;
	access(y);
	splay(y);
	return 1;
}
void dfs(int x){
    for(int i=h[x];i;i=G[i].nxt){
        int y=G[i].to;
        if(Q[y].op==1){
            bool f=Link(Q[y].u,Q[y].v);
            dfs(y);
            if(f)Cut(Q[y].u,Q[y].v);
        }
        else if(Q[y].op==2){
            bool f=Cut(Q[y].u,Q[y].v);
            dfs(y);
            if(f)Link(Q[y].u,Q[y].v);
        }
        else if(Q[y].op==4){
            ans[y]=split(Q[y].u,Q[y].v)?sum[Q[y].v]:0;
            dfs(y);
        }
        else if(Q[y].op==5){
            int tmp=Q[y].v;
            splay(Q[y].u),Q[y].v=val[Q[y].u],val[Q[y].u]=tmp,up(Q[y].u);
            dfs(y);
            splay(Q[y].u),val[Q[y].u]=Q[y].v,up(Q[y].u);
        }else dfs(y);
    }
}
int main(){
	freopen("data.in","r",stdin);
	freopen("test.out","w",stdout);
	for(int _=(scanf("%d",&_),_);_;_--){
		clr(h,0);tot=0;sum[0]=1;
		scanf("%d%d",&n,&q);
		for(int i=1,a;i<=n;i++){
			scanf("%d",&a);
			reset(i);
			val[i]=sum[i]=a*(a-1)/2%P;
		}
		for(int i=1;i<=q;i++){
			scanf("%d%d",&Q[i].op,&Q[i].u);
			if(Q[i].op!=3){
				scanf("%d",&Q[i].v);
				if(Q[i].op==5)Q[i].v=Q[i].v*(Q[i].v-1)/2%P;
				Add(i-1,i);
			}
			else Add(Q[i].u,i);
		}
		dfs(0);
		for(int i=1;i<=q;i++)if(Q[i].op==4)printf("%d\n",ans[i]);
	}
	return 0;
}
