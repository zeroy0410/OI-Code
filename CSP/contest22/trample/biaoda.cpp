
#include<bits/stdc++.h>
#define rep(i,x,y) for (int i=(x);i<=(y);i++)
#define ll long long
using namespace std;
const int N=3005;
int n,ans,m,now,q[N*3],id[N*3]; ll f[2][N*3]; bool flag;
struct node{ int l,r,p; }a[N];
bool cmp(node x,node y){ return x.p<y.p; }
int main(){
    scanf("%d",&n);
    rep (i,1,n) scanf("%d%d%d",&a[i].p,&a[i].l,&a[i].r),q[++m]=a[i].p-a[i].l,q[++m]=a[i].p+a[i].r,q[++m]=a[i].p;
    sort(q+1,q+1+m); m=unique(q+1,q+1+m)-q-1; sort(a+1,a+1+n,cmp);
    rep (i,1,n){
        a[i].l=lower_bound(q+1,q+1+m,a[i].p-a[i].l)-q;
        a[i].r=lower_bound(q+1,q+1+m,a[i].p+a[i].r)-q;
        a[i].p=lower_bound(q+1,q+1+m,a[i].p)-q;
        id[a[i].p]=i;
    }
    //f[i][j]表示前i个区间，已经覆盖到位置j，最大覆盖长度
    rep (i,1,n){
        now^=1;
        rep (j,1,m) f[now][j]=f[now^1][j];
        rep (j,a[i].l+1,a[i].p)//往左照
            f[now][j]=max(f[now][j],f[now][j-1]+q[j]-q[j-1]);
        ll mx=f[now^1][a[i].p];
        rep (j,a[i].p+1,a[i].r){//往右照
            f[now][j]=max(f[now][j],mx+q[j]-q[a[i].p]);//之前往左照不相交或往右照
            if (id[j]&&a[id[j]].l<a[i].p)//之前的往左照且相交
                mx=max(mx,f[now^1][a[id[j]].l]+q[a[i].p]-q[a[id[j]].l]);
        }
        rep (j,1,m) f[now][j]=max(f[now][j],f[now][j-1]);
    }
    cout<<f[now][m];
    return 0;
}
