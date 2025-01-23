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
    int n, q; cin >> n >> q;
    vl a(n);
    rep(i,0,n){
        cin >> a[i];
    }    
    sort(all(a));
    vl b(a);
    rep(i, 0, n) b[i] -= i;
    vl prefb(b);
    rep(i, 1, n) prefb[i] = min(prefb[i], prefb[i-1]);
    vl suffa(a);
    for(int i = n-2; i >= 0; i--) suffa[i] = min(suffa[i], suffa[i+1]);
    suffa.pb(2e9);
    vl bsort(b);
    vl bsort1(b);
    bsort1.pop_back();
    sort(all(bsort));
    sort(all(bsort1));
    vl bsuff(bsort);
    vl bsuff1(bsort1);
    bsuff.pb(0);
    bsuff1.pb(0);
    for(int i = sz(bsuff)-2; i >= 0; i--) bsuff[i] += bsuff[i+1];
    for(int i = sz(bsuff1)-2; i >= 0; i--) bsuff1[i] += bsuff1[i+1];
    // amt needed to make v in array
    auto qryfull = [&](ll v, ll k) -> ll {
        v++;
        int idx = lower_bound(all(bsort), v - k) - begin(bsort);
        ll req = bsuff[idx] + (k-v) * (n-idx);
        return req+1;
    };
    // amt needed to make v in array
    auto qryfull1 = [&](ll v, ll k) -> ll {
        v++;
        int idx = lower_bound(all(bsort1), v - k) - begin(bsort1);
        ll req = bsuff1[idx] + (k-v) * (n-1-idx);
        if(v < a.back()) req += a.back() - v;
        return req+1;
    };
    rep(_, 0, q){
        ll k; cin >> k;
        if(n == 1) {
            if(k & 1) {
                cout << a[0]+k-(k-1)/2 << " ";
            } else {
                cout << a[0]-k/2 << " ";
            }
            continue;
        }
        if(k <= n) {
            ll left = prefb[k-1] + k;
            ll right = suffa[k];
            cout << min(left, right) << " ";
            continue;
        }
        if((n & 1) != (k & 1)){
            ll ans = -1;
            for(ll dif = 1LL << 33; dif; dif /= 2){
                if(qryfull1(ans + dif, k) > (k - (n-1))/2) ans += dif;
            }
            ans++;
            cout << min({bsort1[0] + k, a.back(), ans}) << " ";
        } else {
            ll ans = -1;
            for(ll dif = 1LL << 33; dif; dif /= 2){
                if(qryfull(ans + dif, k) > (k - n)/2) ans += dif;
            }
            ans++;
            cout << min(bsort[0] + k, ans) << " ";
        }
    }
    cout << "\n";
    
    return 0;
}
