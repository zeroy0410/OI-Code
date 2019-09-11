#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>

#define MAXE 12000
#define MAXV 3000
#define MAXN 1000

using namespace std;

struct edge
{
    int u,v,next;
}edges[MAXE];

int head[MAXV],nCount=0;

void AddEdge(int U,int V)
{
    edges[++nCount].u=U;
    edges[nCount].v=V;
    edges[nCount].next=head[U];
    head[U]=nCount;
}

int pre[MAXV],vis[MAXV],tot=0;
bool deleted[MAXV]; 
bool res[MAXV];

bool DFS(int u)
{
	cout<<u<<endl;
    for(int p=head[u];p!=-1;p=edges[p].next)
    {
        int v=edges[p].v;
        if(deleted[v]) continue;
        if(vis[v]==tot) continue;
        vis[v]=tot;
        if(pre[v]==-1||DFS(pre[v]))
        {
            pre[v]=u;
            pre[u]=v; 
            return true;
        }
    }
    return false;
}

int n,m,q;

char map[MAXN][MAXN];
int num[MAXN][MAXN],cnt=0;

int main()
{
    memset(head,-1,sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        scanf("%s",map[i]+1);
    int blankx,blanky;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(map[i][j]=='.')
            {
                blankx=i;
                blanky=j;
                break;
            }
    map[blankx][blanky]='X'; 
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if((map[i][j]=='O'&&(abs(i-blankx)+abs(j-blanky))%2==1)||(map[i][j]=='X'&&(abs(i-blankx)+abs(j-blanky))%2==0))
                num[i][j]=++cnt;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(num[i][j])
            {
                if(num[i-1][j]) AddEdge(num[i][j],num[i-1][j]);
                if(num[i+1][j]) AddEdge(num[i][j],num[i+1][j]);
                if(num[i][j-1]) AddEdge(num[i][j],num[i][j-1]);
                if(num[i][j+1]) AddEdge(num[i][j],num[i][j+1]);
            }
    memset(pre,-1,sizeof(pre)); 
    for(int i=1;i<=cnt;i++)
        if(pre[i]==-1)
        {
            tot++;
            DFS(i);
        }
    scanf("%d",&q);
    q<<=1;
    for(int i=1;i<=q;i++)
    {
        if(pre[num[blankx][blanky]]!=-1) 
        {
            int tmp=pre[num[blankx][blanky]]; 
            pre[num[blankx][blanky]]=pre[tmp]=-1; 
            deleted[num[blankx][blanky]]=true;
            tot++;
            res[i]=DFS(tmp);
        }
        else
        {
            deleted[num[blankx][blanky]]=true;
            res[i]=true;
        }
        scanf("%d%d",&blankx,&blanky);
    }
    int ans=0;
    for(int i=1;i<=q;i+=2)
        if(!res[i]&&!res[i+1])
            ans++;
    printf("%d\n",ans);
    for(int i=1;i<=q;i+=2) 
 		if(!res[i]&&!res[i+1])
            printf("%d\n",(i+1)>>1);
    return 0;
}

