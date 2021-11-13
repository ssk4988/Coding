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

  // Remove duplicates in items
  { int item_len=0;
    for (int i=0; i<items.size(); i++)
      if (i==0 or items[item_len-1]!=items[i])
        items[item_len++]=items[i];
    items.resize(item_len); }

  // Precalculate locations
  unordered_map<int,vector<int>> places;
  for (int i=0; i<spots.size(); i++)
    places[spots[i]].push_back(i);

  vector<vector<ld>> dp(items.size()+1,vector<ld>(spots.size(), 1e60L));
  for (auto i: places[items[0]]) dp[0][i]=1.L;

  auto const dist=[angle,&spots](int a,int b){
    return hypotl(cos(a*angle)-cos(b*angle), sin(a*angle)-sin(b*angle));
  };
  for (int i=1; i<items.size(); i++){
    vector<int> const &s=places[items[i-1]];
    vector<int> const &t=places[items[i]];
    priority_queue<tuple<ld,int,int>,vector<tuple<ld,int,int>>,greater<tuple<ld,int,int>>> todo;
    for (int k=0,j=0; k<s.size(); k++){
      j%=t.size();
      while (t[j%t.size()]+(j>=t.size()?(int)spots.size():0)<s[k]) ++j;
      todo.emplace(dp[i-1][s[k]]+dist(t[j%t.size()],s[k]),j%t.size(),k); (j+=t.size()-1)%=t.size();
      todo.emplace(dp[i-1][s[k]]+dist(t[j%t.size()],s[k]),j%t.size(),k); (j+=t.size()+1)%=t.size();
    }

    unordered_set<int> done;
    while (not todo.empty()){
      ld d=get<0>(todo.top());
      int j=get<1>(todo.top());
      int k=get<2>(todo.top());
      todo.pop();
      if (done.count(j)) continue; else done.insert(j);
      dp[i][t[j%t.size()]]=d;
      todo.emplace(dp[i-1][s[k]]+dist(t[(j+t.size()-1)%t.size()],s[k]),(j+t.size()-1)%t.size(),k);
      todo.emplace(dp[i-1][s[k]]+dist(t[(j+t.size()+1)%t.size()],s[k]),(j+t.size()+1)%t.size(),k);
    }
//    for (auto j: places[items[i]])
//      for (auto k: places[items[i-1]])
//        dp[i][j]=min(dp[i][j], dp[i-1][k]+hypotl(cos(j*angle)-cos(k*angle), sin(j*angle)-sin(k*angle)));
  }

  ld res=1e60L;
  for (auto i: places[items.back()]) res=min(res,dp[items.size()-1][i]);

  cout.precision(8);
  cout<<fixed<<res<<endl;
}
