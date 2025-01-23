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

void solve() {
    int n; cin >> n;
    auto qry = [&](int i, int j) {
        cout << "? " << i+1 << " " << j+1 << endl;
        int res; cin >> res;
        return res;
    };
    if(n <= 4){
        cout << 1 << endl;
        int t = qry(0, 1);
        cout << "! 1 2" << endl;
        return;
    }
    if(n <= 7) {
        cout << 2 << endl;
        vi res;
        rep(i, 0, n){
            res.pb(qry(i, (i+1)%n));
        }
        rep(i, 0, n){
            rep(j, i+2, n){
                if(i == 0 && j == n-1) continue;
                if(res[i] == res[j]){
                    cout << "! " << 1+(i%n) << " " << 1+((i+1)%n) << " " << 1+(j%n) << " " << 1+((j+1)%n) << endl;
                    return;
                }
            }
        }
    }
    // assert(false);
    int k = (n / 4) + 1;
    cout << k << endl;
    int k2 = k * 2;
    vi ed(n, -1);
    vi cnt(2);
    rep(i, 0, n/2){
        ed[2*i] = (qry(2 * i, 2 * i + 1));
        cnt[ed[2*i]]++;
    }
    rep(t, 0, 2){
        if(cnt[t] < k) continue;
        cout << "! ";
        int use = 0;
        rep(i, 0, sz(ed)) {
            if(ed[i] == t){
                cout << (i+1) << " " << (i+1+1) << " ";
                use++;
                if(use == k) break;
            }
        }
        cout << endl;
        return;
    }
    rep(i, 0, n-1){
        if(ed[i] != -1) continue;
        ed[i] = qry(i, i+1);
    }
    vi used(n);
    rep(i, 0, n){
        if(ed[i] == ed[(i+1)%n] && ed[i] == ed[(i+2)%n]){
            vi ans;
            rep(j, 0, n){
                if(ed[j] == ed[i] && (sz(ans) == 0 || (ans.back()+1) % n != j)){
                    ans.pb(j);
                }
            }
            cout << "! ";
            rep(j, 0, k){
                cout << ans[j]+1 << " " << (ans[j]+1)%n+1 << " ";
            }
            cout << endl;
            return;
        }
    }
    int idx = -1;
    rep(i, 0, n){
        if(ed[i] == -1) continue;
        if(ed[i] == ed[(i+1)%n] && ed[(i+2)%n] == ed[(i+3)%n]) {
            int t = qry(i, (i+4)%n);
            used[i] = used[(i+4)%n] = true;
            int cnt = 1;
            cout << "! ";
            cout << (i+1) << " " << (i+4)%n+1 << " ";
            rep(j, 0, n){
                if(ed[j] == t && !used[j] && !used[(j+1)%n]) {
                    cout << j+1 << " " << (j+1)%n << " ";
                    cnt++;
                    if(cnt == k) break;
                    used[j] = used[(j+1)%n] = 1;
                }
            }
            cout << endl;
            return;
        }
    }
    assert(false);
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
