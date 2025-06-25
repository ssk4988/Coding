#include <bits/stdc++.h>
using namespace std;

#include <bits/extc++.h> /** keep-include */
using namespace __gnu_pbds;

template<class T>
using Tree = tree<T, null_type, less<T>, rb_tree_tag,
	tree_order_statistics_node_update>;

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



/*
E: divide and conquer, two pointer. 
For each suffix of left, find longest prefix where max <= max on that suffix. 
count num that works with this suffix.
(human - v) >= (ai + v) * k
human >= ai * k + v * (k+1)
count pairs (human + human1, ai + ai1) where human + human1 - ai * k - ai1 * k >= v * (k+1)

find make 
count human, ai where human - ai * k >= v * (k+1) + ai1 * k - human1
*/

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    ll k; cin >> k;
    vl a(n); // pos is human, neg is ai
    {
        vl a1(n), a2(n);
        rep(i, 0, n) cin >> a1[i];
        rep(i, 0, n) cin >> a2[i];
        rep(i, 0, n) {
            a[i] = a1[i] - a2[i];
            // cerr << a[i] << " ";
        }
        // cerr << endl;
    }
    ll ans = 0;
    auto dnc = [&](int l, int r, auto &&dnc) -> void {
        if(r-l == 1) {
            if(k == 1 && a[l] == 0) {
                ans++;
                // cerr << "add one just for i=" << l << endl;
            }
            return;
        }
        int m = (l+r)/2;
        int p = m;
        ll prefmax = 0;
        ll prefhuman = 0, prefai = 0, suffhuman = 0, suffai = 0;
        Tree<pll> tree;
        // cerr << "L=" << l << " R=" << r << " M=" << m << endl;
        rep(i, m, r) {
            prefmax = max(prefmax, a[i]);
            if(a[i] > 0) prefhuman += a[i];
            else prefai -= a[i];
            while(p-1 >= l && a[p-1] <= prefmax) {
                p--;
                if(a[p] > 0) suffhuman += a[p];
                else suffai -= a[p];
                ll u = suffhuman - k * suffai;
                tree.insert(pll{u, p});
                // cerr << "p=" << p << " u=" << u << endl;
            }
            ll u = prefmax * (k+1) + prefai * k - prefhuman;
            ll below = tree.order_of_key(pll{u, -1});
            ll works = sz(tree) - below;
            // cerr << "i=" << i << " add=" << works << " prefmax=" << prefmax << " phu=" << prefhuman << " pai=" << prefai << endl;
            ans += works;
        }
        p = m;
        ll suffmax = 0;
        prefhuman = suffhuman = prefai = suffai = 0;
        tree.clear();
        for(int i = m-1; i >= l; i--) {
            suffmax = max(suffmax, a[i]);
            if(a[i] > 0) suffhuman += a[i];
            else suffai -= a[i];
            while(p < r && a[p] < suffmax) {
                if(a[p] > 0) prefhuman += a[p];
                else prefai -= a[p];
                ll u = prefhuman - k * prefai;
                tree.insert(pll{u, p});
                p++;
            }
            ll u = suffmax * (k+1) + suffai * k - suffhuman;
            ll below = tree.order_of_key(pll{u, -1});
            ll works = sz(tree) - below;
            // cerr << "i=" << i << " add=" << works << " suffmax=" << suffmax << " shu=" << suffhuman << " sai=" << suffai << endl;
            ans += works;
        }
        dnc(l, m, dnc);
        dnc(m, r, dnc);
    };
    dnc(0, n, dnc);
    cout << ans << "\n";
    
    return 0;
}
