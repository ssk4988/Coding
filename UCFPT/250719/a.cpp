#include <bits/stdc++.h>
using namespace std;


using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using ll = long long;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define sz(x) (int)x.size()

#define f first
#define s second

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, k; cin >> n >> k;
    vi a(n);
    rep(i, 0, n) {
        cin >> a[i];
    }
    int x = n / (k+1);
    assert(x >= 2);
    vi ans;
    for(int i = 0, si = 0; i < n && si <= k; i += x, si++) {
        int diff = a[i+1] - a[i];
        int lim = min(n, i + x);
        if(si == k){
            lim = n;
        }
        bool works = true;
        rep(j, i+1, lim) {
            if(a[j] - a[j-1] != diff) {
                works = false;
                break;
            }
        }
        if(!works) {
            continue;
        }
        vi seq;
        int cur = a[i];
        rep(j, i, n) {
            if(a[j] == cur) {
                seq.push_back(j);
                cur += diff;
            }
        }
        cur = a[i] - diff;
        vi front;
        for(int j = i-1; j >= 0; j--) {
            if(a[j] == cur) {
                front.push_back(j);
                cur -= diff;
            }
        }
        reverse(all(front));
        front.insert(end(front), all(seq));
        if(sz(front) > sz(ans)) ans = front;
    }
    if(sz(ans) + k < n) {
        cout << "-1\n";
        return 0;
    }
    // for(int i : ans) cerr << i << " ";
    // cerr << endl;
    int p = 0;
    vi inv;
    rep(i, 0, n) {
        while(p < sz(ans) && ans[p] < i) p++;
        if(p >= sz(ans) || ans[p] != i) inv.push_back(i);
    }
    cout << sz(inv) << "\n";
    for(int v : inv) {
        cout << v+1 << " ";
    }
    cout << "\n";

    
    return 0;
}
