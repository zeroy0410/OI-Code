include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char s[52];
int f[52][52];
int main() {
    int n;
    scanf("%s",s+1);
    n=strlen(s+1);
    memset(f,0x7F,sizeof(f));
    for(int i=1;i<=n;++i)
        f[i][i]=1;
    for(int l=1;l<n;++l) 
        for(int i=1,j=1+l;j<=n;++i,++j) {
            if(s[i]==s[j])
                f[i][j]=min(f[i+1][j],f[i][j-1]);
            else
                for(int k=i;k<j;++k)
                    f[i][j]=min(f[i][j],f[i][k]+f[k+1][j]);
        }
    printf("%d",f[1][n]);
    return 0;
}
