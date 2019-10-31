#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n,K,A[M];
struct node{
	int x,num;
	bool operator < (const node& res)const{
		return x>res.x;
	}
}L[M];
priority_queue<node>Q;
int main(){
	scanf("%d%d",&n,&K);
	for(int i=1;i<=n;i++)scanf("%d",&A[i]);
	return 0;
}
