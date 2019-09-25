#include<cstdio>
#include<string.h>
#include<algorithm>
#define M 1000005
using namespace std;
int n,A[M];
int gcd(int a,int b){return b==0?a:gcd(b,a%b);}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	return 0;
}
