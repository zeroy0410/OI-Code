#include<bits/stdc++.h>
#define M 1000005
#define LL long long
using namespace std;
int n,m1,m2;
LL cnt[205],cnt2[205],cnt3[205];
LL tmp[205],tmp2[205],tmp3[205];
struct P1{
	LL solve(){
		int i=200,j=0;
		LL res=0;
		while(i>j){
			LL t=min(cnt[i],cnt3[j]);
			res+=(i-j)*t;
			cnt[i]-=t;
			cnt3[j]-=t;
			if(cnt[i]==0)i--;
			if(cnt3[j]==0)j++;
		}
		return res;
	}
}p1;
struct P2{
	void solve(){
		memcpy(tmp,cnt,sizeof(tmp));
		memcpy(tmp3,cnt3,sizeof(tmp3));
		LL ans=p1.solve();
		memcpy(cnt,tmp,sizeof(tmp));
		memcpy(cnt3,tmp3,sizeof(tmp3));
		bool fl=1;
		for(int i=0;i<=200;i++){
            if(cnt2[i]==0)continue;
            for(int j=i;j<=200;j++){
                LL res=min(cnt[j],cnt2[i]);
                cnt[j]-=res;
                cnt2[i]-=res;
                if(cnt2[i]==0)break;
            }
            if(cnt2[i]>0){fl=0;break;}
        }	
		if(fl){
			cnt3[100]+=1e18;
			ans=max(ans,p1.solve());
		}
		printf("%lld\n",ans);
	}
}p2;
int main(){
	scanf("%d%d%d",&n,&m1,&m2);
	for(int i=1,a,x;i<=n;i++){
		scanf("%d%d",&a,&x);
		cnt[a+100]+=x;
	}
	for(int i=1,a,x;i<=m1;i++){
		scanf("%d%d",&a,&x);
		cnt2[a+100]+=x;
	}
	for(int i=1,a,x;i<=m2;i++){
		scanf("%d%d",&a,&x);
		cnt3[a+100]+=x;
	}
	p2.solve();
	return 0;
}
