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

struct FT {
	vector<ll> s;
	FT(int n) : s(n) {}
	void update(int pos, ll dif) { // a[pos] += dif
		for (; pos < sz(s); pos |= pos + 1) s[pos] += dif;
	}
	ll query(int pos) { // sum of values in [0, pos)
		ll res = 0;
		for (; pos > 0; pos &= pos - 1) res += s[pos-1];
		return res;
	}
	int lower_bound(ll sum) {// min pos st sum of [0, pos] >= sum
		// Returns n if no sum is >= sum, or -1 if empty sum is.
		if (sum <= 0) return -1;
		int pos = 0;
		for (int pw = 1 << 25; pw; pw >>= 1) {
			if (pos + pw <= sz(s) && s[pos + pw-1] < sum)
				pos += pw, sum -= s[pos-1];
		}
		return pos;
	}
};

ostream& operator<<(ostream& os, vi &v) {
    rep(i, 0, sz(v))
        os << v[i];
    return os;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vi x, y;
    int n;
    vi xfreq(10);
    {
        string s, t; cin >> s >> t; n = sz(s);
        x.resize(n);
        y.resize(n);
        rep(i, 0, n) {
            x[i] = s[i] - '0';
            xfreq[x[i]]++;
            y[i] = t[i] - '0';
        }

    }
    vi yfreq(10);
    vector<FT> fts(10, FT(n)); // fts[i] stores digits <= i
    rep(i, 0, n) {
        rep(d, y[i], 10) fts[d].update(i, 1);
        yfreq[y[i]]++;
    }
    int q; cin >> q;
    rep(qid, 0, q) {
        int typ; cin >> typ;
        if(typ == 1) {
            int i, x; cin >> i >> x; i--;
            rep(d, y[i], 10) fts[d].update(i, -1);
            yfreq[y[i]]--;
            y[i] = x;
            yfreq[y[i]]++;
            rep(d, y[i], 10) fts[d].update(i, 1);
            continue;
        }

        int req_dig; cin >> req_dig; req_dig--;
        // cerr << "asking digit " << req_dig << " x: " << x << " y: " << y << endl;
        // case out equal
        if(yfreq == xfreq){
            cout << y[req_dig] << "\n";
            continue;
        }
        // using x, can make [0, lcp)
        int lcp = 0;
        {
            vi cur_freq(10);
            for(int pw = 1 << 20; pw; pw >>= 1) {
                if(lcp + pw > n) continue;
                bool works = true;
                rep(i, 0, 10) {
                    int add = fts[i].s[lcp + pw-1] + (i ? -fts[i-1].s[lcp + pw-1] : 0);
                    if(cur_freq[i] + add > xfreq[i]) {works = false; break;}
                }
                if(works) {
                    rep(i, 0, 10) {
                        int add = fts[i].s[lcp + pw-1] + (i ? -fts[i-1].s[lcp + pw-1] : 0);
                        cur_freq[i] += add;
                    }
                    lcp += pw;
                }
            }
        }
        // cerr << "lcp is " << lcp << endl;
        // what digit to put in a spot after matching a prefix to 'win'
        vi betters(10, -1);
        int latestbeat = -1;
        rep(better, 1, 10) {
            if(xfreq[better] == 0) continue;
            // max pos where after matching [0, pos) we still have at least 1 of better 
            int pos = 0;
            int better_freq = 0;
            for (int pw = 1 << 20; pw; pw >>= 1) {
                if(pos + pw > lcp) continue;
                bool works = true;
                int add = fts[better].s[pos + pw-1] + (better ? -fts[better-1].s[pos + pw-1] : 0);
                if (better_freq + add < xfreq[better]) {
                    better_freq += add;
                    pos += pw;
                }
            }
            betters[better] = pos;
            // cerr << "better: " << better << " pos: " << pos << endl;
            int under = fts[better-1].query(min(n, pos+1));
            if(under == 0) continue;
            int idx_under = fts[better-1].lower_bound(under);
            latestbeat = max(latestbeat, idx_under);
        }
        if(latestbeat == -1) {
            cout << "-1\n";
            continue;
        }
        // sum of digs in [0, latestbeat)
        vi freq_at(10);
        rep(i, 0, 10) freq_at[i] = fts[i].query(latestbeat);
        for(int i = 9; i > 0; i--) freq_at[i] -= freq_at[i-1];
        int to_beat = y[latestbeat];
        int smallest_larger = -1;
        rep(i, to_beat+1, 10) {
            if(freq_at[i] < xfreq[i]) {
                smallest_larger = i;
                break;
            }
        }
        assert(smallest_larger != -1);
        if(req_dig < latestbeat) {
            cout << y[req_dig] << "\n";
            continue;
        }
        if(req_dig == latestbeat) {
            cout << smallest_larger << "\n";
            continue;
        }
        freq_at[smallest_larger]++;
        int left = req_dig - latestbeat;
        bool done = false;
        rep(i, 0, 10) {
            if(xfreq[i] - freq_at[i] >= left){
                done = true;
                cout << i << "\n";
                break;
            }
            left -= xfreq[i] - freq_at[i];
        }
        assert(done);
    }
    return 0;
}
