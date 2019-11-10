#include<cstdio>
#include<algorithm>
#define M 100005
#define LL long long
using namespace std;
int T,n,V,A[M];
LL sum[M];
struct P30{
	struct node{
		LL l,r;
		bool operator < (const node& res)const{
			return l<res.l;
		}
	}E[M*10];
	int tt;
	void solve(){
		tt=0;
		for(int i=1;i<=n;i++){
			for(int j=i;j<=n;j++){
				LL r=sum[j]-sum[i-1];
				LL l=r/V;
				if(r%V!=0)l++;
				E[++tt]=(node){l,r};
			}
		}
		sort(E+1,E+tt+1);
		LL mx=0,ans=0;
		for(int i=1;i<=tt;i++){
			LL l=E[i].l,r=E[i].r;
			if(mx<l)ans+=r-l+1;
			else ans+=max(0ll,r-mx);
			mx=max(mx,r);
		}
		printf("%lld\n",ans);
	}
}p30;
struct P100{
	inline LL get(LL r){
		if(r%V==0)return r/V;
		return r/V+1;
	}
	void solve(){
		LL l=get(sum[n]);
		//[l-1,sum[n]-1]
		LL r=sum[n];
		LL R=sum[n];
		LL mi=2e9;
		LL ans=0;
		for(int i=1;i<=n;i++)mi=min(mi,1LL*A[i]);
		while(1){
			LL tmp=1e18;
			for(int i=1;i<=n;i++){
				int cur=upper_bound(sum,sum+i,sum[i]-l+1)-sum-1;
				if(cur<0)continue;
				if(sum[cur]<sum[i]-r+1)continue;
				tmp=min(tmp,sum[i]-sum[cur]);
			}
			if(tmp!=1e18)l=get(tmp),r=tmp;
			else {
				ans+=R-l+1;
				r=0;
				for(int i=1;i<=n;i++){
					int cur=lower_bound(sum,sum+i,sum[i]-l+2)-sum;
					if(cur==i)continue;
					r=max(r,sum[i]-sum[cur]);
				}
				if(r==0)break;
				R=r;
				l=get(r);
			}
		}
		printf("%lld\n",ans);
	}
}p100;
int main(){
	freopen("magic.in","r",stdin);
	freopen("magic.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%d%d",&n,&V);
		for(int i=1;i<=n;i++)
			scanf("%d",&A[i]);
		for(int i=1;i<=n;i++)sum[i]=sum[i-1]+A[i];
		p100.solve();
	}
	return 0;
}
