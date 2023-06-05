#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

using P = array<ld, 3>;
const ll per = 500;

ld dist(P &p1, P &p2){
    return sqrtl((p1[0] - p2[0])*(p1[0] - p2[0]) + (p1[1] - p2[1])*(p1[1] - p2[1]) + (p1[2] - p2[2])*(p1[2] - p2[2]));
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ld w, h, l; cin >> w >> h >> l;
    vector<P> dim = {{0, 0, 0}, {w, h, l}};
    P p1, p2;
    rep(i, 0, 3) cin >> p1[i];
    rep(i, 0, 3) cin >> p2[i];
    vvi planes;
    planes.pb({0, -1, -1});planes.pb({1, -1, -1});
    planes.pb({-1, 0, -1}); planes.pb({-1, 1, -1});
    planes.pb({-1, -1, 0}); planes.pb({-1, -1, 1});
    vector<P> pts;
    pts.pb(p1);
    pts.pb(p2);
    int source = 0, sink = 1;
    vector<vector<pair<int, ld>>> adj;
    vvi lines;
    lines.pb({0, 0, -1}); lines.pb({0, 1, -1}); lines.pb({1, 0, -1}); lines.pb({1, 1, -1});
    lines.pb({0, -1, 0}); lines.pb({0, -1, 1}); lines.pb({1, -1, 0}); lines.pb({1, -1, 1}); 
    lines.pb({-1, 0, 0}); lines.pb({-1, 0, 1}); lines.pb({-1, 1, 0}); lines.pb({-1, 1, 1}); 
    for(auto &l : lines){
        P base = {0, 0, 0};
        int exc = -1;
        rep(i, 0, 3){
            if(l[i] == -1) exc = i;
            else base[i] = dim[l[i]][i];
        }
        rep(i, 0, per){
            P p(base);
            p[exc] = dim[1][exc] * i / per;
            pts.pb(p);
        }
        P p(base);
        p[exc] = dim[1][exc];
        pts.pb(p);
    }
    
    int n = sz(pts);
    adj.resize(sz(pts));
    rep(i, 0, 3){
        // sort(all(pts1), [](auto &a, auto &b)->int{
        //     if(a.f[i] == b.f[i]) return 0;
        //     if(a.f[i] > b.f[i]) return 1;
        //     return -1;
        // });
        vi str, e;
        rep(j, 0, n){
            if(pts[j][i] == 0){
                str.pb(j);
            }
            if(pts[j][i] == dim[1][i]){
                e.pb(j);
            }
        }
        rep(j, 0, sz(str)){
            rep(j1, j + 1, sz(str)){
                adj[str[j]].pb({str[j1], dist(pts[str[j]], pts[str[j1]])});
                adj[str[j1]].pb({str[j], dist(pts[str[j1]], pts[str[j]])});
            }
        }
        rep(j, 0, sz(e)){
            rep(j1, j + 1, sz(e)){
                adj[e[j]].pb({e[j1], dist(pts[e[j]], pts[e[j1]])});
                adj[e[j1]].pb({e[j], dist(pts[e[j1]], pts[e[j]])});
            }
        }
    }
    
    vi visited(n);
    vd d(n, 1e9);
    d[source] = 0;
    using li = pair<ld, int>;
    priority_queue<li, vector<li>, greater<li>> pq;
    pq.push({0, source});
    while(!pq.empty()){
        auto [d1, x] = pq.top(); pq.pop();
        if(visited[x]) continue;
        visited[x] = true;
        for(auto &e : adj[x]){
            if(!visited[e.f] && d[e.f] > d1 + e.str){
                d[e.f] = d1 + e.str;
                pq.push({d[e.f], e.f});
            }
        }
    }
    cout << fixed << setprecision(3) << d[sink] << "\n";
    return 0;
}
