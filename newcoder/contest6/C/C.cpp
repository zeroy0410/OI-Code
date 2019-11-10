#include<bits/stdc++.h>
#define LL long long
using namespace std;
const int P=19260817;
LL n,m;
LL fac[P-1],inv[P-1];
void init(){
    fac[0]=1;
    for(int i=1;i<P;i++)fac[i]=fac[i-1]*i%P;
    inv[0]=inv[1]=1;
    for(int i=2;i<P;i++)inv[i]=(P-P/i)*inv[P%i]%P;
    for(int i=1;i<P;i++)inv[i]=inv[i-1]*inv[i]%P;
}
LL C(LL n,LL m){
    if(n<m)return 0;
    if(n<P)return inv[m]*inv[n-m]%P*fac[n]%P;
    return C(n%P,m%P)*C(n/P,m/P)%P;
}
int main(){
    init();
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%lld%lld",&n,&m);
        printf("%lld\n",2*m%P*C(n+m-1,m)%P);
    }
    return 0;
}
