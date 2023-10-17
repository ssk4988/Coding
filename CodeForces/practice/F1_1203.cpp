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

bool cmp(pi &a, pi &b){
    if(a.s >= 0 && b.s >= 0){
        return a.f < b.f;
    }
    else if(a.s < 0 && b.s < 0){
        return a.f + a.s > b.f + b.s;
    }
    else {
        return (a.s >= 0) > (b.s >= 0);
    }
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, r; cin >> n >> r;
    vpi p(n);
    rep(i, 0, n){
        cin >> p[i].f >> p[i].s;
    }
    sort(all(p), cmp);
    int used = 0;
    for(used = 0; used < n && r >= p[used].f && r + p[used].s >= 0; used++){
        r += p[used].s;
    }
    cout << (used == n ? "YES" : "NO") << nL;
    
    return 0;
}
