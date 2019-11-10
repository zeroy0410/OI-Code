#include<bits/stdc++.h>
#define LL long long
#define M 100005
using namespace std;
const LL mod=998244353;
int n,m;
LL qkpow(LL a,LL b){
	LL res=1;
	while(b){
		if(b&1)res=res*a%mod;
		a=a*a%mod;
		b>>=1;
	}
	return res;
}
LL calc(LL x,LL y){
	return x*qkpow(y,mod-2)%mod;
}
LL add(LL a,LL b){
	return (a*(mod+1-b)+b*(mod+1-a))%mod;
}
int now;
int Lson[M*400],Rson[M*400],sum[M*400],ver[M<<2],tt;
void AddY(int &p,int l,int r,int L,int R){
	if(!p)p=++tt;
	if(l==L&&r==R){sum[p]=add(sum[p],now);return;}
	int mid=(l+r)>>1;
	if(R<=mid)AddY(Lson[p],l,mid,L,R);
	else if(L>mid)AddY(Rson[p],mid+1,r,L,R);
	else {
		AddY(Lson[p],l,mid,L,mid);
		AddY(Rson[p],mid+1,r,mid+1,R);
	}
}
void AddX(int p,int l,int r,int lX,int rX,int lY,int rY){
//	cout<<l<<' '<<r<<' '<<lX<<' '<<rX<<endl;
	if(l==lX&&r==rX){
		AddY(ver[p],0,n,lY,rY);
		return;
	}
	int mid=(l+r)>>1;
	if(rX<=mid)AddX(p<<1,l,mid,lX,rX,lY,rY);
	else if(lX>mid)AddX(p<<1|1,mid+1,r,lX,rX,lY,rY);
	else {
		AddX(p<<1,l,mid,lX,mid,lY,rY);
		AddX(p<<1|1,mid+1,r,mid+1,rX,lY,rY);
	}
}
int queryY(int x,int l,int r,int Y) {
    if(l==r) return sum[x];
    int mid=(l+r)>>1,res=sum[x];
    if(Y<=mid) res=add(res,queryY(Lson[x],l,mid,Y));
    else res=add(res,queryY(Rson[x],mid+1,r,Y));
    return res;
}
int queryX(int x,int l,int r,int X,int Y) {
    if(l==r) return queryY(ver[x],0,n,Y);
    int mid=(l+r)>>1,res=queryY(ver[x],0,n,Y);
    if(X<=mid)res=add(res,queryX(x<<1,l,mid,X,Y));
    else res=add(res,queryX(x<<1|1,mid+1,r,X,Y));
    return res;
}
int main(){
//	freopen("bit.in","r",stdin);
//	freopen("bit.out","w",stdout); 
	scanf("%d%d",&n,&m);
	int ct=0;
	while(m--){
		int op,l,r;
		scanf("%d%d%d",&op,&l,&r);
		if(op==1){
			now=calc(2,r-l+1);
			AddX(1,0,n,l,r,l,r);
			now=calc(1,r-l+1);
			if(r<n)AddX(1,0,n,l,r,r+1,n);
			AddX(1,0,n,0,l-1,l,r);
			ct=!ct;
		}
		else {
			int res=(mod+1-queryX(1,0,n,l-1,r))%mod;
			if(l==1&&ct)res=(1-res+mod)%mod;
			printf("%d\n",res);	
		}
	}
	return 0;
}
