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

int main()
{
    freopen("student.in", "r", stdin);
    freopen("student.out", "w", stdout);
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi ks(n);
    int total = 0;
    vector<vector<tuple<ll, ll, ll>>> labs(n); // time, weight
    rep(i, 0, n){
        cin >> ks[i];
        labs[i].resize(ks[i]);
        total += ks[i];
    }
    int idx = 0;
    rep(i, 0, n){
        rep(j, 0, ks[i]){
            cin >> get<0>(labs[i][j]);
            get<2>(labs[i][j]) = idx++;
        }
    }
    rep(i, 0, n){
        rep(j, 0, ks[i]){
            cin >> get<1>(labs[i][j]);
        }
    }
    vl totaltime(n), totalweight(n);
    rep(i, 0, n){
        sort(all(labs[i]), [](auto a, auto b)->bool {
            return get<0>(a) * get<1>(b) < get<0>(b) * get<1>(a);
        });
        totaltime[i] = 0;
        rep(j, 0, ks[i]){
            totaltime[i] += get<0>(labs[i][j]);
            totalweight[i] += get<1>(labs[i][j]);
        }
    }
    vi perm(n);
    rep(i, 0, n) perm[i] = i;
    sort(all(perm), [&](int a, int b)-> bool {
        return totaltime[a] * totalweight[b] < totaltime[b] * totalweight[a];
    });
    vector<tuple<int, int, int>> ls;
    for(int i : perm){
        rep(j, 0, ks[i]){
            ls.pb(labs[i][j]);
        }
    }
    ll t = 0, pen = 0;
    for(auto [p, w, idx] : ls){
        t += p;
        pen += t * w;
    }
    cout << pen << nL;
    for(auto [p, w, idx] : ls){
        cout << idx + 1 << " ";
    }
    cout << nL;

    
    return 0;
}
