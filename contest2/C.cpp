#include<bits/stdc++.h>
#define M 4005
using namespace std;
int n,m,p,LL;
bool mark[M][M]; 
int U[M][M],D[M][M],L[M][M],R[M][M];
long long ans=0;
int Lson[M*60],Rson[M*60],cnt[M*60],ver[M],tt=0;
void Insert(int od,int& rt,int x,int L,int R){
	rt=++tt;
	Lson[rt]=Lson[od];
	Rson[rt]=Rson[od];
	cnt[rt]=cnt[od]+1;
	if(L==R)return;
	int mid=(L+R)>>1;
	if(x<=mid)Insert(Lson[od],Lson[rt],x,L,mid);
	else Insert(Rson[od],Rson[rt],x,mid+1,R); 
}
int query(int od,int rt,int L,int R,int ql,int qr){
	if(L==ql&&R==qr)return cnt[rt]-cnt[od];
	int mid=(L+R)>>1;
	if(qr<=mid)return query(Lson[od],Lson[rt],L,mid,ql,qr);
	else if(ql>mid)return query(Rson[od],Rson[rt],mid+1,R,ql,qr);
	return query(Lson[od],Lson[rt],L,mid,ql,mid)+query(Rson[od],Rson[rt],mid+1,R,mid+1,qr); 
}
int main(){
//	freopen("wall.in","r",stdin);
//	freopen("wall.out","w",stdout);
	scanf("%d%d%d%d",&n,&m,&LL,&p);
	for(int i=1,x,y;i<=p;i++){
		scanf("%d%d",&x,&y);
		mark[x][y]=1;	
	}
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(mark[i][j])continue;
			U[i][j]=U[i-1][j]+1;
			L[i][j]=L[i][j-1]+1;
		}
	}
	for(int i=n;i>=1;i--){
		for(int j=m;j>=1;j--){
			if(mark[i][j])continue;
			D[i][j]=D[i+1][j]+1;
			R[i][j]=R[i][j+1]+1;
		}
	} 
	for(int i=1;i<=n;i++){
		tt=0;
		for(int j=1,x,y;i+j-1<=n&&j<=m;j++){
			x=i+j-1;y=j;
			ver[j]=ver[j-1];
			if(mark[x][y])continue;
			int mi=min(L[x][y],U[x][y]);
			if(j-LL+1>j-mi)ans+=query(ver[j-mi],ver[j-LL+1],1,n+m,j,n+m);
			Insert(ver[j-1],ver[j],j+min(R[x][y],D[x][y])-1,1,n+m);
		}
	}
	for(int i=2;i<=m;i++){
		tt=0;
		for(int j=1,x,y;i+j-1<=m&&j<=n;j++){
			x=j;y=i+j-1;
			ver[j]=ver[j-1];
			if(mark[x][y])continue;
			int mi=min(L[x][y],U[x][y]);
			if(j-LL+1>j-mi)ans+=query(ver[j-mi],ver[j-LL+1],1,n+m,j,n+m);
			Insert(ver[j-1],ver[j],j+min(R[x][y],D[x][y])-1,1,n+m);
		}
	}
	printf("%lld\n",ans);
	return 0;
}
