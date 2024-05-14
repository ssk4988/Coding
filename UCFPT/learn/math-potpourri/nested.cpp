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

struct UF {
	vi e;
	UF(int n) : e(n, -1) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (a > b) swap(a, b);
		e[a] += e[b]; e[b] = a;
		return true;
	}
};

const ll inf = 1e18 + 10;

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    while(true){
        ll k; cin >> k;
        if(k == 0) break;
        string s; cin >> s;
        int n = sz(s);
        if(n == 1){
            if(s == "?"){
                cout << (k < 10 ? k : -1) << "\n";
            } else{
                cout << (k == 1 ? s : "-1") << "\n";
            }
            continue;
        }
        int n2 = n / 2;
        if(n % 2 == 0 || n2 % 2 == 0){
            cout << -1 << "\n";
            continue;
        }
        vi digs;
        rep(i, 0, n2/2 + 1){
            digs.pb(i);
        }
        digs.pb(n2);
        UF uf(n);
        rep(i, 0, n){
            uf.join(i, n - 1 - i);
        }
        rep(i, 0, n/2){
            uf.join(i, n/2 - 1 - i);
            uf.join(n - n/2 + i, n-1 - i);
        }
        vector<set<int>> poss(n);
        rep(i, 0, n){
            if(s[i] != '?') poss[uf.find(i)].insert(s[i] - '0');
        }
        bool bad = false;
        vi ans(n, -1);
        rep(i, 0, n){
            if(sz(poss[i]) > 1){
                bad = true;
            }
            if(sz(poss[uf.find(i)]) == 1){
                ans[uf.find(i)] = *poss[uf.find(i)].begin();
            }
        }
        if(ans[0] == 0) bad = true;
        if(bad){
            cout << -1 << "\n";
            continue;
        }
        vector<vector<vl>> dp(sz(digs), vector<vl>(10, vl(10, -1)));
        auto go = [&](int idx, int dig, int first, auto &&go)->ll{
            int place = digs[idx];
            ll& res = dp[idx][dig][first];
            // cout << "at go(" << place <<"," << dig <<")\n";
            if(res != -1) return res;
            res = 0;
            // if(dig == 10 && !(ans[place] != -1 || uf.find(place) != place)) return res;
            if(ans[place] != -1 && dig != ans[place]) return res;
            if(place == 0 && dig == 0) return res;
            if(place == 0 && dig != first) return res;
            if(idx == sz(digs)-1){
                return res = dig != first;
            }
            int nextplace = digs[idx+1];
            rep(d, 0, 10){
                if(d == dig && nextplace - place == 1) continue;
                res += go(idx+1, d, first, go);
                res = min(inf, res);
            }
            // cout << "go place=" << place << " dig=" << dig << " = " << res << "\n";
            return res;
        };
        ll tot = 0;
        rep(i, 0, 10){
            tot += go(0, i, i, go);
            tot = min(tot, inf);
        }
        if(tot < k){
            cout << -1 << "\n";
            continue;
        }
        int first = -1;
        int dig = 0;
        for(; dig < 10; dig++){
            ll res = go(0, dig, dig, go);
            if(res >= k){
                break;
            }
            k -= res;
        }
        first = dig;
        ans[digs[0]] = first;
        // cout << "first: " << first << " left=" << k << "\n";
        // cout << "digs: ";
        // for(int x : digs) cout << x << " ";
        // cout << "\n";
        rep(idx, 1, sz(digs)){
            // if(uf.find(place) != place || ans[place] != -1){
            //     ans[place] = ans[uf.find(place)];
            //     continue;
            // }
            int place = digs[idx];
            int prevplace = digs[idx-1];
            rep(d, 0, 10){
                if(place - prevplace == 1 && d == dig) continue;
                // if(idx == sz(digs) - 1 && d == first) continue;
                ll res = go(idx, d, first, go);
                // cout << "consider " << d << " at " << place << " = " << res << "\n";
                if(res >= k){
                    dig = d;
                    break;
                }
                k -= res;
            }
            ans[digs[idx]] = dig;
        }
        rep(i, 0, n){
            ans[i] = ans[uf.find(i)];
            cout << ans[i];
        }
        cout << "\n";
    }
    
    return 0;
}
