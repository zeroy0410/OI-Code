#include<bits/stdc++.h>
#define db double
#define M 35
using namespace std;
bool __1;
const int rx[]={1,-1,0,0};
const int ry[]={0,0,1,-1};
const db eps=1e-6;
int n,m,K,H,base;
int sx,sy;
int P[M];
char mp[M][M];
struct Poi{int x,y;};
vector<Poi>vec[M][M][M];
bool ok[M][M][M];
bool vis[M][M];
db po[M*M][5];
bool check(int x,int y){
    return x&&x<=n&&y&&y<=m&&mp[x][y]!='#';
}
bool isch(int x,int y){
    return mp[x][y]>='A'&&mp[x][y]<='Z';
}
void dfsfind(int x,int y,int a,int b,int st){
    vis[x][y]=1;
    for(int i=0;i<4;i++){
        int xx=x+rx[i];
        int yy=y+ry[i];
        if(!check(xx,yy)||vis[xx][yy])continue;
        if(mp[a][b]=='@')ok[xx][yy][st]=1;
        if(isch(xx,yy)){
            int c=mp[xx][yy]-'A';
            if(( (1<<c)&st )==0){
                vec[a][b][st].push_back((Poi){xx,yy});
                continue;
            }
        }
        dfsfind(xx,yy,a,b,st);
    }
}
void init(){
    for(int i=0;i<=base;i++){
        memset(vis,0,sizeof(vis));
        for(int x=1;x<=n;x++)
            for(int y=1;y<=m;y++)
                if(mp[x][y]=='@')
                    dfsfind(x,y,x,y,i);
    }
    for(int i=0,ed=(1<<(K<<1))-1;i<=ed;i++){
        bool f=1;
        int s1=0,s2=0;
        for(int j=0;f&&j<K;j++){
            int t=(i>>(j*2))&3;
            if(t==3){f=0;break;}
            if(t){
                s1|=(t-1)<<j;
                s2|=1<<j;
            }
        }
        if(!f)continue;
        int t=base^s2;
        for(int j=0;j<K;j++){
            int sum=0,p=0;
            for(int s=t;;s=(s-1)&t){
                sum+=P[s^s1];
                if((s^s1)&(1<<j))p+=P[s^s1];
                if(s==0)break;
            }
            po[i][j]=p*1.0/sum;
        }
    }
}
bool mark[M][M][M*M][6];
db dp[M][M][M*M][6];
db dfs(int x,int y,int S,int ss,int hp){
    if(hp<=0)return 0;
    if(mp[x][y]=='@'||ok[x][y][ss])return 1;
    if(mark[x][y][S][hp])return dp[x][y][S][hp];
    mark[x][y][S][hp]=1;
    db ans=0;
    if(vec[x][y][ss].empty()){
        memset(vis,0,sizeof(vis));
        dfsfind(x,y,x,y,ss);
    }
    for(int i=0,sz=vec[x][y][ss].size();i<sz;i++){
        int xx=vec[x][y][ss][i].x;
        int yy=vec[x][y][ss][i].y;
        int c=mp[xx][yy]-'A';
        db p=po[S][c],res=0;
        if(p>  eps)res+=p    *dfs(xx,yy,S|(2<<(c<<1)),ss,hp-1);
        if(p<1-eps)res+=(1-p)*dfs(xx,yy,S|(1<<(c<<1)),ss|(1<<c),hp);
        ans=max(ans,res);
    }
    return dp[x][y][S][hp]=ans;
}
bool __2;
int main(){
    scanf("%d%d%d%d",&n,&m,&K,&H);
    base=(1<<K)-1;
    for(int i=1;i<=n;i++)
        scanf("%s",mp[i]+1);
    for(int i=0;i<=base;i++)scanf("%d",&P[i]);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            if(mp[i][j]=='$')sx=i,sy=j;
    init();
    printf("%.3lf\n",dfs(sx,sy,0,0,H));
    return 0;
}
