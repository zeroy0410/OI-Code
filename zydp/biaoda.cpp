#include<iostream>
#include<cstdio>
using namespace std;
const int mod=1000000007;
int n,m,p,temp,f[35][35][(1<<9)+5][9];
int main()
{
    scanf("%d%d%d",&n,&m,&p);
    temp=(1<<(p+1))-1;
    f[1][0][0][0]=1;
    for(int i=1;i<=n;i++)
     for(int j=0;j<=m;j++) 
      for(int k=0;k<=temp;k++)
      {
        for(int l=0;l<p;l++)
          if(f[i][j][k][l])
          {
            f[i][j][k][l+1]=(f[i][j][k][l+1]+f[i][j][k][l])%mod;
            if(j+1<=m&&i-p+l>=1)
              f[i][j+1][k^(1<<p)^(1<<l)][l]=(f[i][j+1][k^(1<<p)^(1<<l)][l]+f[i][j][k][l])%mod;
          }
        if((!(k&1))&&f[i][j][k][p])
           f[i+1][j][k>>1][0]=f[i][j][k][p]%mod;
      }
    printf("%d",f[n+1][m][0][0]);
    return 0;
}

road
