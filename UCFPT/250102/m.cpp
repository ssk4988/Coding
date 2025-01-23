#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()
#define all(x) begin(x), end(x)


int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int nc ;cin >> nc;
    rep(cn, 0, nc){
        int n, m; cin >> n >> m;
        vvi a(n, vi(m));
        int c = 1;
        rep(i, 0, n){
            rep(j, 0, m){
                a[i][j] = c++;
            }
            if((i&1) || m % 2 == 0) continue;
            rotate(begin(a[i]), begin(a[i])+1, end(a[i]));
        }
        cout << "YES\n";
        set<int> res;
        rep(i, 0, n){
            rep(j, 0, m){
                cout << a[i][j] << " ";
            }
            cout << "\n";
        }
        rep(i, 0, n){
            rep(j, 0, m){
                if(i+1 < n){
                    int v = a[i][j] + a[i+1][j];
                    assert(!res.count(v));
                    res.insert(v);
                }
                if(j+1 < m){
                    int v = a[i][j] + a[i][j+1];
                    assert(!res.count(v));
                    res.insert(v);
                }
            }
        }
    }

    return 0;
}
