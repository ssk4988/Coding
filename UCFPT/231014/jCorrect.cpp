#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef tuple<ll, ll, ll, ll> edge;

const ll inf = 4e18;

int main()
{
  ll n, m; cin >> n >> m;

  vector<edge> edges(m);
  vector<vector<pair<ll, ll>>> adjr(n);

  for (auto &[a, b, t, r] : edges)
  {
    cin >> a >> b >> t >> r;
    a--, b--;

    adjr[b].emplace_back(a, r);
  }

  ll tpathlen; cin >> tpathlen;
  vector<pair<ll, ll>> tpath(tpathlen);

  for (auto &[e, sleep] : tpath)
  {
    cin >> e >> sleep;
    e--;
  }

  tpath.back().second = 0;

  ll rpathlen; cin >> rpathlen;
  vector<ll> rpath(rpathlen);

  for (auto &e : rpath)
  {
    cin >> e;
    e--;
  }

  // {time, node}
  map<ll, ll> aha_moments;

  aha_moments[0] = 0;
  ll time = 0;

  for (auto &[e, sleep] : tpath)
  {
    auto &[a, b, t, r] = edges[e];
    time += t;
    aha_moments[time] = b;
    time += sleep;
    aha_moments[time] = b;
  }
  
  // Dijkstra, find rabbit's shortest time to finish
  vector<ll> distr_fast(n, inf);
  vector<ll> par(n, -1);
  priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
  distr_fast[n - 1] = 0;
  pq.push({0, n - 1});

  while (pq.size())
  {
    auto [d, u] = pq.top();
    pq.pop();

    for (auto [v, w] : adjr[u])
    {
      if (d + w < distr_fast[v])
      {
        distr_fast[v] = d + w;
        pq.push({distr_fast[v], v});
        par[v] = u;
      }
    }
  }

  // Find rabbit's time to finish (using given path)
  vector<ll> distr(n, -1);
  distr[n-1] = 0;
  ll time_to_finish = 0;
  for (ll i = rpathlen - 1; i >= 0; i--)
  {
    auto &[a, b, t, r] = edges[rpath[i]];
    time_to_finish += r;
    distr[a] = time_to_finish;
  }

  // Find turtle's time to finish (using given path)
  vector<ll> distt(n, -1);
  distt[n-1] = 0;
  time_to_finish = 0;
  for (ll i = tpathlen - 1; i >= 0; i--)
  {
    auto &[a, b, t, r] = edges[tpath[i].first];
    time_to_finish += t;
    distt[a] = time_to_finish;
  }

  vector<ll> res;
  ll rtimesofar = 0;

  // Try cheating right before taking edge e
  for (auto &e : rpath)
  {
    auto &[a, b, t, r] = edges[e];

    ll rcur = a;

    cout << rcur << " " << distr[rcur] << " " << distr_fast[rcur] << " " << par[rcur] << " " << b <<  "\n";
    if (distr[rcur] <= distr_fast[rcur] || par[rcur] == b)
    {
      rtimesofar += r;
      continue;
    }
    ll rtotal = rtimesofar + distr_fast[a];
    
    auto iter = aha_moments.upper_bound(rtimesofar);

    if (iter == aha_moments.end())
    {
      rtimesofar += r;
      continue;
    }

    auto [ttimesofar, tcur] = *iter;

    ll ttotal = ttimesofar + distt[tcur];

    if (rtotal <= ttotal)
    {
      res.push_back(a + 1);
    }

    rtimesofar += r;
  }

  sort(res.begin(), res.end());

  cout << (ll)res.size() << '\n';
  for (ll x : res)
    cout << x << " ";
  cout << "\n";
  return 0;
}