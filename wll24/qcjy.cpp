#include <bits/stdc++.h>
#define M 105
using namespace std;
int n,K,A,B,C,mp[M][M];
int dis[15][M][M],Q[15][M][M];
int dx[]={1,0,-1,0};
int dy[]={0,1,0,-1};
struct node{int x,y,k;};
queue<node>q;
int spfa(){
    memset(dis,63,sizeof dis);
    dis[K][1][1]=0;
    Q[K][1][1]=1;q.push((node){1,1,K});
    while(!q.empty()){
        node now=q.front();q.pop();
        int x=now.x,y=now.y,k=now.k;
        Q[k][x][y]=0;
        int s=dis[k][x][y];
        if(k==0)
            s+=C+A,k=K;
        for (int i=0;i<4;i++){
            int X=x+dx[i],Y=y+dy[i];
            if(X<1||X>n||Y<1||Y>n)continue;
            int K1=k-1,S=s;
            if(mp[X][Y])
                K1=K,S+=A;
            if(X<x||Y<y)
                S+=B;
            if(dis[K1][X][Y]>S){
                dis[K1][X][Y]=S;
                if(!Q[K1][X][Y])
                    q.push((node){X,Y,K1}),Q[K1][X][Y]=1;
            }
        }
    }
    int ans=1e9;
    for(int i=0;i<=K;i++)ans=min(ans,dis[i][n][n]);
    return ans;
}
int main(){
    scanf("%d%d%d%d%d",&n,&K,&A,&B,&C);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)scanf("%d",&mp[i][j]);
    printf("%d\n",spfa());
    return 0;
}