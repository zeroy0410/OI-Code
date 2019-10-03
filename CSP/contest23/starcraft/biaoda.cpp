#include<bits/stdc++.h>
using namespace std;
struct Matrix{
    double a[30][30];
    Matrix operator *(const Matrix&b) const{
        Matrix ret;
        memset(ret.a,0,sizeof(ret.a));
        for(int i=1;i<=25;i++){
            for(int j=1;j<=25;j++){
                if(a[i][j]==0) continue;
                for(int l=1;l<=25;l++) ret.a[i][l]+=a[i][j]*b.a[j][l];
            }
        }
        return ret;
    }
};
Matrix ksm(Matrix x,int p){
    Matrix ret;
    memset(ret.a,0,sizeof(ret.a));
    for(int i=1;i<=25;i++) ret.a[i][i]=1;
    while(p){
        if(p&1) ret=ret*x;
        x=x*x;p>>=1;
    }
    return ret;
}
int main(){
    int n,m,t,k;
    scanf("%d%d%d%d",&n,&m,&t,&k);
    int nxt;
    Matrix ans;
    memset(ans.a,0,sizeof(ans.a));
    ans.a[1][1]=1;
    for(int i=1;i<=t;i=nxt+1){
        nxt=t/(t/i);
        Matrix m1;
        double p1=(t/i)*1.0/t;
        double p2=1-p1;
        for(int j=1;j<=m-n;j++) m1.a[j][j]=p2,m1.a[j+1][j]=p1;
        m1.a[m-n+1][m-n+1]=1;
        for(int j=1;j<=m-n+1;j++) m1.a[m-n+2][j]=n+j-1;
        m1.a[m-n+2][m-n+2]=1;
        ans=ksm(m1,nxt-i+1)*ans;
    }
    printf("%.8lf",ans.a[m-n+2][1]*k);
    return 0;
}
