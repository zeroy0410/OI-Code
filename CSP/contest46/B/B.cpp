#include<bits/stdc++.h>
#define M 1000005
using namespace std;
int T,A,B;
int X[M],Y[M];
struct node{int x,y;}P[M];
struct in{
	int l,r;
	bool operator < (const in& res)const{
		return r>res.r;
	}
}S[M];
priority_queue<in>Q;
bool cmp(in a,in b){
	return a.l<b.l;
}
bool check(int mid){
	int cur=1;
	while(!Q.empty())Q.pop();
	for(int i=1;i<=A+B;i++){
		while(cur<=T&&S[cur].l<=i)Q.push(S[cur++]);
		for(int j=1;j<=mid&&!Q.empty();j++){
			if(Q.top().r<i)return 0;
			Q.pop();
		}
	}
	return Q.empty();
}
int main(){
//	freopen("robots.in","r",stdin);
//	freopen("robots.out","w",stdout);
	scanf("%d%d%d",&A,&B,&T);
	for(int i=1;i<=A;i++)scanf("%d",&X[i]);
	for(int i=1;i<=B;i++)scanf("%d",&Y[i]);
	for(int i=1;i<=T;i++)scanf("%d%d",&P[i].x,&P[i].y);
	sort(X+1,X+A+1);sort(Y+1,Y+B+1);
	for(int i=1;i<=T;i++){
		int L=upper_bound(X+1,X+A+1,P[i].x)-X;
		int R=upper_bound(Y+1,Y+B+1,P[i].y)-Y;
		if(L>A&&R>B){puts("-1");return 0;}
		S[i]=(in){L,A+B-R+1};
	}
	int l=(T+A+B-1)/(A+B),r=T,ans=-1;
	sort(S+1,S+T+1,cmp);
	while(l<=r){
		int mid=(l+r)>>1;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
