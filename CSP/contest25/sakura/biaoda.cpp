struct Edge{
    int u,v;
    Edge(int u=0,int v=0):u(u),v(v){}
}e[maxm];
int n,m,stamp,dfn[maxn],low[maxn],iscut[maxn],bccno[maxn];
int scnt,stack[maxm],bcc_cnt;
vector<int> vec[maxn],bcc[maxn];

void tarjan(int index,int fa)
{
    int child=0,tmp;
    dfn[index]=low[index]=++stamp;
    for(int i=0;i<vec[index].size();i++)
    {
        tmp=e[vec[index][i]].v;
        if(!dfn[tmp])
        {
            stack[++scnt]=vec[index][i],child++;
            tarjan(tmp,index);
            low[index]=min(low[index],low[tmp]);
            if(low[tmp]>=dfn[index])
            {
                iscut[index]=1;
                bcc[++bcc_cnt].clear();
                while(1)
                {
                    int num=stack[scnt--];
                    if(bccno[e[num].u]!=bcc_cnt)
                    {
                        bcc[bcc_cnt].push_back(e[num].u);
                        bccno[e[num].u]=bcc_cnt;
                    }
                    if(bccno[e[num].v]!=bcc_cnt)
                    {
                        bcc[bcc_cnt].push_back(e[num].v);
                        bccno[e[num].v]=bcc_cnt;
                    }
                    if(e[num].u==index && e[num].v==tmp)
                        break;
                }
            }
        }
        else if(dfn[tmp]<dfn[index] && tmp!=fa)
        {
            stack[++scnt]=vec[index][i];
            low[index]=min(low[index], dfn[tmp]);
        }
    }
    if(fa<0 && child==1)
        iscut[index]=0;
}

void find_bcc()
{
    // 割顶的bccno值无意义 
    memset(dfn,0,sizeof(dfn));
    memset(low,0,sizeof(low));
    memset(iscut,0,sizeof(iscut));
    memset(bccno,0,sizeof(bccno));
    memset(bcc,0,sizeof(bcc));
    stamp=scnt=bcc_cnt=0;
    for(int i=1;i<=n;i++)
        if(!dfn[i])
            tarjan(i,-1);
}
