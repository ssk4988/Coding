#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vii = vector<pii>;
using vll = vector<pll>;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

const int N = 2005;

void solve(){
    int n; cin >> n;
    string as, bs; cin >> as >> bs;
    bitset<N> a(as), b(bs);
    if(a == b){
        cout << "0\n";
        return;
    }
    if((a.count() == 0) != (b.count() == 0)){
        cout << "-1\n";
        return;
    }
    bitset<N> mask;
    rep(i, 0, n) mask[i] = 1;
    vi moves;
    int firstb = -1, secondb = -1;
    rep(i, 0, n){
        if(b[i] && firstb == -1) firstb = i;
        if(b[i]) secondb = i;
    }
    auto domove = [&](int d) -> void {
        if(d == 0) return;
        moves.pb(d);
        if(d < 0) {
            a = (a ^ (a >> -d)) & mask;
        } else a = (a ^ (a << d)) & mask;
    };
    while(a != b){
        int firsta = -1, seconda = -1;
        rep(i, 0, n){
            if(a[i] && firsta == -1) firsta = i;
            if(a[i]) seconda = i;
        }
        if(firstb < firsta){
            domove(firstb - firsta);
            continue;
        }
        int matched = firstb;
        while(matched < n && a[matched] == b[matched]) matched++;
        if(matched < n){
            domove(matched - firsta);
            continue;
        }
        matched = firstb-1;
        while(matched >= 0 && a[matched] == b[matched]) {
            matched--;
        }
        assert(matched >= 0);
        domove(matched-seconda);
    }
    // assert(sz(moves) <= n);
    cout << sz(moves) << "\n";
    for(int m : moves){
        assert(m != 0);
        cout << m << " ";
    }
    cout << "\n";
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        solve();
    }    
    
    return 0;
}
