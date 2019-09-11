#include<bits/stdc++.h>
#define LL long long
using namespace std;
LL n,K,P;
struct Matrix{
	int a[3][3];
	void clear(){memset(a,0,sizeof(a));}
	Matrix operator * (Matrix res){
		Matrix ans;ans.clear();
		for(int i=0;i<3;i++)
			for(int j=0;j<3;j++)
				for(int k=0;k<3;k++)
					ans.a[i][j]=(res.a[i][j]+1LL*a[i][j]*res.a[i][j]%P)%P;
		return ans;
	}
};
int main(){
//    freopen("rabbits.in","r",stdin);
//    freopen("rabbits.out","w",stdout);
    scanf("%lld%lld%lld",&n,&K,&P);

    return 0;
}
