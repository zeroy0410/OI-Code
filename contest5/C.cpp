#include<bits/stdc++.h>
#define M 100005
#define S 330 
#define LL long long 
using namespace std;
struct node{
	int l,r,id;
	bool operator < (const node& res) const{return r<res.r;}
};
int n,m,A[M],B[M],bn,cnt[M]; 
LL ans[M],val[M],Ans;
vector<node>vec[S];
void update(int x,int d){
	x=A[x];
	Ans=max(Ans,val[x]+=1LL*d*B[x]);
}
int main(){
	freopen("history.in","r",stdin);
	freopen("history.out","w",stdout); 
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]),B[i]=A[i];
	sort(B+1,B+n+1);bn=unique(B+1,B+n+1)-B-1;
	for(int i=1;i<=n;i++)A[i]=lower_bound(B+1,B+bn+1,A[i])-B;
	int s=320,c=n/s;
	for(int i=1,l,r;i<=m;i++){
		scanf("%d%d",&l,&r);
		vec[l/s].push_back((node){l,r,i});
	}
	int L=0,R=0;
	for(int i=0;i<=c;i++){
		sort(vec[i].begin(),vec[i].end());
		if(vec[i].size()){ 
			Ans=0;memset(val,0,sizeof(val)); 
			int lim=min(i*S+S-1,n),L=lim,R=lim;
			LL tmp;update(L,1);
			for(int j=0;j<vec[i].size();j++){
				int l=vec[i][j].l,r=vec[i][j].r,id=vec[i][j].id; 
				if(r>=lim){
					while(R<r)update(++R,1);
					tmp=Ans;
					while(L>l)update(--L,1); 
					ans[id]=Ans;
					while(L<lim)update(L++,-1);
					Ans=tmp;
				}
				else{
					LL &mx=ans[id];
					for(int k=l;k<=r;k++)mx=max(mx,1LL*B[A[k]]*(++cnt[A[k]]));	
					for(int k=l;k<=r;k++)cnt[A[k]]=0;
				}
			}
		}
	}
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
	return 0;
}
