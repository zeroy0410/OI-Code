#include<bits/stdc++.h>
#define LL long long
#pragma GCC optimize(3)
#define M 10005
using namespace std;
int n,W,K;
struct node{int a,b;}A[M];
struct Sta{
	int Ldp[M][5005],DP[5005],Ra[M],Rb[M],top1,top2;
	void Init(){
		memset(Ldp,60,sizeof(Ldp));
		memset(DP,60,sizeof(DP));
		Ldp[0][0]=DP[0]=0;
		top1=top2=0;
	}
	void Push(int a,int b){
		++top2;Ra[top2]=a;Rb[top2]=b;
		for(int i=W;i>=a;i--)DP[i]=min(DP[i],DP[i-a]+b);
	}
	void Pop(){
		if(top1>0){top1--;return;}
		for(int i=top2;i>=1;i--){
			int a=Ra[i],b=Rb[i];
			++top1;
			for(int j=0;j<=W;j++)Ldp[top1][j]=Ldp[top1-1][j];
			for(int j=W;j>=a;j--)Ldp[top1][j]=min(Ldp[top1][j],Ldp[top1][j-a]+b);
		}
		top2=0; memset(DP,60,sizeof(DP));DP[0]=0;
		top1--;
	}
	bool check(){
		for(int i=0;i<=W;i++)
			if(Ldp[top1][i]+DP[W-i]<=K)
				return 1;
		return 0;
	}
}stk;
bool mark[M];
int main(){
	cin>>n>>W>>K;
	for(int i=1;i<=n;i++)
		scanf("%d%d",&A[i].a,&A[i].b);
	stk.Init();
	int R=1,ans=1e9;
	for(int L=1;L<=n;L++){
		while(R<=n){
			if(!mark[R])stk.Push(A[R].a,A[R].b),mark[R]=1;
			if(stk.check())break;
			R++;
		}
		if(R>n)break;
		ans=min(ans,R-L+1);
		stk.Pop();
	}
	if(ans==1e9)ans=-1;
	printf("%d\n",ans);
	return 0;
}
