#include<bits/stdc++.h>
#define M 500005
using namespace std;
int n,c,Q;
int A[M];
int pre(int x,int step){
	x-=step;
	while(x<1)x+=n;
	return x;
}
int nxt(int x,int step){
	x+=step;
	while(x>n)x-=n;
	return x;
}
struct P60{
	char op[15];
	int tmp[1005];
	void solve(){
		scanf("%d",&Q);
		while(Q--){
			int k,l,r,x;
//			for(int i=1;i<=n;i++)printf("%d ",A[i]);
//			puts("");
			scanf("%s",op);
			if(op[0]=='R'){
				scanf("%d",&k);
				for(int i=1;i<=n;i++)tmp[i]=A[i];
				for(int i=1;i<=n;i++)A[nxt(i,k)]=tmp[i];
			}
			else if(op[0]=='F'){
				for(int i=2;n-i+2>i;i++)
					swap(A[i],A[n-i+2]);
			}
			else if(op[0]=='S'){
				scanf("%d%d",&l,&r);
				swap(A[l],A[r]);
			}
			else if(op[0]=='P'){
				scanf("%d%d%d",&l,&r,&x);
				for(int i=l;;i=nxt(i,1)){
					A[i]=x;
					if(i==r)break;
				}
			}
			else if(op[0]=='C'&&op[1]=='S'){
				scanf("%d%d",&l,&r);
				if(l==r){puts("1");continue;}
				int ans=1;
				for(int i=nxt(l,1);;i=nxt(i,1)){
					if(A[i]!=A[pre(i,1)])ans++;
					if(i==r)break;
				}
				printf("%d\n",ans);
			}
			else {
				int st=0;
				for(int i=1;i<=n;i++)
					if(A[i]!=A[pre(i,1)]){st=i;break;}
				if(st==0){puts("1");continue;}
				int ed=pre(st,1);
				int ans=0;
				for(int i=st;;i=nxt(i,1)){
					if(A[i]!=A[pre(i,1)])ans++;
					if(i==ed)break;
				}
				printf("%d\n",ans);
			}
		}
	}
}p60;
struct P100{
	//对于答案，维护缝隙的个数，存储每个子树的最左边的点和最右边的点的颜色 
	int ch[M][2],fa[M],rt,tot,val[M],sz[M],stk[M],sum[M],ll[M],rr[M],lzy[M],top;
	bool mark[M];
	void Print(int p){
		if(ch[p][0])Print(ch[p][0]);
		printf("%d ",val[p]);
		if(ch[p][1])Print(ch[p][1]);
	}
	void replace(int a,int b){
		swap(ch[a][0],ch[b][0]);
		swap(ch[a][1],ch[b][1]);
		swap(fa[a],fa[b]);
		swap(val[a],val[b]);
		swap(sz[a],sz[b]);
		swap(sum[a],sum[b]);
		swap(ll[a],ll[b]);
		swap(rr[a],rr[b]);
		swap(lzy[a],lzy[b]);
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
		mark[p]^=1;
		swap(ch[p][0],ch[p][1]);
	}
	void reset(int p,int cl){
		sum[p]=0;
		lzy[p]=ll[p]=rr[p]=cl;
		val[p]=cl;
	}
	void Down(int p){
		if(lzy[p]){
			reset(ch[p][0],lzy[p]);
			reset(ch[p][1],lzy[p]);
			lzy[p]=0;
		}
		if(mark[p]){
			flip(ch[p][0]);flip(ch[p][1]);
			mark[p]=0;
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
//		cout<<l-1<<' '<<r+1<<endl;
		splay(L,0);splay(R,L);
		return R;
	}
	//[n-k+1,n]->[1,k]
	void Rota(int k){
		int p=split(n-k+1,n);int tmp=ch[p][0];
		fa[ch[p][0]]=0;ch[p][0]=0;Up(p);Up(fa[p]);
		int x=find(1);
		splay(x,0);
		x=ch[x][0];
//		Print(tmp);
//		puts("");
		ch[x][1]=tmp;fa[tmp]=x;Up(x);Up(rt);
	}
	void Flip(){
		flip(rt);
		int x=rt;Down(x);
		while(ch[x][1])Down(x=ch[x][1]);
		splay(x,0);
		swap(ch[x][0],ch[x][1]);
	}
	void Swap(int x,int y){
		int a=find(x),b=find(y);
		replace(a,b);
		while(a)Up(a=fa[a]);
		while(b)Up(b=fa[b]);
	}
	void Paint(int l,int r,int x){
		int p=split(l,r);
		reset(ch[p][0],x);Up(p);Up(fa[p]);
	}
	char op[15];
	void solve(){
		build(rt,0,A,0,n+1);
		scanf("%d",&Q);
		while(Q--){
//			Print(rt);
//			puts("");
//			printf("haha: %d %d\n",find(4),find(6));
			int k,l,r,x;
			scanf("%s",op);
			if(op[0]=='R'){
				scanf("%d",&k);
				Rota(k);
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
				printf("%d\n",sum[rt]+(val[find(1)]!=val[find(n)])-2);
			}
		}
	}
}p100;
int main(){
	freopen("necklace.in","r",stdin);
	freopen("biaoda.out","w",stdout);
	scanf("%d%d",&n,&c);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	p60.solve();
	return 0;
}
