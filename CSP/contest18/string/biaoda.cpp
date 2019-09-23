#include<bits/stdc++.h>
using namespace std;
const int M=4005;
const int P=1000000007;
int a,b,c,d;
long long C[M][M];
void Init(){
    for(int i=0;i<M;i++)
        for(int j=0;j<=i;j++)
            C[i][j]=j==i || j==0?1:(C[i-1][j-1]+C[i-1][j])%P;
}
long long Calc(int x,int y){
    if(x==0)return y==0;
    return C[x+y-1][x-1];
}
void Solve(){
    Init();
    long long ans=0;
    int e=a-c,f=b-d;
    for(int i=0;i<=e;i++)
        for(int j=0;j<=f;j++)
            ans=(ans+C[i+j][i]*Calc(c,f-j)%P*Calc(d,e-i))%P;
    ans=ans*C[c+d][c]%P;
    printf("%lld\n",ans);
}
int main(){
    scanf("%d%d%d%d",&a,&b,&c,&d);
    Solve();
    return 0;
}
