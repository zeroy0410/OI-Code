#include<bits/stdc++.h>
using namespace std;
#define M 805
const int dx[]={0,0,1,-1};
const int dy[]={1,-1,0,0};
bool tomin(double& x,double y){
    if(x>y){x=y;return 1;}
    return 0;
}  
int n;
int X[M],szx;
int Y[M],szy;
int mp[M][M];
struct Edge{
    int x1,x2,y1,y2;
    void Rd(){
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        x1<<=1; x2<<=1; y1<<=1; y2<<=1;
        X[++szx]=x1; X[++szx]=x2; X[++szx]=x1-1; X[++szx]=x2+1;
        Y[++szy]=y1; Y[++szy]=y2; Y[++szy]=y1-1; Y[++szy]=y2+1;
    }
    void uni(){
        x1=lower_bound(X+1,X+szx+1,x1)-X;
        x2=lower_bound(X+1,X+szx+1,x2)-X;
        y1=lower_bound(Y+1,Y+szy+1,y1)-Y;
        y2=lower_bound(Y+1,Y+szy+1,y2)-Y;
    }
    void cvr(){
        for(int i=x1;i<=x2;i++)
            for(int j=y1;j<=y2;j++)
                mp[i][j]++;
    }
}A[M];
struct node{
    int x,y;
    double d;
    bool operator <(const node &A)const{
        return d>A.d;
    }
};
priority_queue<node>q;
double dis[M][M];
bool vis[M][M];
double Dis(int x1,int y1,int x2,int y2){
    return (double)(abs(X[x1]-X[x2])+abs(Y[y1]-Y[y2]))/min(mp[x1][y1],mp[x2][y2]);
}
void Dijk(){
    for(int i=1;i<=szx;i++)
        for(int j=1;j<=szy;j++){
        dis[i][j]=1e100;
        vis[i][j]=0;
    }
    dis[A[0].x1][A[0].y1]=0;
    while(!q.empty())q.pop();
    q.push((node){A[0].x1,A[0].y1,0});
    while(!q.empty()){
        node tmp=q.top();q.pop();
        int x=tmp.x,y=tmp.y;
        if(vis[x][y])continue;
        vis[x][y]=1;
        if(x==A[0].x2&&y==A[0].y2){
            printf("%.5lf\n",dis[x][y]/2);
            return;
        }
        for(int i=0;i<4;i++){
            int xx=x+dx[i];
            int yy=y+dy[i];
            if(mp[xx][yy]&&tomin(dis[xx][yy],dis[x][y]+Dis(x,y,xx,yy)))
                q.push((node){xx,yy,dis[xx][yy]});
        }
    }
}
int main(){
    int T;
    scanf("%d",&T);
    while(T--){
        szx=szy=0;
        scanf("%d",&n);
        for(int i=1;i<=n;i++)A[i].Rd();A[0].Rd();
        sort(X+1,X+szx+1);
        szx=unique(X+1,X+szx+1)-X-1;
        sort(Y+1,Y+szy+1);
        szy=unique(Y+1,Y+szy+1)-Y-1;
        for(int i=0;i<=n;i++)A[i].uni();
        memset(mp,0,sizeof(mp));
        for(int i=1;i<=szx;i++)
            for(int j=1;j<=szy;j++)
                mp[i][j]=1;
        for(int i=1;i<=n;i++)A[i].cvr();
        Dijk();
    }
    return 0;
}
