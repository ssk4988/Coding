#include <bits/stdc++.h>

using namespace std;

using ll = long long int;
using vi = vector<int>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vvi = vector<vi>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define pb push_back

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vi a(n); vi reva(n);
    vi b(n); vi revb(n);
    rep(i, 0, n){
        cin >> a[i]; a[i]--;
        reva[a[i]] = i;
    }
    rep(i, 0, n){
        cin >> b[i]; b[i]--;
        revb[b[i]] = i;
    }
    vi moves;
    rep(i, 0, n){
        rep(j, 0, n-1){
            if(revb[a[j]] > revb[a[j + 1]] && abs(a[j] - a[j + 1]) >= 2){
                moves.pb(j);
                swap(a[j], a[j+1]);
            }
        }
    }
    if(a != b){
        cout << "-1\n";
    }
    else{
        cout << sz(moves) << "\n";
        for(int i : moves) cout << (i + 1) << " ";
        cout << "\n";
    }

    return 0;
}
