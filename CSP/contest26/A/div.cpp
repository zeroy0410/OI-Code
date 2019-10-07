#include<bits/stdc++.h>
#define M 205
using namespace std;
const int mx=100005;
bool mm1;
int n,m,A[M],B[M];
int pri[mx+5],pc;
bool mark[mx+5];
struct P0{
    int cnt[205];
    void solve(){
        memset(cnt,0,sizeof(cnt));
        for(int i=1;i<=n;i++){
            int c=0;
            for(int j=1;j<=m;j++)
                if(A[j]%i==0)c++;
            cnt[c]++;
        }
        for(int i=0;i<=m;i++)
            printf("%d\n",cnt[i]);
    }
}p0;
struct P1{
    void Init(){
        pc=0;
        for(int i=2;i<=mx;i++){
            if(!mark[i])pri[++pc]=i;
            for(int j=i+i;j<=mx;j+=i)
                mark[j]=1;
        }
    }
    int ct[mx+5],ans[205];
    map<int,int>mp;
    map<int,int>::iterator it;
    vector<bitset<205>>ca[10005];
    bitset<205>tmp;
    bitset<205>st;
    bitset<205>em;
    void solve(){
        Init();mp.clear();
        for(int i=1;i<=m;i++)B[i]=A[i];
        st.reset();em.reset();
        for(int i=1;i<=m;i++)st[i]=1;
        for(int i=1;i<=m;i++){
            for(int j=1;j<=pc;j++){
                if(B[i]%pri[j]==0){
                    int c=0;
                    while(B[i]%pri[j]==0){
                        c++;
                        B[i]/=pri[j];
                    }
                    while(ca[j].size()<c+1)ca[j].push_back(em);
                    ca[j][c][i]=1;
                }
                if(B[i]==1)break;
            }
            if(B[i]!=1)mp[B[i]]++;
        }
        for(int i=1;i<=pc;i++){
            if(ca[i].size()==0)continue;
            for(int j=ca[i].size()-2;j>=0;j--){
                ca[i][j]|=ca[i][j+1];
            }
        }
        for(int i=1;i<=min(mx,n);i++){
            tmp=st;int x=i;
            for(int j=1;j<=pc;j++){
                if(x%pri[j]==0){
                    int c=0;
                    while(x%pri[j]==0){
                        c++;
                        x/=pri[j];
                    }
                    if((int)ca[j].size()-1<c)tmp.reset();
                    else tmp&=ca[j][c];
                }
                if(x==1)break;
            }
            ans[tmp.count()]++;
        }
        for(it=mp.begin();it!=mp.end();it++)
            ans[it->second]++;
        for(int i=0;i<=m;i++)
            printf("%d\n",ans[i]);
    }
}p1;
bool mm2;
int main(){
    freopen("div.in","r",stdin);
    freopen("div.out","w",stdout);
    scanf("%d%d",&n,&m);
    for(int i=1;i<=m;i++)scanf("%d",&A[i]);
    p1.solve();
    return 0;
}