#include <bits/stdc++.h>
using namespace std;

int main(){
  int n,s; cin>>n>>s;
  int v=(1<<(n-1));

  if (s<v){
    cout<<"impossible"<<endl;
    return 0;
  }

  vector<vector<int>> choose(n+1,vector<int>(n+1));
  for (int i=0; i<=n; i++)
    for (int j=0; j<=i; j++)
      choose[i][j]=min(s+1, i==0 or j==0? 1: choose[i-1][j]+choose[i-1][j-1]);

  vector<vector<int>> ans; ans.emplace_back(n,1);
  for (int i=0; i<n; i++){
    s-=choose[n-1][i];
  }
  for (int i=(n-1)/2, j=(n-0)/2; 0<=i or j<n; --i,++j){
    assert(choose[n-1][i]==choose[n-1][j]);
    if (i>=0) {int a=s/choose[n-1][i]/(j<n?2:1); s-=a*choose[n-1][i]; ans[0][i]+=a;}
    if (j< n) {int b=s/choose[n-1][j]/(j<n?1:2); s-=b*choose[n-1][j]; ans[0][j]+=b;}
  }

  for (int i=1; i<n; i++){
    ans.emplace_back(n-i,1);
    for (int j=0; j<ans[i].size(); j++){
      ans[i][j]=ans[i-1][j]+ans[i-1][j+1];
    }
  }

  for (int i=n; i--;)
    for (int j=n-i; j--;)
      cout<<ans[i][j]<<(j?' ':'\n');
}
