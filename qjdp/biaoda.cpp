#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define M 3030
using namespace std;
int n,p,a[M];
long long f[M][2][2];
int main()
{
    int i,j;
    cin>>n>>p;
    for(i=1;i<=n;i++)
        scanf("%d",&a[i]);
    a[++n]=p;
    sort(a+1,a+n+1);
    p=lower_bound(a+1,a+n+1,p)-a;
    memset(f,0x3f,sizeof f);
    f[p][1][0]=f[p][1][1]=0;
    for(j=2;j<=n;j++)
    {
        for(i=1;i<=n;i++)
            f[i][j&1][0]=f[i][j&1][1]=0x3f3f3f3f;
        for(i=max(p-j+1,1);i<=min(p,n-j+1);i++)
        {
            if(i!=p)
                f[i][j&1][0]=min(f[i+1][~j&1][0]+(n-j+1)*abs(a[i]-a[i+1]),f[i+1][~j&1][1]+(n-j+1)*abs(a[i]-a[i+j-1]));
            if(i!=p-j+1)
                f[i][j&1][1]=min(f[i][~j&1][0]+(n-j+1)*abs(a[i]-a[i+j-1]),f[i][~j&1][1]+(n-j+1)*abs(a[i+j-2]-a[i+j-1]));
        }
    }
    cout<<min(f[1][n&1][0],f[1][n&1][1])<<endl;
    return 0;
}