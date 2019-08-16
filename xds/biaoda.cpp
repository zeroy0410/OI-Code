#include<bits/stdc++.h>
using namespace std;
#define maxn 100010
#define M 100010
#define LL long long
const int mod=1e9+7;
LL x[M],a[M];
pair<LL,LL>q[M];
int main(){
	LL hp;
	int n,h,t;
	while(scanf("%d%lld",&n,&hp)==2){
		h=t=0;
		LL ans=0,cur=hp;
		for(int i=1;i<=n;++i){
			scanf("%lld%lld",x+i,a+i);
			while(x[i]>=cur&&t>h){
				LL res=q[h].first,rise=q[h].second;
				LL u=(x[i]-cur)/rise+1;
				if(u*rise<=res){
					q[h].first-=u*rise;
					if(q[h].first==0)++h;
					ans+=u;cur+=u*rise;
				}
				else{
					u=res/rise;ans+=u;
					cur+=u*rise;u=res%rise;
					++h;
					if(h==t||u>=q[h].second){
						++ans;cur+=u;
					}
					else{
						q[h].first+=u;
					}
				}
			}
			cur-=x[i];
			pair<LL,LL>p(x[i],a[i]);
			while(t>h&&a[i]>=q[t-1].second){
				--t;p.first+=q[t].first;
			}
			q[t++]=p;
		}
		printf("%lld\n",ans);
	}
	return 0;
}