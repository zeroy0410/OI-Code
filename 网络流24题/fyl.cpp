#include<bits/stdc++.h>
#define M 5005
using namespace std;
int n,m,h[M],tt;
int s,t;
struct edge{
    int nxt,to,co,fe;
}G[M*20];
void Add(int a,int b,int c,int f){
    G[++tt]=(edge){h[a],b,c,f};
    h[a]=tt;
}
void SPFA(){
    
}
int main(){
    scanf("%d%d%d%d",&n,&m,&s,&t);
    for(int i=1,a,b,c,f;i<=m;i++){
        scanf("%d%d%d%d",&a,&b,&c,&f);
        Add(a,b,c,f);
        Add(b,a,0,-f);
    }
    
    return 0;
}