#include <bits/stdc++.h>
using namespace std;
typedef long double ld;

vector<int> read_vector(){
  int n; cin>>n;
  vector<int> res(n); for (auto &i: res) cin>>i;
  return res;
}

int main(){
  vector<int> items=read_vector();
  vector<int> spots=read_vector();
  ld const angle=M_PI*2.L/spots.size();

  vector<vector<ld>> dp(items.size()+1,vector<ld>(spots.size(), 1e60L));
  for (int i=spots.size(); i--;)
    if (items[0]==spots[i])
      dp[0][i]=1.L;

  for (int i=1; i<items.size(); i++)
    for (int j=0; j<spots.size(); j++)
      if (spots[j]==items[i])
        for (int k=0; k<spots.size(); k++)
          dp[i][j]=min(dp[i][j], dp[i-1][k]+hypotl(cos(j*angle)-cos(k*angle), sin(j*angle)-sin(k*angle)));

  ld res=1e60L;
  for (int i=spots.size(); i--;)
    res=min(res,dp[items.size()-1][i]);

  cout.precision(8);
  cout<<fixed<<res<<endl;
}
