#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
 
inline void Read(int &p)
{
    p=0;
    char c=getchar();
    while(c<'0' || c>'9') c=getchar();
    while(c>='0' && c<='9')
        p=p*10+c-'0',c=getchar();
}
 
const int MAXN=102030,MAXM=202030,mod=1e9+7;
 
long long tot[MAXN],cir[MAXN];
int n,m,u,v,cnt,deg[MAXN],arr[MAXN],head[MAXN],nxt[MAXM],to[MAXM];
 
inline void addedge(int u,int v)
{
    nxt[++cnt]=head[u],head[u]=cnt,to[cnt]=v,deg[u]++;
}
 
bool dcmp(int u,int v){return deg[u]==deg[v]?u>v:deg[u]>deg[v];}
 
int main()
{
    Read(n),Read(m);
    for(int i=1;i<=n;i++) Read(arr[i]);
    for(int i=1;i<=m;i++) Read(u),Read(v),addedge(u,v),addedge(v,u);
    for(int x=1;x<=n;x++)
    {
        for(int i=head[x];i;i=nxt[i])
            if(dcmp(x,to[i]))
                for(int j=head[to[i]];j;j=nxt[j])
                    if(dcmp(x,to[j])){
						cout<<x<<' '<<to[i]<<' '<<to[j]<<endl;
                        cir[x]+=tot[to[j]],cir[to[i]]+=tot[to[j]],cir[to[j]]+=tot[to[j]],++tot[to[j]];
					}
        for(int i=head[x];i;i=nxt[i])
            if(dcmp(x,to[i]))
                for(int j=head[to[i]];j;j=nxt[j])
                    if(dcmp(x,to[j]))
                        cir[to[i]]+=(--tot[to[j]]);    
    }
    long long ans=0;
    for(int i=1;i<=n;i++) {
		(ans+=1ll*arr[i]*cir[i])%=mod;
		cout<<cir[i]<<endl;
	}
    cout<<ans<<endl;
}
