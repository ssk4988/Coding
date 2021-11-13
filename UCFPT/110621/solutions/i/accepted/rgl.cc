#include <bits/stdc++.h>
using namespace std;

int main(){
  int n,s; cin>>n>>s;
  int v=(1<<(n-1));

  if (s<v){
    cout<<"impossible"<<endl;
    return 0;
  }

  vector<vector<int>> ans; ans.emplace_back(n,1);
  ans[0][0]=s-(v-1);

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
