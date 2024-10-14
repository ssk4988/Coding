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

int check(int i, int j) {
    cout << "? " << i+1 << " " << j+1 << endl;
    int r; cin >> r; if(r == -1) exit(0);
    cout << "? " << j+1 << " " << i+1 << endl;
    int r1; cin >> r1; if(r1 == -1) exit(0);
    return r != r1;
}

void solve() {
    int n; cin >> n;
    vi imps(n);
    iota(all(imps), 0);
    reverse(all(imps));
    vi known(n);
    if((n&1) && n > 3) {
        int a = n-3, b = n-2, c = n-1;
        cout << "? " << a+1 << " " << b+1 << endl;
        int r1; cin >> r1;
        cout << "? " << b+1 << " " << c+1 << endl;
        int r2; cin >> r2;
        cout << "? " << c+1 << " " << a+1 << endl;
        int r3; cin >> r3;
        if((r1 + r2 + r3) % 2 == 0) {
            cout << "? " << b+1 << " " << a+1 << endl;
            int r4; cin >> r4;
            if(r4 == r1){
                cout << "! " << c+1 << endl;
                return;
            }
            cout << "? " << a+1 << " " << c+1 << endl;
            int r5; cin >> r5;
            cout << "! " << (r5 == r3 ? b : a)+1 << endl;
            return;
        }
        else {
            known[a] = known[b] = known[c] = true;
            imps.erase(begin(imps), begin(imps) + 3);
        }
    }
    for(int i = 0; i < n && sz(imps) > 2; i += 2) {
        int j = (i+1) % n;
        if(check(i, j)) {
            imps = {i, j};
            break;
        }
        known[i] = known[j] = true;
        imps.pop_back();
        imps.pop_back();
    }
    vi n_imps;
    for(int i : imps) if(!known[i]) n_imps.pb(i);
    swap(imps, n_imps);
    if(sz(imps) > 1) {
        int other = 0;
        while(other == imps[0] || other == imps[1]) other++;
        imps = {imps[!check(imps[0], other)]};
    }
    cout << "! " << imps[0]+1 << endl;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc) {
        solve();
    }
    
    return 0;
}
