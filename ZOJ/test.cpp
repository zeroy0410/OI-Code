#include<bits/stdc++.h>
#define M 100005
using namespace std;
int T,n,A[M],cnt[M],ans[M];
struct node{
	int x,d;
	bool operator < (const node& res) const{
		if(d!=res.d)return d<res.d;
		return x>res.x;
	}
};
set<node>S;
set<node>::iterator it2;
set<int>ex;
set<int>::iterator it;
void Add(int x,int d){
	if(cnt[x])it2=S.find((node){x,cnt[x]});
	if(cnt[x])S.erase(it2);
	cnt[x]+=d;
	if(cnt[x])S.insert((node){x,cnt[x]});
	if(!cnt[x])ex.erase(x);
	if(cnt[x]==1)ex.insert(x);
}
int main(){
	scanf("%d",&T);
	while(T--){
		memset(cnt,0,sizeof(cnt));
		scanf("%d",&n);
		ex.clear();S.clear()
		for(int i=1;i<=n;i++)scanf("%d",A+i),cnt[A[i]]++;
		for(int i=1;i<=n;i++)ex.insert(A[i]),S.insert((node){A[i],cnt[A[i]]});
		bool fl=1;
		for(int i=1;i<=n-1;i++){
			it=ex.begin();
			if(*it==A[i]&&*it==*(ex.rbegin())){fl=0;break;}
			if(*it==A[i])it++;
			int xmin=*it;
			Add(xmin,-1);
			it2=S.end();it2--;
			int mx=it2->d,t=it2->x;
			if(n-i+1>mx*2)ans[i]=xmin;
			else {
				Add(xmin,1);
				it2=S.end();it2--;
				if(it2->x==A[i]&&it2!=S.begin())it2--;
				if(it2==S.begin()&&it2->x==A[i]){fl=0;break;}
				int t=it2->x;
				Add(t,-1);
				ans[i]=t;
				if(n-i+1<=cnt[t]*2){fl=0;break;}
			}
		}
		ans[n]=*ex.begin();
		if(!fl)puts("Impossible");
		else {
			for(int i=1;i<=n;i++)
				printf("%d%c",ans[i]," \n"[i==n]);
		}
	}	
	return 0;
}
