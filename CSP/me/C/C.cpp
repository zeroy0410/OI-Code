#include<bits/stdc++.h>
#define M 2005
using namespace std;
int n,T,A[M];
int main(){
//	freopen("tree.in","r",stdin);
//	freopen("tree.out","w",stdout);
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1,x;i<=n;i++){
			scanf("%d",&x);
			A[x]=i;
		}

	}
	return 0;
}