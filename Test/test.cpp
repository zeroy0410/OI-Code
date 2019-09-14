#include<stdio.h>
#include<algorithm>
#define M 4000005
using namespace std;
int n,cnt[M],ans,A[M];
void insert(int x,int y){
	if(cnt[x|y]==2)return;
	if(x==0){
		cnt[y]++;
		return;
	}
	insert(x-(x&-x),y|x&-x);
	insert(x-(x&-x),y);
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=n;i>=1;i--){
		if(i+2<=n){
			int now=0;
			for(int j=20;j>=0;j--)
				if(!((1<<j)&A[i])&&cnt[now|1<<j]==2)now|=1<<j;
			ans=max(ans,now|A[i]);
		}
		insert(A[i],0);
	}
	printf("%d\n",ans);
	return 0;
}
