#include<bits/stdc++.h>
#define M 100005
using namespace std;
int n,A[M];
double sum,sum2,sum3;
int main(){
	freopen("data.in","r",stdin);
	freopen("data.out","w",stdout);
	scanf("%d",&n);sum=sum2=sum3=0.0;
	for(int i=1;i<=n;i++)scanf("%d",&A[i]),sum+=A[i];
	double p=sum/n;
	for(int i=1;i<=n;i++){
		sum2+=(A[i]-p)*(A[i]-p);
		sum3+=2*(A[i]-p);
	}
	for(int i=1;i<=n;i++){
		double nowp=1.0*(sum-A[i])/(n-1);
		double res=-nowp+p;
		double nowsum=sum2-(A[i]-p)*(A[i]-p);
		double nowsum3=sum3-2*(A[i]-p);
		nowsum+=nowsum3*res+res*res*(n-1);
		double ans=1.0*nowsum*(n-1);
		printf("%.0lf ",ans);
	}
	return 0;
}
