#define FILE_NAME "stone"
#include<bits/stdc++.h>
using namespace std;
template<typename T>
bool tomin(T &x,T y) { if(y<x) { x=y; return true; } return false; }
template<typename T>
bool tomax(T &x,T y) { if(x<y) { x=y; return true; } return false; }
typedef long long ll;
#define lowbit(x) ((x)&-(x))
#define FILE_IO freopen(FILE_NAME".in","r",stdin);freopen(FILE_NAME".out","w",stdout)
const int M=5e5+5;
int n,q,L,R,A[M];
struct Queries {
	int x,y,z;
}Q[M];
int Get(int x) {
	for(int i=1;i<=q;i++) {
		if(x%Q[i].x==Q[i].y)
			x+=Q[i].z;
	}
	return x;
}
int FindL(int L,int R,int x) {
	int mid,Ans=INT_MAX;
	while(L<=R) {
		mid=(L+R)>>1;
		if(Get(mid)>=x) {
			Ans=mid;
			R=mid-1;
		} else L=mid+1;
	}
	return Ans;
}
int FindR(int L,int R,int x) {
	int mid,Ans=INT_MIN;
	while(L<=R) {
		mid=(L+R)>>1;
		if(Get(mid)<=x) {
			Ans=mid;
			L=mid+1;
		} else 
			R=mid-1;
	}
	return Ans;
}
void Solve() {
	int lo=INT_MAX,hi=INT_MIN;
	for(int i=1;i<=n;i++) {
		tomin(lo,A[i]);
		tomax(hi,A[i]);
	}
	L=FindL(lo,hi,L); R=FindR(lo,hi,R); 
	cout<<L<<' '<<R<<endl;
	int Ans=0;
	for(int i=1;i<=n;i++) {
		if(L<=A[i] && A[i]<=R) ++Ans;
	}
	cout<<Ans<<endl;
}
int main() {
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	for(int i=1;i<=q;i++) 
		scanf("%d%d%d",&Q[i].x,&Q[i].y,&Q[i].z);
	scanf("%d%d",&L,&R);
	Solve();
	return 0;
}
