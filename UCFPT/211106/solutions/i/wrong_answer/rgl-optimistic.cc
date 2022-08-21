#include <bits/stdc++.h>
using namespace std;

static int res[1001][1001];

int main(){
  int64_t n,k; cin>>n>>k;
  for (int i=0; i<n; i++) res[n-1][i]=1;
  for (int i=n-1; i-->0;)
    for (int j=i+1; j-->0;)
      res[i][j]+=res[i+1][j]+res[i+1][j+1];

  int64_t add=k-res[0][0];
  for (int i=n; i--;)
    res[i][i]+=add;

  for (int i=0; i<n; i++){
    for (int j=0; j<=i; j++)
      cout<<res[i][j]<<" ";
    cout<<endl;
  }
}
