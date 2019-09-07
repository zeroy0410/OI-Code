#include<bits/stdc++.h>
#define For(a,b,c) for(int a=b,_=c;a<=_;++a)
using namespace std;
const int N=20;
int n,m,go[N],C[1<<N],F[1<<N];
int main() {
	scanf("%d%d",&n,&m);
	For(i,1,m) {
		int a,b;
		scanf("%d%d",&a,&b),--a,--b;
		go[a]|=1<<b,go[b]|=1<<a;
	}
	For(i,1,(1<<n)-1) C[i]=C[i&(i-1)]+1;
	memset(F,60,sizeof(F)),F[0]=0;
	For(i,0,(1<<n)-2) {
		int c=0;
		For(j,0,n-1)
		if(i&(1<<j)) c+=C[go[j]&(~i)];
		For(j,0,n-1)
		if(!(i&(1<<j))) F[i|(1<<j)]=min(F[i|(1<<j)],F[i]+c);
	}
	printf("%d\n",F[(1<<n)-1]);
	return 0;
}
