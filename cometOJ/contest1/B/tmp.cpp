// struct P0{
// 	int mx;
// 	bool ca(int x){
// 		if(S[x]=='#'&&S[x-1]!='*'&&S[x+1]!='*')return 0;
// 		return 1;
// 	}
// 	bool mark[M];
// 	void dfs(int x,int hv){
// 		mx=max(mx,hv);
// 		if(x<n&&ca(x+1))dfs(x+1,hv);
// 		if(S[x]=='*'&&!mark[x]){
// 			mark[x]=1;
// 			S[x]='.';
// 			dfs(x,hv+1);
// 			S[x]='*';
// 			mark[x]=0;
// 		}
// 		if(S[x]=='.'&&hv&&!mark[x]){
// 			mark[x]=1;
// 			S[x]='*';
// 			dfs(x,hv-1);
// 			S[x]='.';
// 			mark[x]=0;
// 		}
// 	}
// 	void solve(){
// 		mx=0;
// 		dfs(1,0);
// 		printf("%d\n",mx);
// 	}
// }p0;