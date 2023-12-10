#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using pi = pair<int, int>;
using pl = pair<ll, ll>;
using pd = pair<ld, ld>;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<ld>;
using vpi = vector<pi>;
using vpl = vector<pl>;
using vpd = vector<pd>;
using vvi = vector<vi>;

#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

int modpow(int b, int p, int m){
    if(p == 0) return 1;
    if(p == 1) return b % m;
    int res = modpow(b, p/2, m);
    res = (res * res) % m;
    if(p & 1) res = (res * b) % m;
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, k; cin >> n >> k;
        vi x(n), rev(n);
        rep(i, 0, n){
            cin >> x[i]; x[i]--;
            rev[x[i]] = i;
        }
        vi vis(n);
        vvi cycles;
        rep(i, 0, n){
            if(vis[i]) continue;
            cycles.pb({i});
            vis[i] = true;
            int cur = x[i];
            while(cur != i){
                vis[cur] = true;
                cycles.back().pb(cur);
                cur = x[cur];
            }
        }
        vvi evencycles, oddcycles;
        for(auto &v : cycles){
            if(sz(v) % 2 == 0){
                evencycles.pb(v);
            } else oddcycles.pb(v);
        }
        auto comb = [&](vi &a, vi &b) -> vi {
            vi res;
            rep(i, 0, sz(a)){
                res.pb(a[i]);
                res.pb(b[i]);
            }
            return res;
        };
        bool works = true;
        if(sz(evencycles)){
            rep(i, 0, k){
                vvi neweven;
                sort(all(evencycles), [](vi &a, vi &b) -> bool { return sz(a) < sz(b); });
                rep(j, 0, sz(evencycles)){
                    if(j + 1 >= sz(evencycles) || sz(evencycles[j + 1]) != sz(evencycles[j])){
                        works = false;
                        break;
                    }
                    neweven.pb(comb(evencycles[j], evencycles[j + 1]));
                    j++;
                }
                if(!works) break;
                evencycles = neweven;
            }
        }
        if(!works){
            cout << "NO\n";
            continue;
        }

        map<int, vvi> buckets;
        for(auto &v : oddcycles) buckets[sz(v)].pb(v);
        oddcycles.clear();
        for(auto [l, cyc] : buckets){
            int p = min(20, k);
            int freq = sz(cyc);
            // cout << l << " " << freq << " " << p << "\n";
            for(; p >= 0; p--){
                while(freq >= (1 << p)){
                    freq -= 1 << p;
                    vvi res, res2;
                    rep(i, 0, 1 << p){
                        res.pb(cyc.back());
                        cyc.pop_back();
                    }
                    while(sz(res) > 1){
                        res2.clear();
                        for(int i = 0; i < sz(res); i += 2){
                            res2.pb(comb(res[i], res[i + 1]));
                        }
                        swap(res, res2);
                    }
                    oddcycles.pb(res[0]);
                }
            }
        }
        cout << cn << ": even: ";
        cycles.clear();
        for(auto &v : evencycles){
            cout << sz(v) << " ";
            cycles.pb(v);
        }
        cout << " odd: ";
        for(auto &v : oddcycles){
            cout << sz(v) << " ";
            cycles.pb(v);
        }
        cout << '\n';
        vi ans(n);
        for(auto &v : cycles){
            int offset = modpow(2, k, sz(v));
            int mindex = 0;
            rep(i, 1, sz(v)){
                if(rev[v[i]] < rev[v[mindex]]) mindex = i;
            }
            offset = ((-offset) % sz(v) + sz(v)) % sz(v);
            // int start = ((mindex - offset) % sz(v) + sz(v)) % sz(v);
            // rotate(v.begin(), v.begin() + start, v.end());
            int place = offset;
            vi v1(v);
            rep(i, 0, sz(v)){
                v1[i] = v[place];
                place = (place + offset) % sz(v);
            }
            // start = v[0];
            // rep(i, 0, sz(v)){
            //     start = min(start, v[i]);
            // }
            // cout << "start: " << start << "\n";
            // ans[start] = v[0];
            rep(i, 0, sz(v1)){
                ans[v1[i]] = v1[(i+1)%sz(v1)];
            }
            cout << "cycle: ";
            for(int i : v1) cout << (i + 1) << " ";
            cout << "\n";
        }
        cout << "ans for " << (cn) << ": ";
        rep(i, 0, n){
            cout << (ans[i] + 1) << " ";
        }
        cout << "\n";
    }
    
    return 0;
}
