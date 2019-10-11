#include<bits/stdc++.h>
#define M 1000005
using namespace std;
int n,m,A[M<<1];
void read(int &x){
	char c;
	x=0;
	int f=1;
	while(c=getchar(),c<'0'||c>'9')if(c=='-')f=-1;
	do x=(x<<3)+(x<<1)+(c^48);
	while(c=getchar(),c>='0'&&c<='9');
	x*=f;
}
bool mark[M<<1];
int tot; int id[M<<1];
struct P10{
	struct BIT{
		int C[2005];
		void clear(){
			memset(C,0,sizeof(C));
		}
		void add(int x,int d){
			x++;
			while(x<=n+1){
				C[x]+=d;
				x+=(x&-x);
			}
		}
		int sum(int x){
			int res=0;x++;
			while(x){
				res+=C[x];
				x-=(x&-x);
			}
			return res;
		}
	}Tr,Tr2;
	void solve(){
		for(int i=1,r1,r2;i<=m;i++){
			read(r1);read(r2);
			if(r1>r2)swap(r1,r2);
			Tr.clear();Tr2.clear();
			int res=0;
			for(int j=r2;j>r1;j--)
				if(Tr.sum(id[j])-Tr.sum(id[j]-1))Tr.add(id[j],-1);
				else Tr.add(id[j],1);
			for(int j=r1;j>=0;j--){
				if(Tr.sum(id[j])-Tr.sum(id[j]-1))Tr.add(id[j],-1);
				else Tr.add(id[j],1);
				if(Tr2.sum(id[j])-Tr2.sum(id[j]-1))Tr2.add(id[j],-1);
				else Tr2.add(id[j],1);
				if(Tr.sum(tot)==0&&Tr2.sum(tot)==0)res++;
			}
			printf("%d\n",res);
		}
	}
}p10;
//struct P100{
//	int ret[M<<1];
//	int cnt[M<<1],mx[M<<1];
//	int ver[M<<1],Lson[(M<<1)*60],Rson[(M<<1)*60],sum[(M<<1)*60];
//	void Insert(int od,int &rt,int x,int L,int R){
//		rt=++tot;
//		Lson[rt]=Lson[od];
//		Rson[rt]=Rson[od];
//		sum[rt]=sum[od]+1;
//		if(L==R)return;
//		int mid=(L+R)>>1;
//		if(x<=mid)Insert(Lson[od],Lson[rt],x,L,mid);
//		else Insert(Rson[od],Rson[rt],x,mid+1,R);
//	}
//	int query(int l,int r,int L,int R,int x){
//		if(L==x&&R==x)return sum[r]-sum[l];
//		int mid=(L+R)>>1;
//		if(x<=mid)return query(l,r,L,mid,x);
//		return query(l,r,mid+1,R,x);
//	}
//	void solve(){
//		for(int i=1;i<=2*n;i++){
//			if(A[i]<i)ret[i]=ret[i-1]-1;
//			else ret[i]=ret[i-1]+1;
//			Insert(ver[i-1],ver[i],ret[i],1,n);
//		}
//		for(int i=2*n;i>=1;i--){
//			mx[i]=mx[i+1];
//		for(int i=1,r1,r2;i<=m;i++){
//			read(r1);read(r2);
//			if(r1>r2)swap(r1,r2);
//			Q[i]=(que){r1,r2,i};
//		}
//	}
//}p100;
int main(){
	freopen("hotchkiss.in","r",stdin);
	freopen("hotchkiss.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n*2;i++){
		scanf("%d",&A[i]);
		if(!mark[i]){
			mark[i]=mark[A[i]]=1;
			id[i]=id[A[i]]=++tot;
		}
	}
	p10.solve();
	return 0;
}
