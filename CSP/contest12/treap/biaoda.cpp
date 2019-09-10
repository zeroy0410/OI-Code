#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=1e6+5,P=998244353;
void rd(int &x){
    static char c;x=0;
    while((c=getchar())<48);
    do x=(x<<1)+(x<<3)+(c^48);
    while((c=getchar())>47);
}
int n,p;
int inv[M],v[M];
int h[M],nx[M<<1],to[M<<1],tot;
void add(int a,int b){
    to[++tot]=b;
    nx[tot]=h[a];
    h[a]=tot;
}
int sz[M];
int resx=1,resy=1,ansx=0,ansy=1,cnt=0;
void dfs(int x,int f){
    sz[x]=1;
    for(int i=h[x];i;i=nx[i]){
        int y=to[i];
        if(y==f)continue;
        dfs(y,x);
        sz[x]+=sz[y];
    }
    int p=v[sz[x]];
	cout<<sz[x]<<' '<<p<<endl;
    if(p)resx=(ll)resx*p%P;
    else cnt++;
}
void redfs(int x,int f){
    if(!cnt){
        ansx=((ll)ansx*resy+(ll)resx*ansy)%P;
        ansy=(ll)ansy*resy%P;
    }
    for(int i=h[x];i;i=nx[i]){
        int y=to[i];
        if(y==f)continue;
        int q=v[sz[y]],p=v[n-sz[y]];
        q?resy=(ll)resy*q%P:cnt--;
        p?resx=(ll)resx*p%P:cnt++;
        redfs(y,x);
        q?resx=(ll)resx*q%P:cnt++;
        p?resy=(ll)resy*p%P:cnt--;
    }
}
int Inv(int a){
    int res=1;
    for(int b=P-2;b;b>>=1){
        if(b&1)res=(ll)res*a%P;
        a=(ll)a*a%P;
    }
    return res;
}
int main(){
    rd(n),rd(p);
    inv[0]=inv[1]=1;
    for(int i=2;i<=n;i++)inv[i]=(ll)(P-P/i)*inv[P%i]%P;
    for(int i=0;i<=n;i++)v[i]=(ll)(i-1+p)*inv[i]%P;
    for(int a,b,i=1;i<n;i++){
        rd(a),rd(b);
        add(a,b),add(b,a);
    }
    dfs(1,0);
    redfs(1,0);
    printf("%lld\n",(ll)ansx*Inv(ansy)%P*inv[n]%P);
    return 0;
}
