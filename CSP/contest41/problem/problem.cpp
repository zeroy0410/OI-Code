#include<bits/stdc++.h>
#define M 1005
using namespace std;
int n;
struct Pshui{
	int A[M];
	void solve(){
		for(int i=1;i<=n;i++)A[i]=i;
		for(int i=1;i<=n/2;i++)printf("%d %d ",A[i],A[i+n/2]);
		puts("");
		int cur=n/2;
		for(int j=2;j<n;j++){
			swap(A[cur],A[n/2+cur]);
			int tmp=A[n/2+1];
			for(int i=n/2+1;i<n;i++)A[i]=A[i+1];
			A[n]=tmp;
			for(int i=1;i<=n/2;i++)printf("%d %d ",A[i],A[i+n/2]);
			puts("");
			if(j&1)cur--;
		}
	}
}pshui;
int main(){
	freopen("problem.in","r",stdin);
	freopen("problem.out","w",stdout);
	scanf("%d",&n);
	pshui.solve();
	return 0;
}
