#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
const int inf=1061109567;
int n;
int a[6][maxn];
struct node{
	int ll[6][6],rr[6][6],lr[6][6];
	void clear(){memset(ll,0x3f,sizeof ll);memset(rr,0x3f,sizeof rr);
				memset(lr,0x3f,sizeof lr);}
	bool empty()const{return ll[0][0]==inf;}	
}t[maxn<<2];
node operator+(const node &ls,const node &rs){
	static int lm[6][6],rm[6][6];
	if(ls.empty())return rs;if(rs.empty())return ls;
	node a;a.clear();
	memset(lm,0x3f,sizeof lm);memset(rm,0x3f,sizeof rm);
	for(int k=0;k<6;k++)for(int i=0;i<6;i++)for(int j=0;j<6;j++)
	lm[i][j]=min(lm[i][j],ls.lr[i][k]+rs.ll[k][j]+ls.rr[j][j]),
	rm[i][j]=min(rm[i][j],rs.ll[i][i]+ls.rr[i][k]+rs.lr[k][j]);
	for(int i=0;i<6;i++)
	for(int j=0;j<6;j++){
		a.ll[i][j]=ls.ll[i][j];a.rr[i][j]=rs.rr[i][j];a.lr[i][j]=inf;
		for(int k=0;k<6;k++){
			a.ll[i][j]=min(a.ll[i][j],lm[i][k]+ls.lr[j][k]-ls.rr[k][k]);
			a.rr[i][j]=min(a.rr[i][j],rm[k][i]+rs.lr[k][j]-rs.ll[k][k]);
			a.lr[i][j]=min(a.lr[i][j],ls.lr[i][k]+rs.lr[k][j]);
			a.lr[i][j]=min(a.lr[i][j],lm[i][k]+rm[k][j]-ls.rr[k][k]-rs.ll[k][k]);
		}
	}return a;
}
#define lson i<<1,l,(l+r)/2
#define rson i<<1|1,(l+r)/2+1,r
#define ls i<<1
#define rs i<<1|1
void init(int i,int l){
	int sum[6];
	for(int j=0;j<6;j++)sum[j]=(j?sum[j-1]:0)+a[j][l];
	for(int j=0;j<6;j++)for(int k=0;k<6;k++)
	t[i].ll[j][k]=t[i].rr[j][k]=t[i].lr[j][k]=sum[max(j,k)]-(min(j,k)?sum[min(j,k)-1]:0);
	return;
}
void build(int i,int l,int r){
	if(l==r){
		init(i,l);
		return;
	}build(lson);build(rson);
	t[i]=t[ls]+t[rs];
}
void Change(int i,int l,int r,int ps){
	if(l==r){init(i,l);return;}
	if(ps<=(l+r)/2)Change(lson,ps);
	else Change(rson,ps);
	t[i]=t[ls]+t[rs];
}
node Qmin(int i,int l,int r,int l0,int r0){
	if(l0<=l&&r0>=r)return t[i];
	node ans;ans.clear();
	if(l0<=(l+r)/2)ans=Qmin(lson,l0,r0)+ans;
	if(r0>(l+r)/2)ans=ans+Qmin(rson,l0,r0);
	return ans;
}	
#undef ls
#undef rs
int Qmin(int sx,int sy,int tx,int ty){
	node ls=Qmin(1,1,n,1,sy);
	node md=Qmin(1,1,n,sy,ty);
	node rs=Qmin(1,1,n,ty,n);
	int ans=md.lr[sx][tx];
	for(int i=0;i<6;i++)for(int j=0;j<6;j++){
		ans=min(ans,md.ll[sx][i]+ls.rr[i][j]+md.lr[j][tx]-a[i][sy]-a[j][sy]);
		ans=min(ans,md.lr[sx][i]+rs.ll[i][j]+md.rr[j][tx]-a[i][ty]-a[j][ty]);
		ans=min(ans,ls.rr[sx][i]+md.lr[i][j]+rs.ll[j][tx]-a[i][sy]-a[j][ty]);
	}return ans;
}
int getint(){
	int res=0;char c=getchar();
	while(!isdigit(c))c=getchar();
	while(isdigit(c))res=res*10+c-'0',c=getchar();
	return res;
}
int main(){
	n=getint();
	for(int i=0;i<6;i++)
	for(int j=1;j<=n;j++)
	a[i][j]=getint();
	build(1,1,n);
	int m=getint();
	while(m--){
		int op=getint();
		if(op==1){
			int x=getint(),y=getint(),z=getint();
			a[x-1][y]=z;
			Change(1,1,n,y);
		}else{
			int x=getint(),y=getint(),z=getint(),w=getint();
			if(y>w){swap(x,z);swap(y,w);}
			printf("%d\n",Qmin(x-1,y,z-1,w));
		}
	}
	return 0;
}
