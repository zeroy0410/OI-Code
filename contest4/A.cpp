#include<bits/stdc++.h>
#define M 200005
using namespace std;
int n,m,A[M];
struct P10{
	void solve(){
		for(int i=1,op,x,y;i<=m;i++){
			scanf("%d%d",&op,&x);
			if(op==1){
				int ans=0;
				for(int j=1;j<=n;j++)
					if(A[j]>=x&&A[j-1]<x)ans++;
				printf("%d\n",ans);
			}
			else {
				scanf("%d",&y);
				A[x]=y;	
			}
		}
	}
}p10;
int ans[M],B[M<<1],sz,wcnt;
struct P100{
	struct BIT{
		int C[M<<1];
		void add(int x,int d){
			x++;
			while(x<=sz+1){
				C[x]+=d;
				x+=(x&-x);	
			}
		}
		int sum(int x){
			x++;int res=0;
			while(x){
				res+=C[x];
				x-=(x&-x);
			}
			return res;
		}
	}Tr;
	struct que{
		int id,op,x,y,d,qid;
		bool operator < (const que& res) const{
			if(x!=res.x)return x<res.x;
			return op<res.op;
		}
	}Q[M],wk[M<<2],tmp[M<<2];
	struct flo{int x,y;};
	vector<flo>vec;
	void CDQ(int l,int r){
		if(l==r)return;
		int mid=(l+r)>>1;
		CDQ(l,mid);CDQ(mid+1,r);vec.clear();
		int i=l,j=mid+1,k=l;
		while(i<=mid&&j<=r){
        	if(wk[i]<wk[j])tmp[k++]=wk[i++];
        	else tmp[k++]=wk[j++];
    	}
    	while(i<=mid)tmp[k++]=wk[i++];
    	while(j<=r)tmp[k++]=wk[j++];
    	for(int i=l;i<=r;i++)wk[i]=tmp[i];
		for(int i=l;i<=r;i++){
			if(wk[i].op==2&&wk[i].id<=mid){
				Tr.add(wk[i].y,wk[i].d);
				vec.push_back((flo){wk[i].y,wk[i].d});
			}
			else if(wk[i].op==1&&wk[i].id>=mid+1){
				ans[wk[i].qid]+=Tr.sum(sz)-Tr.sum(wk[i].x-1);
			}
		}
		for(int i=0;i<vec.size();i++)Tr.add(vec[i].x,-vec[i].y);
	}
	void solve(){
		sz=wcnt=0;B[++sz]=0;
		for(int i=1;i<=n;i++)B[++sz]=A[i];
		for(int i=1;i<=m;i++){
			scanf("%d%d",&Q[i].op,&Q[i].x);
			if(Q[i].op==2){scanf("%d",&Q[i].y);B[++sz]=Q[i].y;}
			else B[++sz]=Q[i].x;
			Q[i].id=i;
		}
		sort(B+1,B+sz+1);
		sz=unique(B+1,B+sz+1)-B-1;
		for(int i=0;i<=n;i++)A[i]=lower_bound(B+1,B+sz+1,A[i])-B;
		for(int i=1;i<=m;i++)
			if(Q[i].op==2)Q[i].y=lower_bound(B+1,B+sz+1,Q[i].y)-B;
			else Q[i].x=lower_bound(B+1,B+sz+1,Q[i].x)-B;
		for(int i=1;i<=n;i++){
			wk[++wcnt]=(que){wcnt,2,A[i-1],A[i],1,0};
		}
		for(int i=1;i<=m;i++){
			if(Q[i].op==1)wk[++wcnt]=(que){wcnt,1,Q[i].x,0,0,i};
			else {
				wk[++wcnt]=(que){wcnt,2,A[Q[i].x],A[Q[i].x+1],-1,0};
				wk[++wcnt]=(que){wcnt,2,A[Q[i].x-1],A[Q[i].x],-1,0};
				wk[++wcnt]=(que){wcnt,2,Q[i].y,A[Q[i].x+1],1,0};
				wk[++wcnt]=(que){wcnt,2,A[Q[i].x-1],Q[i].y,1,0};
				A[Q[i].x]=Q[i].y;
			}
		}
		CDQ(1,wcnt);
		for(int i=1;i<=m;i++)
			if(Q[i].op==1)printf("%d\n",ans[i]);
	}
}p100;
int main(){
	freopen("plan.in","r",stdin);
	freopen("plan.out","w",stdout);
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
//	if(n<=2000&&m<=2000)p10.solve();
	solve
	p100.solve();
	return 0;
}
