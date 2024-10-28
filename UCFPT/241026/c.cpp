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
    int k, p, q; cin >> k >> p >> q; p--, q--;
    vi f(k);
    int n = 0;
    set<pii> s;
    rep(i, 0, k) {
        cin >> f[i];
        n += f[i];
        f[i] *= 2;
        // cout << "insert " << i << " " << 2*f[i]-1 << endl;
        s.insert({f[i], i});
    }
    if(n == 1){
        cout << (p == q ? p+1 : 0) << "\n";
        return 0;
    }
    if(n == 2 && p == q){
        cout << "0\n";
        return 0;
    }
    auto change = [&](int c, int d) -> bool {
        if(f[c] <= 0) return true;
        s.erase({f[c], c});
        // cout << "change col " << c << " from " << f[c] << " to " << f[c]+d << endl;
        f[c] += d;
        if(f[c] < 0) return true;
        if(f[c])
            s.insert({f[c], c});
        return false;
    };
    bool works = true;
    for(int i : {p, q}){
        if(change(i, -1)){
            works = false;
        }
    }
    int l = 0, r = n-1;
    vi a(n);
    a[l] = p, a[r] = q;
    l++, r--;
    n -= 2;
    while(works && n >= 2) {
        // cout << "stage " << n << endl;
        if(change(p, -1) || change(q, -1) || sz(s) == 0){
            works = false;
            break;
        }
        // cout << "got here" << endl;
        {
            auto [freq, col] = *rbegin(s);
            if (freq > n + 1){
                works = false;
                break;
            }
        }
        // cout << "try p" << endl;
        bool did = false;
        for(auto it = rbegin(s); it != rend(s); it++) {
            auto [freq, col] = *it;
            if(col == p) continue;
            p = col;
            did = true;
            a[l++] = p;
            if(change(p, -1) || sz(s) == 0) {works = false;}
            break;
        }
        if(!did || !works) {works = false; break;}
        did = false;
        for(auto it = rbegin(s); it != rend(s); it++) {
            auto [freq, col] = *it;
            if(col == q) continue;
            q = col;
            did = true;
            a[r--] = q;
            if(change(q, -1) || sz(s) == 0) {works = false;}
            break;
        }
        if(!did) {works = false; break;}
        // cout << "p= " << p << " q= " << q << endl;
        n -= 2;
    }
    if(n) {
        if(sz(s) == 0 || change(p, -1) || change(q, -1) || sz(s) == 0){
            works = false;
        }
        else{
            auto [freq, col] = *begin(s);
            if(col == p || col == q) works = false;
            else a[l] = col;
        }
    } else if (p==q) works = false;
    if(works){
        rep(i, 0, sz(a)) cout << a[i]+1 << " ";
        cout << "\n";
    } else cout << "0\n";
    
    return 0;
}
