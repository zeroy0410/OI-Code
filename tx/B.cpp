#include<bits/stdc++.h>
#define M 250005
#define LL long long
using namespace std;
int n,A[M],B[M],ans[M];
struct node{
	int x;
	bool operator < (const node& res)const{
		return B[x]>B[res.x];
	}
};
multiset<node>S;
multiset<node>::iterator it;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	for(int i=1;i<=n;i++)scanf("%d",&B[i]);
	LL res=0;
	for(int i=1;i<=n;i++){
		res+=A[i];
		if(res>=B[i]){
			res-=B[i];
			S.insert((node){i});
		}
		else {
			it=S.begin();
			if(res+B[it->x]>=B[i]){
				res+=B[it->x]-B[i];
				S.erase(it);
				S.insert((node){i});
			}
		}
	}
	printf("%d\n",(int)S.size());
	int acnt=0;
	if((int)S.size()){
		it=S.end();it--;
		for(;;it--){
			ans[++acnt]=it->x;
			if(it==S.begin())break;
		}
	}
	sort(ans+1,ans+acnt+1);
	for(int i=1;i<=acnt;i++)
		printf("%d ",ans[i]);
	return 0;
}
