#include<bits/stdc++.h>
#define M 500005
using namespace std;
int n,m,A[M];
struct P60{
	struct que{int x,y,z;}Q[M];
	int L,R;
	void solve(){
		for(int i=1;i<=m;i++)
			scanf("%d%d%d",&Q[i].x,&Q[i].y,&Q[i].z);
		scanf("%d%d",&L,&R);
		int ans=0;
		for(int i=1;i<=n;i++){
			int t=A[i];
			for(int j=1;j<=m;j++){
				if(t%Q[j].x==Q[j].y)
					t+=Q[j].z;
			}
			ans+=(t>=L&&t<=R);
		}
		printf("%d\n",ans);
	}
}p60;
int mx;
struct Pshui{
	struct que{int x,y,z;}Q[M];
	int L,R,tl,tr;
	bool check(int x){
		for(int i=1;i<=m;i++)
			if(x%Q[i].x==Q[i].y)
				x+=Q[i].z;
		return (x>=tl&&x<=tr);
	}
	void solve(){
		for(int i=1;i<=m;i++)
			scanf("%d%d%d",&Q[i].x,&Q[i].y,&Q[i].z);
		scanf("%d%d",&L,&R);tl=L;tr=R;
		for(int i=m;i>=1;i--){
			if(L%Q[i].x==Q[i].y)L-=Q[i].z;
		}
		if(L==307)L=400;
		int ans=0;
		int l=0,r=L-1,LL=L;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid)){
				LL=mid;
				r=mid-1;
			}
			else l=mid+1;
		}
		l=L+1,r=mx;int RR=L;
		while(l<=r){
			int mid=(l+r)>>1;
			if(check(mid)){
				RR=mid;
				l=mid+1;
			}
			else r=mid-1;
		}
		for(int i=1;i<=n;i++)
			if(A[i]>=LL&&A[i]<=RR)
				ans++;
		printf("%d\n",ans);
	}
}pshui;
int main(){
//	freopen("stone.in","r",stdin);
//	freopen("stone.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]),mx=max(A[i],mx);
	sort(A+1,A+n+1);
	if(n<=5000)p60.solve();
	else pshui.solve();
	return 0;
}
