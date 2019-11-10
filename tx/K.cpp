#include<bits/stdc++.h>
#define M 100005
#define LL long long
using namespace std;
int n;
struct node{
	int h,k;
	bool operator < (const node& res)const{
		return h<res.h;
	}
}A[M];
struct BIT{
	int C[M];
	void add(int x,int d){
		x++;
		while(x<M){
			C[x]+=d;
			x+=(x&-x);
		}
	}
	int sum(int x){
		x++;int res=0;
		while(x){
			res+=C[x];
			x-=(x&-x);
		}
		return res;
	}
	void update(int l,int r,int d){
		add(l,d);add(r+1,-d);
	}
}Tr;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&A[i].h,&A[i].k);
	sort(A+1,A+n+1);
	for(int i=1;i<=n;i++){
		int now=Tr.sum(A[i].h-A[i].k+1);
		int l=1,r=A[i].h,s1=1,s2=A[i].h;
		while(l<=r) {
            int mid=l+r>>1;
            if(Tr.sum(mid)<=now) {
                s1=mid;
                r=mid-1;
            } else l=mid+1;
        }
        l=1,r=A[i].h;
        while(l<=r) {
            int mid=l+r>>1;
            if(Tr.sum(mid)>=now) {
                s2=mid;
                l=mid+1;
            } else r=mid-1;
        }
		Tr.update(s2+1,A[i].h,1);
        A[i].k-=A[i].h-s2;
		Tr.update(s1,s1+A[i].k-1,1);
	}
	LL ans=0;
    for(int i=1; i<=A[n].h; i++) {
        int now=Tr.sum(i);
        ans+=1LL*now*(now-1)/2;
    }
    printf("%lld\n",ans);
	return 0;
}
