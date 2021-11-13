#include <bits/stdc++.h>
using namespace std;

int main(){
  ios::sync_with_stdio(false);
  int n; int64_t m; cin>>n>>m;

  vector<int64_t> v(n);
  for (auto &i: v) cin>>i;

  int res=0;
  vector<bool> avail(n,true);
  for (int i=0; i<n; i++) if (avail[i]){
    int best=-1;
    for (int j=i+1; j<n; j++)
      if (avail[j] and v[i]+v[j]<=m)
        if (best==-1 or v[j]>v[best])
          best=j;
    if (best!=-1)
      avail[best]=false;
    avail[i]=false;
    ++res;
  }
  cout<<res<<endl;
}
