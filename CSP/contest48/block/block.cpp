#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
int n;
LL t;
int X[M],V[M];
struct P30{
	int calc(int s){
		int r=lower_bound(X+1,X+n+1,s)-X;
		int l=r-1;
		LL nowt=t,res=0;
		while(nowt>=0&&r<=n&&l>=1){
			if(X[r]-s<s-X[l]){
				LL ca=min(2LL*(X[r]-s)*V[r],nowt);
				nowt-=ca;
				if(X[r]==s)res+=V[r];
				else res+=ca/(2LL*(X[r]-s));
				r++;
			}
			else {
				LL ca=min(2LL*(s-X[l])*V[l],nowt);
				nowt-=ca;
				if(X[l]==s)res+=V[l];
				else res+=ca/(2LL*(s-X[l]));
				l--;
			}
		}
		while(nowt>=0&&r<=n){
			LL ca=min(2LL*(X[r]-s)*V[r],nowt);
			nowt-=ca;
			if(X[r]==s)res+=V[r];
			else res+=ca/(2LL*(X[r]-s));
			r++;
		}
		while(nowt>=0&&l>=1){
			LL ca=min(2LL*(s-X[l])*V[l],nowt);
			nowt-=ca;
			if(X[l]==s)res+=V[l];
			else res+=ca/(2LL*(s-X[l]));
			l--;
		}
		return res;
	}
	void solve(){
		int ans=0;
		for(int i=1;i<=1000;i++){
			ans=max(ans,calc(i));
		}
		printf("%d",ans);
	}
}p30;
struct P100{
	int l,r;
	LL ans,nowt,Lsum,Rsum,Lcnt,Rcnt,pos;
	LL hv[M];
	void release(){
		LL dis=2*(pos-X[l]),cj=-nowt;
		LL ned;
		if(cj%dis==0)ned=cj/dis;
		else ned=cj/dis+1;
		ned=min(ned,hv[l]);
		hv[l]-=ned;Lsum-=X[l]*ned;Lcnt-=ned;
		nowt+=ned*dis;
		if(hv[l]==0)l++;
	}
	void update(){
		LL dis=2*(X[r]-pos);
		LL res=V[r]-hv[r],ca;
		if(dis==0)ca=res;
		else ca=min(res,nowt/dis);
		hv[r]+=ca;Rsum+=X[r]*ca;Rcnt+=ca;
		nowt-=ca*dis;
		if(hv[r]==V[r])r++;
	}
	void replace(){
		LL dis=2*(pos-X[l]);
		LL res=V[r]-hv[r];
		LL ca=min(hv[l],res);
		nowt+=dis*ca;Lsum-=ca*X[l];Lcnt-=ca;hv[l]-=ca;if(hv[l]==0)l++;
		if(r<=n&&nowt>=2*(X[r]-pos))update();
	}
	void solve(){
		l=1;r=1;nowt=t;Lsum=Rsum=Lcnt=Rcnt=0;
		for(int i=1;i<=n;i++){
			pos=X[i];
			Lsum+=hv[i-1]*X[i-1];Lcnt+=hv[i-1];Rsum-=hv[i-1]*X[i-1];Rcnt-=hv[i-1];
			nowt=t-2*(Lcnt*pos-Lsum+Rsum-Rcnt*pos);
			while(l<=i-1&&nowt<0)release();
			while(r<=n&&nowt>=2*(X[r]-pos))update();
			while(r<=n&&l<=i-1&&X[r]-pos<=pos-X[l])replace();
			while(r<=n&&nowt>=2*(X[r]-pos))update();
			ans=max(ans,Lcnt+Rcnt);
		}
		printf("%lld\n",ans);
	}
}p100;
int main(){
//	freopen("block.in","r",stdin);
//	freopen("block.out","w",stdout);
	scanf("%d%lld",&n,&t);
	for(int i=1;i<=n;i++)scanf("%d",&X[i]);
	for(int i=1;i<=n;i++)scanf("%d",&V[i]);
	if(n<=100)p30.solve();
	else p100.solve();
	return 0;
}
