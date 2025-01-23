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
    rep(cn, 0, nc) {
        int n; cin >> n;
        vl a(n);
        map<ll, int> freq;
        ll mx2 = -1;
        rep(i, 0, n){
            cin >> a[i];
            freq[a[i]]++;
            if(freq[a[i]] >= 2) mx2 = max(mx2, a[i]);
        }
        if(mx2 == -1){
            cout << "-1\n";
            continue;
        }
        a.erase(find(all(a), mx2));
        a.erase(find(all(a), mx2));
        sort(all(a));
        bool works = false;
        rep(i, 0, sz(a)-1){
            if(a[i+1]-a[i] < 2 * mx2) {
                works = true;
                cout << mx2 << " " << mx2 << " " << a[i] << " " << a[i+1] << "\n";
                break;
            }
        }
        if(!works){
            cout << "-1\n";
        }
    }
    
    return 0;
}
