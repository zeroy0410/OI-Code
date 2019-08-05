#include<bits/stdc++.h>
#define M 100005
#define LL long long
#define clr(x,y) memset(x,y,sizeof(x))
using namespace std;
const int P=1e9+7;
int n,m;
struct LCT{
	int ch[M][2],fa[M];
	LL sum[M],isum[M],val[M],Sum[M],ans[M];
	int stk[M],top;
	bool mark[M];
	void newnode(int x,int d){
		ch[x][0]=ch[x][1]=fa[x]=mark[x]=0;
		val[x]=sum[x]=d;
		isum[x]=Sum[x]=ans[x]=0;
	}
	void rs(int x){
		if(!x)return;
		mark[x]^=1;
		swap(ch[x][0],ch[x][1]);
   	}
	bool isrt(int x){
		return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
	}
	void down(int p){
		if(mark[p]){
			rs(ch[p][0]);rs(ch[p][1]);
			mark[p]=0;
		}
	}
	void up(int x){
	    sum[x]=(sum[ch[x][0]]+sum[ch[x][1]]+val[x]+isum[x])%P;
	    ans[x]=(ans[ch[x][0]]+ans[ch[x][1]]+Sum[x])%P;
	}
	void rotate(int x){
	    int y=fa[x],z=fa[y],k=(x==ch[y][1]);
	    if(!isrt(y))ch[z][y==ch[z][1]]=x; fa[x]=z;
	    ch[y][k]=ch[x][!k]; if(ch[x][!k])fa[ch[x][!k]]=y;
	    ch[x][!k]=y,fa[y]=x;
	    up(y),up(x);
	}
	void splay(int x){
		for(int y=x;;y=fa[y]){
			stk[++top]=y;
			if(isrt(y))break;
		}while(top)down(stk[top--]);
		while(!isrt(x)){
			int y=fa[x],z=fa[y];
			if(!isrt(y))
				((ch[z][1]==y)^(ch[y][1]==x))?rotate(x):rotate(y);
			rotate(x);
		}
	}
//	void splay(int x){
//	    stk[top=1]=x;
//	    for(int y=x;!isrt(y);y=fa[y])stk[++top]=fa[y];
//	    while(stk[top])down(stk[top]),top--;
//	    while(!isrt(x))
//	    {
//	        int y=fa[x],z=fa[y];
//	        if(!isrt(y))(x==ch[y][1])==(y==ch[z][1])?rotate(y):rotate(x);
//	        rotate(x);
//	    }
//	}
	void access(int x){
		for(int y=0;x;y=x,x=fa[x]){
			splay(x);
        	(isum[x]+=(-sum[y]+sum[ch[x][1]])%P)%=P;
        	(Sum[x]+=(-sum[y]*sum[y]%P+sum[ch[x][1]]*sum[ch[x][1]])%P)%=P;
			ch[x][1]=y;
			up(x);
		}
	}
	void makert(int x){
		access(x);splay(x);rs(x);
	}
	int fintrt(int x){
		access(x);splay(x);down(x);
		while(ch[x][0])down(x=ch[x][0]);
		splay(x);return x;
	}
	void link(int x,int y){
		makert(x),makert(y);
		fa[x]=y;
	    (isum[y]+=sum[x])%=P;
	    (Sum[y]+=sum[x]*sum[x]%P)%=P;
		up(y);
	}
	void split(int x,int y){
		makert(x);access(y);splay(x);
	}
	void update(int x,int d){
		split(x,x);val[x]=d;up(x);
	}
	LL query(int x,int y){
		split(x,y);
    	return ((sum[x]*sum[x]%P-ans[x])%P+P)%P;
	}
}Tr;
int main(){
	while(~scanf("%d%d",&n,&m)){
		for(int i=1,x;i<=n;i++)scanf("%d",&x),Tr.newnode(i,x);
		for(int i=1,a,b;i<n;i++){
			scanf("%d%d",&a,&b);
			Tr.link(a,b);
		}
		while(m--){
            int op,u,v;
            scanf("%d%d%d",&op,&u,&v);
            if(op==1)Tr.update(u,v);
            else if(op==2)printf("%d\n",Tr.query(u,v));
        }
	}
	return 0;
}
