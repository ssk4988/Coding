#include <bits/stdc++.h>
using namespace std;

using pi = pair<int, int>;
using vi = vector<int>;
using vpi = vector<pi>;
using vvi = vector<vi>;

#define f first
#define s second
#define all(x) x.begin(), x.end()
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)

void solve() {
	int n, m; cin >> n >> m;
	vi p(n), r(n), d(n);
	int mx_d = 0;
	rep(i, 0, n){
		cin >> p[i] >> r[i] >> d[i];
		mx_d = max(mx_d, d[i]);
	}
	vector<array<int, 4>> ord, nxt_ord;
	ord.reserve(n);
	nxt_ord.reserve(n);
	vector<vector<vi>> times(n);
	bool works = true;
	vi inq(n);
	vpi rs;
	int prevt = 0;
	vi dur(n);
	vvi durs;
	rep(t, 0, mx_d+1) {
		bool did = false;
		rep(i, 0, n){
			if(r[i] == t) {
				if (r[i] != d[i]) {
					ord.push_back({d[i] - r[i] - p[i], t, p[i], i});
					inq[i] = true;
					did = true;
				}
			}
			else if (d[i] == t) {
				did = true;
				if(inq[i]) 
					for(int j = sz(ord)-1; j >= 0; j--){
						auto [slack, ins, left, idx] = ord[j];
						if(idx == i){
							if(left > 0) works = false;
							ord.erase(begin(ord) + j);
							break;
						}
					}
			} 
		}
		if(did) {
			if(t != 0) {
				rs.emplace_back(prevt, t);
				durs.push_back(dur);
				dur = vi(n);
				prevt = t;
			}
			sort(all(ord));
		}
		int rem = 0, cnt = 0;
		rep(i, 0, sz(ord)){
			auto &[slack, ins, left, idx] = ord[i];
			if (cnt >= m) {
				slack--;
			}
			else {
				dur[idx]++;
				left--;
				if (left <= 0) {
					inq[idx] = false;
					rem++;
					ord.erase(begin(ord) + i);
					i--;
					if (slack < 0) works = false;
				}
			}
			cnt++;
		}
		int start = min(sz(ord), m - rem);
		merge(begin(ord), begin(ord) + start, begin(ord) + start, end(ord), back_inserter(nxt_ord));
		swap(ord, nxt_ord);
		nxt_ord.clear();
	}

	cout << (works ? "YES" : "NO") << "\n";
	if(!works) {
		cout << "\n";
		return;
	}
	rep(ti, 0, sz(rs)) {
		int pid = 1, ts = rs[ti].f;
		rep(i, 0, n){
			while(durs[ti][i]) {
				int amt = min(durs[ti][i], rs[ti].s - ts);
				times[i].push_back({ts, ts + amt, pid});
				durs[ti][i] -= amt;
				ts += amt;
				if (ts == rs[ti].s) pid++, ts = rs[ti].f;
			}
		}
	}

	rep(i, 0, n){
		cout << sz(times[i]) << "\n";
		for(auto v : times[i]){
			cout << v[0] << " " << v[1] << " " << v[2] << "\n";
		}
	}
	cout << "\n";
}

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int nc; cin >> nc;
	rep(cn, 0, nc) solve();
	
	return 0;
}
