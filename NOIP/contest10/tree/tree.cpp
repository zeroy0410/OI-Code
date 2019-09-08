#include<bits/stdc++.h>
#define M 2000005
using namespace std;
int n,A[M];
bool mark[M];
int main(){
	freopen("tree.in","r",stdin);
	freopen("tree.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	int ans=1;
	for(int i=1;i<n;i++){
		for(int j=i+i;j<=n;j+=i)
			if(A[j]!=A[i]&&!mark[j]){ans++;mark[j]=1;}
	}
	printf("%d\n",ans);
	return 0;
}
