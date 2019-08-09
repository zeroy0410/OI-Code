#include<bits/stdc++.h>
using namespace std;
#define M 1000005
int n,i,j,h,a[M],r,f,l,L,R;
long long s[M],b[M],c,d,tot,ans;
bool mark[M];
int main() {
	freopen("stone.in","r",stdin);
	freopen("stone.out","w",stdout);
	scanf("%d",&n);
	for(i=1; i<=n; i++) {
		scanf("%d",&a[i]),tot+=a[i],s[++r]=a[i];
		if(a[i]==0)mark[r]=1;
		else mark[r]=0;
		while(r>2)
			if(!mark[r]&&!mark[r-1]&&!mark[r-2]&&s[r]<s[r-1]&&s[r-2]<s[r-1])
				s[r-2]+=s[r]-s[r-1],r-=2;
			else break;
	}
	L=f=1,R=r;
	while(!mark[L]&&!mark[L+1]&&s[L]>s[L+1])L+=2;
	while(!mark[R]&&!mark[R-1]&&s[R]>s[R-1])R-=2;
	L--,R++;
	for(i=L+1; i<R; i++)if(!mark[i])b[++l]=s[i];
	sort(b+1,b+l+1);
	for(i=l; i>0; i--,f=-f)ans+=b[i]*f;
	for(i=L; i>0; i--,f=-f)ans+=s[i]*f;
	for(i=R; i<=r; i++,f=-f)ans+=s[i]*f;
	printf("%lld %lld\n",(ans+tot)/2,(tot-ans)/2);
	return 0;
}