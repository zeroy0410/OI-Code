#include<bits/stdc++.h>
#define LL long long
#define M 400005 
using namespace std;
const int P=998244353;
LL rev[M],fac[M],Ifac[M];
LL qkpow(LL a,LL b){
    LL res=1;
    while(b){
        if(b&1)res=res*a%P;
        a=a*a%P;
        b>>=1;
    }
    return res;
}
void NTT(LL *A,int n,LL f){
    for(int i=0;i<n;i++)
        if(rev[i]<i)swap(A[i],A[rev[i]]);
    for(int m=1;m<n;m<<=1){
        LL wn=qkpow(3,(P-1)/(m<<1)*f%(P-1));
        for(int j=0;j<n;j+=m<<1){
            LL w=1;
            for(int k=0;k<m;k++){
                int u=A[j+k];
                int t=w*A[j+k+m]%P;
                A[j+k]=u+t;
                if(A[j+k]>=P)A[j+k]-=P;
                A[j+k+m]=u-t;
                if(A[j+k+m]<0)A[j+k+m]+=P; 
                w=w*wn%P;
            }
        }
    }
}
LL C[M],A[M],B[M],n,m,a;
int op[]={1,-1};
int main(){
//    freopen("data.in","r",stdin);
//    freopen("test.out","w",stdout);
    fac[0]=Ifac[0]=1;
    for(int i=1;i<M;i++){
        fac[i]=1LL*fac[i-1]*i%P; 
        Ifac[i]=Ifac[i-1]*qkpow(i,P-2)%P;
    }
    while(~scanf("%d",&n)){
        memset(A,0,sizeof(A));
        memset(B,0,sizeof(B));n++;
        for(int i=0;i<n;i++)scanf("%lld",&C[i]);
        scanf("%d",&m);a=0;LL x;
        for(int i=1;i<=m;i++)scanf("%lld",&x),a=(a+x)%P;
        LL tmp=A[0]=1;
        for(int i=1;i<n;i++){
            tmp*=a; tmp%=P; tmp=P-tmp;
            A[i]=tmp*Ifac[i]%P;
        }
        for(int i=0;i<n;i++)B[n-1-i]=1LL*C[i]*fac[i]%P;
        int nn=n,mm=n+n,c=0;
        for(nn=1;nn<mm;nn<<=1)c++;
        for(int i=0;i<nn;i++)rev[i]=(rev[i>>1]>>1)|((i&1)<<(c-1));
        NTT(A,nn,1);NTT(B,nn,1);
        for(int i=0;i<nn;i++)A[i]=1LL*A[i]*B[i]%P;
        NTT(A,nn,P-2);
        LL inv=qkpow(nn,P-2);
        for(int i=0;i<n;i++)
            printf("%d ",1LL*A[n-i-1]*inv%P*Ifac[i]%P); 
        printf("\n");
    }
    return 0;
}