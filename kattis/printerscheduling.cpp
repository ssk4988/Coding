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

void solve() {
    int n, m; cin >> n >> m;
    vi p(n), r(n), d(n);
    int mx_d = 0;
    rep(i, 0, n){
        cin >> p[i] >> r[i] >> d[i];
        mx_d = max(mx_d, d[i]);
    }
    vector<array<int, 3>> ord, nxt_ord;
    ord.reserve(n);
    nxt_ord.reserve(n);
    vector<vector<vi>> times(n);
    bool works = true;
    vi inq(n);
    rep(t, 0, mx_d+1) {
        bool did = false;
        rep(i, 0, n){
            if(r[i] == t) {
                if (r[i] != d[i]) {
                    ord.push_back({d[i] - r[i] - p[i], p[i], i});
                    inq[i] = true;
                    did = true;
                }
            }
            else if (inq[i] && d[i] == t) {
                for(int j = sz(ord)-1; j >= 0; j--){
                    auto [slack, left, idx] = ord[j];
                    if(idx == i){
                        if(left > 0) works = false;
                        ord.erase(begin(ord) + j);
                        break;
                    }
                }
            } 
        }
        if(did) sort(all(ord));
        int rem = 0, cnt = 0;
        int start = 0;
        rep(i, 0, sz(ord)){
            auto &[slack, left, idx] = ord[i];
            if (cnt >= m) {
                slack--;
            }
            else {
                if(sz(times[idx]) && times[idx].back()[1] == t) {
                    times[idx].back()[1]++;
                }
                else times[idx].push_back({t, t+1, -1});
                left--;
                if (left <= 0) {
                    inq[idx] = false;
                    rem++;
                    ord.erase(begin(ord) + i);
                    i--;
                    if (slack < 0) works = false;
                }
            }
            cnt++;
        }
        merge(begin(ord), begin(ord) + start, begin(ord) + start, end(ord), back_inserter(nxt_ord));
        swap(ord, nxt_ord);
        nxt_ord.clear();
    }

    cout << (works ? "YES" : "NO") << "\n";
    if(!works) {
        cout << "\n";
        return;
    }
    set<int> unused;
    rep(i, 0, m) unused.insert(i+1);
    vi ps(n);
    rep(t, 0, mx_d + 1) {
        // cout << "processing time " << t << endl;
        rep(i, 0, n){
            if(ps[i] == sz(times[i])) continue;
            if(times[i][ps[i]][1] == t) {
                unused.insert(times[i][ps[i]][2]);
                ps[i]++;
            }
        }
        rep(i, 0, n){
            if(ps[i] == sz(times[i])) continue;
            if(times[i][ps[i]][0] == t) {
                int x = *unused.begin();
                unused.erase(begin(unused));
                times[i][ps[i]][2] = x;
            }
        }
    }

    rep(i, 0, n){
        cout << sz(times[i]) << "\n";
        for(auto v : times[i]){
            cout << v[0] << " " << v[1] << " " << v[2] << "\n";
        }
    }
    cout << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) solve();
    
    return 0;
}
