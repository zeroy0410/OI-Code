#include<bits/stdc++.h>
#define For(a,b,c) for(int a=b,_=c;a<=_;++a)
#define Dor(a,b,c) for(int a=b,_=c;a>=_;--a)
#define LL long long
using namespace std;
const int N=100007,S=330;
struct W {
	int l,r,id;
};
bool cmp(W a,W b) {
	return a.r<b.r;
}
int n,m,e,A[N],C[N],E[N];
LL ANS[N];
vector<W>V[S];
int main() {
	freopen("history.in","r",stdin);
	freopen("history.out","w",stdout);
	scanf("%d%d",&n,&m);
	For(i,1,n) scanf("%d",&A[i]),E[i]=A[i];
	sort(E+1,E+1+n),e=unique(E+1,E+1+n)-E-1;
	For(i,1,n) A[i]=lower_bound(E+1,E+1+e,A[i])-E;
	int s=320,c=n/s;
	For(i,1,m) {
		int l,r;
		scanf("%d%d",&l,&r);
		V[l/s].push_back((W){l,r,i});
	}
	For(i,0,c) {
		int mx=0;
		sort(V[i].begin(),V[i].end(),cmp);
		memset(C,0,sizeof(C));
		For(j,0,(int)V[i].size()-1) mx=max(mx,V[i][j].l);
		int r=mx+1;
		LL a=0;
		For(j,0,(int)V[i].size()-1) {
			int Ql=V[i][j].l,Qr=V[i][j].r;
			LL b=0;
			while(r<=Qr) ++C[A[r]],a=max(a,1LL*E[A[r]]*C[A[r]]),++r;
			Dor(l,min(mx,Qr),Ql) ++C[A[l]],b=max(b,1LL*E[A[l]]*C[A[l]]);
			Dor(l,min(mx,Qr),Ql) --C[A[l]];
			ANS[V[i][j].id]=max(a,b);
		}
	}
	For(i,1,m) printf("%lld\n",ANS[i]);
	return 0;
}
