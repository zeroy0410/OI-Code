#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <cmath>
using namespace std;
const int N=50005;
int head[N],n,num=0,val[N],nxt[N<<1],to[N<<1],tot=0,r[N];
void link(int x,int y){nxt[++num]=head[x];to[num]=y;head[x]=num;}
void dfs1(int x,int last){
   int u,k;
   for(int i=head[x];i;i=nxt[i]){
      u=to[i];if(u==last)continue;
      dfs1(u,x);
      k=Min(val[x],val[u]);tot+=k<<1;
      val[x]-=k;val[u]-=k;
      if(val[u])r[x]=u;
   }
}
int ans[N];
void dfs(int x,int last){
   int u,flag;ans[x]=tot;
   for(int i=head[x];i;i=nxt[i]){
      u=to[i];if(u==last)continue;
      if(val[x])flag=1,tot++;
      else if(r[u])flag=2,tot++,val[r[u]]--;
      else flag=3,tot--,val[u]++;
      dfs(u,x);
      if(flag==1)tot--;
      else if(flag==2)tot--,val[r[u]]++;
      else tot++,val[u]--;
   }
}
void work()
{
   int x,y;
   scanf("%d",&n);
   for(int i=1;i<=n;i++)scanf("%d",&val[i]);
   for(int i=1;i<n;i++){
      scanf("%d%d",&x,&y);x++;y++;
      link(x,y);link(y,x);
      val[x]--;val[y]--;tot+=2;
   }
   dfs1(1,1);dfs(1,1);
   for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
}

int main()
{
    work();
    return 0;
}