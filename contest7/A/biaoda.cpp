#include<bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
int n;char S[1000005];
int main(){
	freopen("zoo.in","r",stdin);
	freopen("biaoda.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%s",S+1);
		int len=strlen(S+1);
		int ans=1;
		for(int i=1;i<=len;i++){
			int res=1;
			for(int j=1;j<=i/2;j++){
				bool f=1;
				for(int k=1;k<=j&&f;k++)
					if(S[k]!=S[i-j+k])f=0;
				res+=f;
			}
			ans=1LL*ans*res%mod;
		}
		printf("%d\n",ans);
	}
	return 0;
}
