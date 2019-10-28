#include<bits/stdc++.h>
#define max(x,y) ((x)>(y)? (x):(y))
using namespace std;
const int N=1e5+5;
int n,m,R,a[N],q[N],tr[N],Up,c[N],z[N],y[N],ma=-1,d,W[17][N],up[N];
void Max(int &x,int y){(x<y)&&(x=y);}
int maQr(int z,int y){
    int ll=up[y-z];
    return max(W[ll][z],W[ll][y-(1<<ll)]);
}
void Ad(int i){
    for(;i<=n;i+=i&-i)tr[i]--;
}
int Qr(int w){
    int rs=0,nw=0;
    for(int i=Up;i;i>>=1){
        if(rs+i<=n&&nw+tr[rs+i]<w)nw+=tr[rs+=i];
    }
    return rs+1;
}
void Rd(int &x){
    x=0;char c=getchar();
    while(!isdigit(c))c=getchar();
    while(isdigit(c)){x=(x<<1)+(x<<3)+c-48;c=getchar();}
}
int main(){
    freopen("tournament.in","r",stdin);
    freopen("tournament.out","w",stdout);
    Rd(n);Rd(m);Rd(R);
    for(int i=1;i<n;++i){
        Rd(W[0][i]);
        tr[i]=i&-i;
        z[i]=y[i]=i;
    }
    for(Up=1;Up<=n;Up<<=1);Up>>=1;
    for(int i=2;i<=n;++i)up[i]=up[i>>1]+1;
    for(int i=n;i;i--){
        for(int o=1,u=1;o<=up[n-i+1];o++,u<<=1){
            W[o][i]=max(W[o-1][i],W[o-1][i+u]);
        }
    }
    tr[n]=n&-n;z[n]=y[n]=n;
    int l,r;
    for(int i=1;i<=m;++i){
        Rd(l);Rd(r);
        l++;r++;ma=0;
        for(int o=l;o<=r;++o)q[o]=Qr(o);
        if(maQr(z[q[l]],y[q[r]])<R){
            c[z[q[l]]]++;c[y[q[r]]]--;
        }
        for(int o=l;o<r;++o)Ad(q[o]);
        z[q[r]]=z[q[l]];
    }
    for(int i=1;i<=n;++i){
        c[i]+=c[i-1];
        if(c[i]>ma){
            ma=c[i];d=i-1;
        }
    }
    printf("%d\n",d);
    fclose(stdin);fclose(stdout);
    return 0;
}
