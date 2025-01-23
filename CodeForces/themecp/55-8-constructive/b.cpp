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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    mt19937 rng(time(NULL));
    srand(time(NULL));
    rep(cn, 0, nc){
        int n; cin >> n;
        set<int> cands;
        rep(i, 0, n) cands.insert(i);
        while(sz(cands) >= 3) {
            int i = *begin(cands); cands.erase(i);
            int j = *begin(cands); cands.erase(j);
            int k = *begin(cands); cands.erase(k);
            int r1; cout << "? " << i+1 << " " << j+1 << endl; cin >> r1;
            int r2; cout << "? " << i+1 << " " << k+1 << endl; cin >> r2;
            if(r1 == r2) {
                cands.insert(j);
                cands.insert(k);
            } else{
                cands.insert(i);
                cands.insert(r1 > r2 ? j : k);
            }
        }
        int i = *begin(cands); cands.erase(i);
            int j = *begin(cands); cands.erase(j);
            cout << "! " << i+1 << " " << j+1 << endl;
            int fin; cin >> fin;
    }
    
    return 0;
}
