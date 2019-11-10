#include<stdio.h>
#include<algorithm>
#include<string.h>
#define M 305
using namespace std;
int n,K;
char S[M],T[M];
int main(){
	freopen("master.in","r",stdin);
	freopen("master.out","w",stdout);
//	printf("%lf\n",(&mm2-&mm1)/1024.0/1024);
	scanf("%d%d",&n,&K);
	scanf("%s%s",S+1,T+1);
	int ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			int cur1=i,cur2=j,cnt=0;
			while(cur1<=n&&cur2<=n&&cnt<=K){
				if(S[cur1]==T[cur2])
					cur1++,cur2++;
				else {
					if(cnt==K)break;
					cur1++,cur2++;
					cnt++;
				}
			}
			ans=max(ans,cur1-i);
		}
	}
	printf("%d\n",ans);
	return 0;
}
