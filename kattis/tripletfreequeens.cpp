#include <bits/stdc++.h>
using namespace std;

using pi = pair<int, int>;
using vi = vector<int>;

#define f first
#define s second
#define pb push_back
#define sz(x) (int)(x).size()
#define rep(i, a, b) for (int i = a; i < (b); ++i)
#define nL "\n"

const int N = 300;
const int OFFSET = 150;
int row[N], col[N], d1[N], d2[N];

int main()
{
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);
	int n, m; cin >> n >> m;
	vector<string> grid(n);
	vi rs, cs, d1s, d2s;
	rep(i, 0, n) cin >> grid[i];
	if (n > m) {
		vector<string> g2(m, string(n, '.'));
		rep(i, 0, n) rep(j, 0, m) g2[j][i] = grid[i][j];
		swap(g2, grid);
		swap(n, m);
	}
	rep(i, 0, n){
		rep(j, 0, m){
			if(grid[i][j] == '#') continue;
			rs.pb(i), cs.pb(j), d1s.pb(i + j + OFFSET), d2s.pb(i - j + OFFSET);
		}
	}
	vi nxt(sz(rs), sz(rs));
	for(int i = sz(rs)-2, prv = sz(rs); i >= 0; i--) {
		nxt[i] = rs[i] != rs[i+1] ? i+1 : nxt[i+1];
	}
	pi cnt = {0, 0};
	vi idxs, qmask;
	auto bt = [&](int idx, int queens, auto &&bt) -> void {
		if (sz(rs) - idx < cnt.f - queens) return;
		if (idx == sz(rs)) {
			if(queens > cnt.f) cnt = {queens, 0};
			if(cnt.f == queens) cnt.s++;
			return;
		}
		if (max({row[rs[idx]], col[cs[idx]], d1[d1s[idx]], d2[d2s[idx]]}) < 2) {
			int mask = 0;
			rep(i, 0, sz(idxs)) {
				if(rs[idxs[i]] == rs[idx] || cs[idxs[i]] == cs[idx] || d1s[idxs[i]] == d1s[idx] || d2s[idxs[i]] == d2s[idx])
					mask |= 1 << i;
			}
			bool works = true;
			rep(i, 0, sz(idxs)) {
				if(rs[idxs[i]] == rs[idx] || cs[idxs[i]] == cs[idx] || d1s[idxs[i]] == d1s[idx] || d2s[idxs[i]] == d2s[idx])
					if (mask & qmask[i]) works = false;
			}
			if (works) {
				row[rs[idx]]++, col[cs[idx]]++, d1[d1s[idx]]++, d2[d2s[idx]]++;
				idxs.pb(idx), qmask.pb(mask);
				bt(idx+1, queens+1, bt);
				idxs.pop_back(), qmask.pop_back();
				row[rs[idx]]--, col[cs[idx]]--, d1[d1s[idx]]--, d2[d2s[idx]]--;
			}
		}
		bt(row[rs[idx]] >= 2 ? nxt[idx] : idx+1, queens, bt);
	};
	bt(0, 0, bt);
	cout << cnt.f << " " << cnt.s << "\n";
	
	return 0;
}
