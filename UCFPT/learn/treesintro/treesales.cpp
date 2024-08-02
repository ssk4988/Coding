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
using vll = vector<pll>;;
using vvi = vector<vi>;

#define f first
#define s second
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        cout << "COMPANY " << (cn+1) << "\n";
        int n; cin >> n;
        map<string, string> parent;
        map<string, int> score;
        rep(i, 0, n){
            string t; cin >> t;
            if(t == "ADD"){
                string p, x; cin >> p >> x;
                parent[x] = p;
            } else if(t == "SALE") {
                string x; int a; cin >> x >> a;
                while(x != "ROOT"){
                    score[x] += a;
                    x = parent[x];
                }
            } else {
                string x; cin >> x;
                cout << score[x] << "\n";
            }
        }
    }
    
    return 0;
}
