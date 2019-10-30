#include<bits/stdc++.h>
using namespace std;
int i,i0,n,m,k,vis[1000005],pre[1000005],maxi,mini;
bool ans[1000005];
vector<int>mp[1000005],q;
int fin(int x){
    int tmp=x,tmp2;
    while(pre[tmp]!=tmp)tmp=pre[tmp];
    while(x!=tmp)tmp2=pre[x],pre[x]=tmp,x=tmp2;
    return tmp;
}
void uni(int x,int y){if(fin(x)!=fin(y))pre[fin(y)]=fin(x);}
void dfs(int now){
    if(vis[now])return;
    mini=min(mini,now),maxi=max(maxi,now);
    vis[now]=1;
    for(auto i:mp[now])dfs(i);
}
struct node{
    int l,r,i;
}qry[1000005];
vector<node>v;
bool cmp(const node &a,const node &b){return a.r<b.r;}
int main(){
    scanf("%lld %lld",&n,&k);
    for(i=1;i<=n;i++)pre[i]=i;
    while(k--){
        int x,y;
        scanf("%d %d",&x,&y);
        if(fin(x)==fin(y))q.push_back(x);
        else{
            uni(x,y);
            mp[x].push_back(y),mp[y].push_back(x);
        }
    }
    for(auto i:q)dfs(i);
    for(i=1;i<=n;i++){
        if(!vis[i]){
            mini=n,maxi=1,dfs(i);
			cout<<mini<<' '<<maxi<<endl;
            v.push_back({mini,maxi,0});
        }
    }
    scanf("%d",&m);
    for(i=1;i<=m;i++)scanf("%d %d",&qry[i].l,&qry[i].r),qry[i].i=i;
    sort(qry+1,qry+1+m,cmp),sort(v.begin(),v.end(),cmp);
    int maxl=0;
    for(i=1,i0=0;i<=m;i++){
        while(i0<v.size()&&v[i0].r<=qry[i].r)maxl=max(maxl,v[i0].l),i0++;
        if(maxl>=qry[i].l)ans[qry[i].i]=1;
    }
    for(i=1;i<=m;i++)printf("%s\n",ans[i]?"No":"Yes");
    return 0;
}
