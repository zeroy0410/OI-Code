#include <bits/stdc++.h>
using namespace std;
#define pb push_back
const int maxn=5e4+10;
const int maxm=1e5+10;
 
struct node{
    int l,r;
};
 
vector <int> pre[maxn];
node seg[maxm];
int maxx[4*maxn],laz[4*maxn];
int n,m,p,q,k;
 
void pushup(int cur){
    maxx[cur]=max(maxx[2*cur],maxx[2*cur+1]);
}
 
void pushdown(int cur){
    if(laz[cur]!=0){
        maxx[2*cur]+=laz[cur];
        laz[2*cur]+=laz[cur];
        maxx[2*cur+1]+=laz[cur];
        laz[2*cur+1]+=laz[cur];
        laz[cur]=0;
    }
}
 
void update(int pl,int pr,int val,int l,int r,int cur){
    int m;
    if(pl<=l&&r<=pr){
        maxx[cur]+=val;
        laz[cur]+=val;
        return;
    }
    pushdown(cur);
    m=(l+r)/2;
    if(pl<=m) update(pl,pr,val,l,m,2*cur);
    if(pr>m) update(pl,pr,val,m+1,r,2*cur+1);
    pushup(cur);
}
 
bool cmp(node n1,node n2){
    return n1.l<n2.l;
}
 
void solve(int id,int val){
    int i,gou;
    for(i=0;i<pre[id].size();i++){
        seg[i+1].l=pre[id][i],seg[i+1].r=min(m,pre[id][i]+q-1);
    }
    sort(seg+1,seg+pre[id].size()+1,cmp);
    gou=0;
    for(i=1;i<=pre[id].size();i++){
        if(seg[i].r>=gou+1){
            update(max(gou+1,seg[i].l),seg[i].r,val,1,m,1);
            gou=seg[i].r;
        }
    }
}
int main(){
    double ans;
    int t,i,j,gun,tar;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d%d%d%d",&n,&m,&p,&q,&k);
        for(i=1;i<=n;i++){
            pre[i].clear();
        }
        while(k--){
            scanf("%d%d",&gun,&tar);
            pre[gun].pb(tar);
        }
        for(i=1;i<=4*m;i++){
            maxx[i]=0,laz[i]=0;
        }
        for(i=1;i<=p-1;i++){
            solve(i,1);
        }
        ans=0.0;
        for(i=p;i<=n;i++){
            solve(i,1);
            ans+=(double)(maxx[1]);
            solve(i-p+1,-1);
        }
        printf("%.2f\n",ans/(double)(n-p+1));
    }
    return 0;
}
