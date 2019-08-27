#include<bits/stdc++.h>
#define M 50005
using namespace std;
int n,m;
struct BIT{
	int C[M];
	void clear(){memset(C,0,sizeof(C));}
	void Add(int x,int d){
		while(x<=n){
			C[x]+=d;
			x+=(x&-x);
		}
	}
	int sum(int x){
		int res=0;
		while(x){
			res+=C[x];
			x-=(x&-x);
		}
		return res;
	}
}Tr;
int ans[M];
int main(){
	while(~scanf("%d",&n)){
		Tr.clear();
		for(int i=1;i<=n;i++)Tr.Add(i,1);
		for(int i=1,x;i<=n;i++){
			scanf("%d",&x);
			int l=1,r=n,res=1;
			while(l<=r){
				int mid=(l+r)>>1;
				if(Tr.sum(mid)>=x){
					res=mid;
					r=mid-1;
				}else l=mid+1;
			}
			Tr.Add(res,-1);
			ans[i]=res;
		}
		scanf("%d",&m);
		for(int i=1,x;i<=m;i++){
			scanf("%d",&x);
			printf("%d",ans[x]);
			if(i!=m)printf(" ");
		}
		puts("");
	}
	return 0;
}
