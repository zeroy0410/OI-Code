#include<stdio.h>
#include<algorithm>
#include<iostream>
#define M 500005
using namespace std;
int n,c,Q;
int A[M];
struct P100{
	int ch[M][2],fa[M],rt,tot,val[M],sz[M],stk[M],sum[M],ll[M],rr[M],lzy[M],top;
	bool mark[M];
	void Print(int p){
		Down(p);
		if(ch[p][0])Print(ch[p][0]);
		printf("%d ",val[p]);
		if(ch[p][1])Print(ch[p][1]);
		Up(p);
	}
	void Up(int p){
		sz[p]=sz[ch[p][0]]+sz[ch[p][1]]+1;
		sum[p]=sum[ch[p][0]]+sum[ch[p][1]]+(ch[p][0]&&val[p]!=rr[ch[p][0]])+(ch[p][1]&&val[p]!=ll[ch[p][1]]);
		if(ch[p][0])ll[p]=ll[ch[p][0]];
		else ll[p]=val[p];
		if(ch[p][1])rr[p]=rr[ch[p][1]];
		else rr[p]=val[p];
	}
	void flip(int p){
		if(!p)return;
		mark[p]^=1;
		swap(ch[p][0],ch[p][1]);
		swap(ll[ch[p][0]],rr[ch[p][0]]);
		swap(ll[ch[p][1]],rr[ch[p][1]]);
		if(p)Up(p);
	}
	void reset(int p,int cl){
		sum[p]=0;
		lzy[p]=ll[p]=rr[p]=cl;
		val[p]=cl;
	}
	void Down(int p){
		if(mark[p]){
			flip(ch[p][0]);flip(ch[p][1]);
			mark[p]=0;
		}
		if(lzy[p]){
			reset(ch[p][0],lzy[p]);
			reset(ch[p][1],lzy[p]);
			lzy[p]=0;
		}
	}
	void build(int &x,int f,int *arr,int L,int R){
		if(L>R)return;
		int mid=(L+R)>>1;
		x=++tot;
		ch[x][0]=ch[x][1]=0;
		fa[x]=f;
		val[x]=arr[mid];
		ll[x]=rr[x]=val[x];
		sz[x]=1;mark[x]=sum[x]=0;
		build(ch[x][0],x,arr,L,mid-1);
		build(ch[x][1],x,arr,mid+1,R);
		Up(x);
	}
	void clear(){rt=tot=0;}
	void rotate(int x){
		int y=fa[x],z=fa[y],k=x==ch[y][1];
		Down(y);Down(x);
		if(z)ch[z][y==ch[z][1]]=x;fa[x]=z;
		ch[y][k]=ch[x][!k];if(ch[x][!k])fa[ch[x][!k]]=y;
		ch[x][!k]=y,fa[y]=x;
		Up(y);Up(x);
	}
	void splay(int x,int w){
		for(int y=x;;y=fa[y]){
			stk[++top]=y;
			if(y==w)break;
		}while(top)Down(stk[top--]);
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
			Down(u);
			if(sz[ch[u][0]]+1==x)return u;
			else if(sz[ch[u][0]]>=x)u=ch[u][0];
			else x-=sz[ch[u][0]]+1,u=ch[u][1];
		}
		return u;
	}
	int split(int l,int r){
		int L=find(l-1),R=find(r+1);
		splay(L,0);splay(R,L);
		return R;
	}
	//[n-k+1,n]->[1,k]
	void modify(int l,int r){
		l=find(l-1),r=find(r+1);
		splay(l,0),splay(r,l);
		int x=ch[r][0];
		fa[x]=ch[r][0]=0;
		splay(r,0);
		l=find(0),r=find(1);
		splay(l,0),splay(r,l);
		fa[x]=r,ch[r][0]=x;
		splay(r,0);
	}
	void Flip(){
		int p=split(2,n);
		flip(ch[p][0]);Up(p);Up(fa[p]);
	}
	void Paint(int l,int r,int x){
		int p=split(l,r);
		reset(ch[p][0],x);Up(p);Up(fa[p]);
	}
	void Swap(int a,int b){
		int aa=find(a),bb=find(b);
		int t1=val[aa],t2=val[bb];
		Paint(b,b,t1);
		Paint(a,a,t2);
	}
	char op[15];
	void solve(){
		build(rt,0,A,0,n+1);
		scanf("%d",&Q);
		while(Q--){
//			Print(rt);
//			puts("");
			int k,l,r,x;
			scanf("%s",op);
			if(op[0]=='R'){
				scanf("%d",&k);
				modify(n-k+1,n);
			}
			else if(op[0]=='F')Flip();	
			else if(op[0]=='S'){
				scanf("%d%d",&l,&r);
				Swap(l,r);
			}
			else if(op[0]=='P'){
				scanf("%d%d%d",&l,&r,&x);
				if(l<=r)Paint(l,r,x);
				else {Paint(l,n,x);Paint(1,r,x);}
			}
			else if(op[0]=='C'&&op[1]=='S'){
				scanf("%d%d",&l,&r);
				if(l<=r){
					int p=split(l,r);
					printf("%d\n",sum[ch[p][0]]+1);	
				}
				else {
					int p1=split(l,n);
					int s1=sum[ch[p1][0]],rr1=rr[ch[p1][0]];
					int p2=split(1,r);
					int s2=sum[ch[p2][0]],ll1=ll[ch[p2][0]];
					printf("%d\n",s1+s2+(ll1!=rr1)+1);
				}
			}
			else {
				if(sum[rt]==2)sum[rt]++;
				printf("%d\n",sum[rt]+(val[find(1)]!=val[find(n)])-2);
			}
		}
	}
}p100;
int main(){
	freopen("necklace.in","r",stdin);
	freopen("necklace.out","w",stdout);
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
//	if(n<=1000)p60.solve();
	p100.solve();
	return 0;
}
