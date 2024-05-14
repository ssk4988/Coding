#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;


#define all(x) begin(x), end(x)
#define sz(x) (int) x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    int LIM = 3e6+10;
    vi dist(LIM, -5);
    vi a(n);
    int pref = 0;
    dist[pref] = -1;
    int mx = 0;
    rep(i, 0, n){
        cin >> a[i];
        mx = max(mx, a[i]);
        pref += a[i];
        dist[pref] = i;
    }
    vi p(a);
    partial_sum(all(p), p.begin());
    rep(i, 1, LIM){
        dist[i] = max(dist[i], dist[i-1]);
    }
    map<int, int> memo;
    int q; cin >> q;
    rep(_, 0, q){
        int d; cin >> d;
        if(d < mx){
            cout << "Impossible\n";
            continue;
        }
        if(memo.count(d)){
            cout << memo[d] << "\n";
            continue;
        }
        pref = 0;
        int cur = -1;
        int cnt = 0;
        while(cur != n-1){
            cur = dist[pref + d];
            pref = p[cur];
            cnt++;
        }
        memo[d] = cnt;
        cout << memo[d] << "\n";
    }


    return 0;
}
