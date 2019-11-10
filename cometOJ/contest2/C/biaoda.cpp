#include <bits/stdc++.h>
using namespace std;
#define M 200005
template<class T>bool tomax(T &x,T y){
    if(x<y)return x=y,1;
    return 0;
}
template<class T>bool tomin(T &x,T y){
    if(x>y)return x=y,1;
    return 0;
}
typedef long long LL;
int n,m;
int A[M],B[M];
struct Edge{
    int to,nx,w;
}edge[M<<1];
int h[M],tt;
void link(int a,int b,int w){
    edge[++tt].to=b;
    edge[tt].nx=h[a];
    edge[tt].w=w;
    h[a]=tt;
}
#define DEG(i,st) for(int i=h[st];i;i=edge[i].nx)
struct P3{
    int in[M],Q[M],nLoop[M];
    void Topo(){
        int L=0,R=-1;
        for(int i=1;i<=n;i++)
            if(!in[i])Q[++R]=i;
        while(L<=R){
            int now=Q[L++];
            nLoop[now]=1;
            in[A[now]]--;
            if(in[A[now]]==0)Q[++R]=A[now];
        }
    }
    int Val[M],Cant,RES,vis[M],Ans;
    void dfs(int now){
        Val[now]=0;
        DEG(i,now){
            int to=edge[i].to;
            if(!nLoop[to])continue;
            dfs(to);
            if(Val[to]+edge[i].w>m)RES++;
            else tomax(Val[now],Val[to]+edge[i].w);
        }
    }
    int P[M<<1],fa[M<<1][19];
    LL sum[M<<1];
    void Calc(int st){
        int len=0;RES=0;
        for(int i=st;!vis[i];){
            vis[P[++len]=i]=1,dfs(i);
            DEG(j,i)if(!nLoop[edge[j].to])i=edge[j].to;
        }
        // for(int i=1;i<=len;i++)
        //     printf("%d ",P[i]);
        // puts("");
        for(int i=1,ed=len;i<=ed;i++)P[++len]=P[i];
        for(int i=2;i<=len;i++){
            sum[i]=B[P[i]];
            sum[i]+=sum[i-1];
        }
        // for(int i=1;i<=len;i++)
        //     printf("%lld ",sum[i]);
        // puts("");
        for(int i=2;i<=len;i++){
            int l=1,r=i,res;
            while(l<=r){
                int mid=l+r>>1;
                if(sum[i]-sum[mid]+Val[P[i]]<=m)res=mid,r=mid-1;
                else l=mid+1;
            }
            fa[i][0]=res-1;
            for(int j=1;j<19;j++)
                fa[i][j]=fa[fa[i][j-1]][j-1];
        }
        int ans=1e9;
        for(int i=1;i<=len>>1;i++){
            int r=i+(len>>1)-1,res=0;
            for(int j=18;~j;--j)
                if(fa[r][j]>=i)
                    r=fa[r][j],res|=1<<j;
            tomin(ans,res);
        }
        Ans+=ans+RES+1;
    }
    void solve(){
        for(int i=1;i<=n;i++)in[i]=h[i]=vis[i]=nLoop[i]=0;tt=0;
        for(int i=1;i<=n;i++)in[A[i]]++;
        for(int i=1;i<=n;i++)link(A[i],i,B[i]);
        Topo();Ans=0;
        for(int i=1;i<=n;i++){
            if(nLoop[i]||vis[i])continue;
            Calc(i);
        }
        printf("%d\n",Ans);
    }
}p3;
int main(){
    int T;
    cin>>T;
    while(T--){
        scanf("%d%d",&n,&m);
        for(int i=1;i<=n;i++)
            scanf("%d%d",&A[i],&B[i]);
        p3.solve(); 
    }
    return 0;
}