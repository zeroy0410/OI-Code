#include<bits/stdc++.h>
using namespace std;
int n,m,f[3005][3005],g[3005][3005],a[3005];
int main(){
    cin>>n>>m;
    memset(f,0x3f,sizeof(f));
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
        for(int j=i+1;j<=n;j++)
            for(int k=i;k<=j;k++)
                g[i][j]+=abs(a[k]-a[(j+i)/2]);
    for(int i=1;i<=m;i++)
        for(int j=1;j<=n;j++){
            for(int k=1;k<=j;k++)
                f[j][i]=min(f[j][i],f[k-1][i-1]+g[k][j]);
            if(i==1) f[j][1]=g[1][j];
        }
    cout<<f[n][m];    
}
