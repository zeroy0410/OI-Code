#include<bits/stdc++.h>
using namespace std;
#define N 100005
#define Erase(a) (La[Ne[a]]=La[a],Ne[La[a]]=Ne[a])
int n,m,P[N],L[N],La[N],Ne[N],Mk[N],ans;
struct V {
	int l,num;
	bool operator <(const V&a)const {
		return l>a.l;
	}
} q;
int la,ne;
priority_queue<V>Q;
int main() {
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; ++i) {
		scanf("%d",&P[i]);
		La[i]=i-1,Ne[i]=i+1;
	}
	for(int i=1; i<n; ++i)
		L[i]=P[i+1]-P[i],Q.push((V){L[i],i});
	L[0]=L[n]=1e9;
	while(m) {
		q=Q.top(),Q.pop();
		if(Mk[q.num]||q.l!=L[q.num]) continue;
		Mk[q.num]=Mk[Ne[q.num]]=1;
		ans+=q.l;
		la=La[q.num];
		ne=Ne[q.num];
		Erase(q.num),Erase(Ne[q.num]);
		L[la]=L[la]+L[ne]-L[q.num];
		Q.push((V){L[la],la}),--m;
	}
	printf("%d\n",ans);
	return 0;
}
