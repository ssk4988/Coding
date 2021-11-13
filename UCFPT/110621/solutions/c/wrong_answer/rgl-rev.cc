#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  int n; int64_t m; cin>>n>>m;

  vector<int64_t> v(n);
  for (auto &i: v) cin>>i;
  sort(v.rbegin(),v.rend());

  int res=0;
  for (int i=0,j=n-1; i<=j;)
    if (i==j or v[i]+v[j]>m)
      ++res,--j;
    else
      ++res,--j,++i;

  cout<<res<<endl;
}
