#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define N 70010
inline void update(int &a,int b){a>b?a=b:0;}
int _n,n;
char _s[N],s[N];
int nex[N][11];
bool must[N];
int f[N][11],g[N][11][11];
int ans;
int main(){
    scanf("%d%s",&_n,_s+1);
    ans=0;
    for (int i=1;i<=_n;++i)
        if (_s[i]=='e')
            ans+=2;
        else{
            s[++n]=_s[i];
            if (_s[i-1]=='e')
                must[n]=1;
        }
    memset(nex[n+1],1,sizeof nex[n+1]);
    s[n+1]='k';
    for (int i=1;i<=n+1;++i)
        s[i]-='a';
    for (int i=n;i>=1;--i){
        memcpy(nex[i],nex[i+1],sizeof nex[i]);
        nex[i][s[i+1]]=i+1;
    }
    memset(f,127,sizeof f);
    memset(g,127,sizeof g);
    f[0][s[1]]=0;
    for (int i=1;i<=n;++i){
        for (int j=0;j<=10;++j){
            if (j!=s[i]){
                if (!must[i])
                    update(f[i][j],f[i-1][j]);
                update(f[i][j],g[i-1][s[i]][j]);
            }
            update(f[i][j],f[i-1][s[i]]+2);
            update(f[i][j],g[i-1][s[i]][s[i]]+2);
        }
        for (int j=0;j<=10;++j)
            for (int k=0;k<=10;++k){
                if (j!=s[i]){
                    update(g[i][j][k],f[i-1][j]+nex[i][j]-i+2);
                    if (k!=s[i])
                        update(g[i][j][k],g[i-1][j][k]);
                    update(g[i][j][k],g[i-1][j][s[i]]+2);
                }
                update(g[i][j][k],f[i-1][s[i]]+nex[i][j]-i+4);
                if (k!=s[i])
                    update(g[i][j][k],g[i-1][s[i]][k]+nex[i][j]-i+2);
                update(g[i][j][k],g[i-1][s[i]][s[i]]+nex[i][j]-i+4);
            }
    }
    ans+=f[n][10]-2;
    printf("%d\n",ans);
    return 0;
}
