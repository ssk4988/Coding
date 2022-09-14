#include <bits/stdc++.h>
#include <cstring>
using namespace std;

const int mxn=1e5+1;
long long n,p,k,dp[mxn][1<<8];

struct info{
	long long a,P[8];
} e[mxn];

bool cmp(info a, info b){
	return a.a > b.a;
}

int main(){
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> p >> k;
	for(int i=1;i<=n;i++)
		cin >> e[i].a;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=p;j++)
			cin >> e[i].P[j];
	sort(e+1,e+n+1,cmp);
	memset(dp, -1, sizeof(dp));
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int s=0;s<1<<p;s++){
			int num=__builtin_popcount(s);
			if(dp[i-1][s]!=-1){
				dp[i][s]=dp[i-1][s];
				if(i-num-1<k) dp[i][s]+=e[i].a;
			}
			for(int j=1;j<=p;j++){
				if(!(1<<(j-1)&s)) continue;
				if(dp[i-1][s^(1<<(j-1))]!=-1)
					dp[i][s]=max(dp[i][s],dp[i-1][s^(1<<(j-1))]+e[i].P[j]);
			}
		} 
	}
	cout << dp[n][(1<<p)-1];
}