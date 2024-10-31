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

struct Tree {
	typedef pl T;
	static constexpr T unit = pl{LLONG_MAX, LLONG_MAX};
	T f(T a, T b) { return min(a, b); } // (any associative fn)
	vector<T> s; int n;
	Tree(int n = 0, T def = unit) : s(2*n, def), n(n) {}
	void update(int pos, T val) {
		for (s[pos += n] = val; pos /= 2;)
			s[pos] = f(s[pos * 2], s[pos * 2 + 1]);
	}
	T query(int b, int e) { // query [b, e)
		T ra = unit, rb = unit;
		for (b += n, e += n; b < e; b /= 2, e /= 2) {
			if (b % 2) ra = f(ra, s[b++]);
			if (e % 2) rb = f(s[--e], rb);
		}
		return f(ra, rb);
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<array<ll, 7>> lines(n); // {r1, c1, r2, c2, start time, which is first, duration}
    int mxc;
    vl cs;
    ll ans = 1e18;
    {
        pl pos{0, 0};
        ll t = 0;
        string dirs = "UDLR";
        int pidx = -1;
        rep(i, 0, n) {
            char c; cin >> c;
            int x; cin >> x;
            lines[i][0] = pos.f;
            lines[i][1] = pos.s;
            if(c == 'U') pos.f -= x-1;
            else if(c == 'D') pos.f += x-1;
            else if(c == 'L') pos.s -= x-1;
            else pos.s += x-1;
            lines[i][2] = pos.f;
            lines[i][3] = pos.s;
            lines[i][4] = t;
            if(c == 'U') pos.f -= 1;
            else if(c == 'D') pos.f += 1;
            else if(c == 'L') pos.s -= 1;
            else pos.s += 1;
            if(i == n-1){
                lines[i][2] = pos.f;
                lines[i][3] = pos.s;
            }
            int nidx = find(all(dirs), c) - begin(dirs);
            if((nidx ^ 1) == pidx){
                ans = min(ans, t);
            }
            pidx = nidx;
            t += x;
            if(pl{lines[i][0], lines[i][1]} > pl{lines[i][2], lines[i][3]}){
                swap(lines[i][0], lines[i][2]);
                swap(lines[i][1], lines[i][3]);
                lines[i][5] ^= 1;
            }
            lines[i][6] = x;
            cs.pb(lines[i][0]);
            cs.pb(lines[i][2]);
            cs.pb(lines[i][1]);
            cs.pb(lines[i][3]);
            cs.pb(lines[i][0]-1);
            cs.pb(lines[i][2]-1);
            cs.pb(lines[i][1]-1);
            cs.pb(lines[i][3]-1);
            cs.pb(lines[i][0]+1);
            cs.pb(lines[i][2]+1);
            cs.pb(lines[i][1]+1);
            cs.pb(lines[i][3]+1);
            // cout << lines[i][0] << "," << lines[i][1] << " " << lines[i][2] << "," << lines[i][3] << endl;
        }
        if (ans == 1e18) ans = t;
        sort(all(cs));
        cs.erase(unique(all(cs)), end(cs));
        for(auto &[r1, c1, r2, c2, start, sw, t] : lines){
            r1 = lower_bound(all(cs), r1) - begin(cs);
            r2 = lower_bound(all(cs), r2) - begin(cs);
            c1 = lower_bound(all(cs), c1) - begin(cs);
            c2 = lower_bound(all(cs), c2) - begin(cs);
            // cout << r1 << "," << c1 << " " << r2 << "," << c2 << endl;
        }
        mxc = sz(cs);
    }
    rep(iter, 0, 2) {
        vvi queries(mxc);
        vector<vpi> updates(mxc);
        vi use(n);
        rep(i, 0, n){
            auto [r1, c1, r2, c2, start, sw, t] = lines[i];
            if (r1 == r2) queries[r1].pb(i);
            else {
                updates[r1].pb({c1, i});
                if(r2+1 < mxc) updates[r2+1].pb({c1, i});
            }
        }
        Tree tree(mxc);
        vector<priority_queue<pl, vpl, greater<>>> pqs(mxc);
        rep(r, 0, mxc){
            for(auto [c, i] : updates[r]) {
                use[i] ^= 1;
                if(!use[i]) while(sz(pqs[c]) && !use[pqs[c].top().s]) pqs[c].pop();
                else pqs[c].push({lines[i][4], i});
                tree.update(c, sz(pqs[c]) ? pqs[c].top() : tree.unit);
            }
            for(int i1 : queries[r]) {
                auto [r1, c1, r2, c2, start, sw, t] = lines[i1];
                auto [t2, i2] = tree.query(c1, c2+1);
                if(t2 == LLONG_MAX) continue;
                ll c = lines[i2][1];
                ll cand1 = start + abs(cs[sw ? c2 : c1] - cs[c]);
                ll cand2 = lines[i2][4] + abs(cs[lines[i2][lines[i2][5] ? 2 : 0]] - cs[r1]);
                ans = min(ans, max(cand1, cand2));
            }
            updates[r].clear();
        }

        rep(i, 0, n){
            use[i] = false;
            auto [r1, c1, r2, c2, start, sw, t] = lines[i];
            if(r1 == r2){
                updates[r1].push_back({c1, i});
                updates[r1].push_back({c2+1, -i});
            }
        }
        rep(r, 0, mxc){
            sort(all(updates[r]));
            set<pl> pq;
            for(auto [c, i] : updates[r]){
                if(i < 0) i = -i;
                auto [r1, c1, r2, c2, start, sw, t] = lines[i];
                use[i] ^= 1;
                ll curc = c + (use[i] ? 0 : -1);
                if(!use[i]) pq.erase({lines[i][4], i});
                if(sz(pq)){
                    auto [t2, i2] = *begin(pq);
                    ll cand1 = start + abs(cs[sw ? c2 : c1] - cs[curc]);
                    ll cand2 = lines[i2][4] + abs(cs[lines[i2][lines[i2][5] ? 3 : 1]] - cs[curc]);
                    ans = min(ans, max(cand1, cand2));
                }
                if(use[i]) pq.insert({lines[i][4], i});
            }
        }
        

        rep(i, 0, n){
            swap(lines[i][0], lines[i][1]);
            swap(lines[i][2], lines[i][3]);
            if(pl{lines[i][0], lines[i][1]} > pl{lines[i][2], lines[i][3]}){
                swap(lines[i][0], lines[i][2]);
                swap(lines[i][1], lines[i][3]);
                lines[i][5] ^= 1;
            }
        }
        swap(cs, cs);
        swap(mxc, mxc);
    }
    cout << ans << "\n";
    return 0;
}
