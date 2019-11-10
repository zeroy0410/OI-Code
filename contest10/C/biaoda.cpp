#include<bits/stdc++.h>
#define M 4500
using namespace std;
int n,m,k;
namespace db{ double f[2][9001][101][3]; }
namespace f128{ __float128 f[2][9001][101][3]; }
template<class T>
inline void pout(T ans,int k){
    printf("%d.",(int)ans);
    while (k--) {
        ans=(ans-(int)ans)*10;
        if(!k) ans+=0.5;
        printf("%d",(int)ans);
    }
}
template<class T>
void solve(T f[][9001][101][3]){ T A;
    f[1][M-2][1][0]=1;f[1][M-1][1][1]=2;f[0][M][1][2]=1;
    for (int i=2,cur=0,pre=1;i<=n;i++,cur=pre,pre^=1) {
        memset(f[cur],0,sizeof f[cur]);
        for (int j=2*M;~j;j--) 
         for (int k=n-1;k;k--)
          for (int l=2;~l;l--) {
              if (!(A=f[pre][j][k][l])) continue;
              if (j+2*i<=2*M) f[cur][j+2*i][k-1][l]+=A*(k-1);
              if (j>=2*i) f[cur][j-2*i][k+1][l]+=A*(k+1-l);
              f[cur][j][k][l]+=A*(k*2-l);
              if (l<2) {
                  if (j+i<=2*M) f[cur][j+i][k][l+1]+=(2-l)*A;
                  if (j>=i) f[cur][j-i][k+1][l+1]+=A*(2-l);
              }
          }
    }
    T ans=0;for (int i=M+m;i<=2*M;i++) ans+=f[n&1][i][1][2];
    for (int i=2;i<=n;i++) ans/=i; 
    pout(ans,k);
}
int main () {
    scanf("%d %d %d",&n,&m,&k);
    if (k<=8) solve(db::f);
    else solve(f128::f);
    return 0;
}
