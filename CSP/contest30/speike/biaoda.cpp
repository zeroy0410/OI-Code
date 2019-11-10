#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=5e5+5;
const ll inf=1e18;
struct inp{
	int x,l,r;
	bool operator <(const inp &_)const{
		return x<_.x;
	}
}A[M];
struct node{
	int x,y;ll ans;
	bool operator <(const node &_)const{
		return y<_.y;
	}
};
set<node>s;
typedef set<node>::iterator sint;
int main(){
	freopen("speike.in","r",stdin);
	freopen("speike.out","w",stdout);
	int n,X;
	scanf("%d%d",&n,&X);
	for(int a,b,c,d,i=1;i<=n;i++){
		scanf("%d%d%d%d",&a,&b,&c,&d);
		if(a>c)swap(a,c);
		if(b>d)swap(b,d);
		A[i]=(inp){a,b,d};
	}
	sort(A+1,A+1+n);
	s.insert((node){0,0,0});
	for(int i=1;i<=n;i++){
		ll ansl=inf,ansr=inf;
		for(sint it=s.lower_bound((node){0,A[i].l,0});it!=s.end()&&it->y<=A[i].r;){
			ansl=min(ansl,it->ans+A[i].x-it->x+it->y-A[i].l);
			ansr=min(ansr,it->ans+A[i].x-it->x+A[i].r-it->y);
			sint tmp=it++;s.erase(tmp);
		}
		if(ansl!=inf)s.insert((node){A[i].x,A[i].l,ansl});
		if(ansr!=inf)s.insert((node){A[i].x,A[i].r,ansr});
	}
	ll ans=inf;
	for(sint it=s.begin();it!=s.end();it++)
		ans=min(ans,it->ans+X-it->x+abs(it->y));
	printf("%lld\n",ans);
	return 0;
}

