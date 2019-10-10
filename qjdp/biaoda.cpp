#include <bits/stdc++.h>
using namespace std;
#define N 2005
int A[N],dp[N][N],head[N],tail[N],Q[N][N];
int Calc_1(int l,int r) {
	return dp[l][r-1] + A[r];
}
int Calc_2(int l,int r) {
	return dp[l+1][r] + A[l];
}
int main() {
	int n;
	cin >> n;
	for(int i=1; i<=n; i++) scanf("%d",&A[i]);
	memset(dp,61,sizeof(dp));
	for(int i=n; i>=1; i--) {
		dp[i][i] = A[i];
		head[0] = 1,tail[0] = 0;
		for(int j=i+1; j<=n; j++) {
			while(head[0] <= tail[0] && Calc_1(i,Q[0][head[0]]) < Calc_2(Q[0][head[0]],j)) head[0] ++;
			while(head[0] <= tail[0] && Calc_1(i,j) < Calc_1(i,Q[0][tail[0]])) tail[0] --;
			Q[0][++tail[0]] = j;

			while(head[j] <= tail[j] && Calc_2(Q[j][head[j]],j) < Calc_1(i,Q[j][head[j]])) head[j] ++;
			while(head[j] <= tail[j] && Calc_2(i,j) < Calc_2(Q[j][tail[j]],j)) tail[j] --;
			Q[j][++tail[j]] = i;
			
			dp[i][j] = min(Calc_1(i,Q[0][head[0]]),Calc_2(Q[j][head[j]] ,j ) );
		}
	}

	cout << dp[1][n] << endl;
	return 0;
}
