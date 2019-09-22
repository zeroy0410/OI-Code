#include<stdio.h>
#include<algorithm>
#include<math.h>
#define LL long long
using namespace std;
struct node{
	int t,g,m;
	bool operator < (const node& res)const{
		return t<res.t;
	}
}A[18],B[18];
int n,bcnt;
LL ans;
LL calc(LL a,LL b,LL c){
    LL delta=b*b-4*a*c;
    if(delta<0)return -1;
    LL x=floor((-b+sqrt(delta))/(2*a));
    if(x<0||a*x*x+b*x+c>0)return -1;
    return x;
}
void solve(int S){
	bcnt=0;LL sum=0;
	for(int i=0;i<n;i++)if(S&1<<i)B[++bcnt]=A[i],sum+=A[i].m;
	int p=1;LL s=0;
	B[0].t=0;
	for(int i=1;i<=bcnt;i++){
		int x=B[i].t-B[i-1].t;LL c=0;
		for(int j=i;j<=bcnt;j++){
			int T=B[j].t-B[i-1].t;
			c+=B[j].g;
			int res=calc(1,p-T,c-s-1LL*T*p);
			if(res==-1)return;
			x=min(x,res);
		}
		p+=x;
		s+=1LL*((B[i].t-B[i-1].t)-x)*p-B[i].g;
	}
	ans=max(ans,sum);
}
int main(){
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%d%d%d",&A[i].t,&A[i].g,&A[i].m);
	sort(A,A+n);
	for(int i=0;i<1<<n;i++)solve(i);
	printf("%lld\n",ans);
	return 0;
}
