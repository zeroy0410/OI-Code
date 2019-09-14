#include <bits/stdc++.h>
using namespace std;
const int _=1e6+7;
int n,ans,a[_],cnt[1<<21];
void insert(int x,int b) {
	if(cnt[x]>=2) return;
	if(b==-1) return cnt[x]++,void();
	insert(x,b-1);
	if(x&(1<<b)) insert(x^(1<<b),b-1);
}
int query(int x) {
	int ans=0;
	for(int i=20;i>=0;--i)
		if(((x&(1<<i))==0)&&cnt[ans|(1<<i)]>=2) ans|=1<<i;
	return x|ans;
}
int main() {
	scanf("%d",&n);
	for(int i=1;i<=n;++i) scanf("%d",&a[i]);
	for(int i=n;i>=1;--i) {
		if(i<=n-2) ans=max(ans,query(a[i]));
		insert(a[i],20);
	}
	printf("%d\n",ans);
	return 0;
}

