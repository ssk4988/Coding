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

typedef pair<ll, int> pli;
void count_sort(vector<pli> &b, int bits) { // (optional)
	//this is just 3 times faster than stl sort for N=10^6
	int mask = (1 << bits) - 1;
	rep(it,0,2) {
		int move = it * bits;
		vi q(1 << bits), w(sz(q) + 1);
		rep(i,0,sz(b))
			q[(b[i].first >> move) & mask]++;
		partial_sum(q.begin(), q.end(), w.begin() + 1);
		vector<pli> res(b.size());
		rep(i,0,sz(b))
			res[w[(b[i].first >> move) & mask]++] = b[i];
		swap(b, res);
	}
}
struct SuffixArray {
	vi a;
	string s;
	SuffixArray(const string& _s) : s(_s + '\0') {
		int N = sz(s);
		vector<pli> b(N);
		a.resize(N);
		rep(i,0,N) {
			b[i].first = s[i];
			b[i].second = i;
		}

		int q = 8;
		while ((1 << q) < N) q++;
		for (int moc = 0;; moc++) {
			count_sort(b, q); // sort(all(b)) can be used as well
			a[b[0].second] = 0;
			rep(i,1,N)
				a[b[i].second] = a[b[i - 1].second] +
					(b[i - 1].first != b[i].first);

			if ((1 << moc) >= N) break;
			rep(i,0,N) {
				b[i].first = (ll)a[i] << q;
				if (i + (1 << moc) < N)
					b[i].first += a[i + (1 << moc)];
				b[i].second = i;
			}
		}
		rep(i,0,sz(a)) a[i] = b[i].second;
	}
	vi lcp() {
		// longest common prefixes: res[i] = lcp(a[i], a[i-1])
		int n = sz(a), h = 0;
		vi inv(n), res(n);
		rep(i,0,n) inv[a[i]] = i;
		rep(i,0,n) if (inv[i] > 0) {
			int p0 = a[inv[i] - 1];
			while (s[i + h] == s[p0 + h]) h++;
			res[inv[i]] = h;
			if(h > 0) h--;
		}
		return res;
	}
};

vvi st;
vi lg;

int query(int l, int r){
    if(l > r) swap(l, r);
    if(l == r) return 1000000;
    l++;
    int i = lg[r - l + 1];
    i = min(st[i][l], st[i][r + 1 - (1 << i)]);
    return i;
}

vector<pair<int, pi>> solve(string str, bool rev){
    int n = str.length();
    lg.clear();
    st.clear();
    lg.pb(0);
    lg.pb(0);
    rep(i, 2, n + 5){
        lg.pb(lg[i / 2] + 1);
    }

    st.pb({});
    SuffixArray sao = SuffixArray(str);
    vi sa = sao.a;
    vi lcp = sao.lcp();
    vi inv(sa.size());
    rep(i, 0, sa.size()){
        inv[sa[i]] = i;
    }
    rep(i, 0, lcp.size()){
        st[0].pb(lcp[i]);
    }
    rep(i, 1, lg[lcp.size()] + 1){
        st.pb({});
        int upb = lcp.size() - (1 << i) + 1;
        rep(j, 0, upb){
            st[i].pb(min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]));
        }
    }
    vector<pair<int, pi>> ans;
    rep(i, 1, n + 1){
        int l = 0, r = 0, k;
        while(l < n){
            while(r + i < n && (k = query(inv[l], inv[r + i])) > 0){
                r += i;
                if(k < i) break;
            }
            k = query(inv[l], inv[r]);
            if(((r - l) / i == 1 && k == i) || (r - l) / i >= 2){
                int len = r - l + k;
                int cont = len - 2 * i + 1;
                // if(rev && (n - 1 - (r + k - 1)) % i == 0) cont = 0;
                cout << str.substr(l, i) << " " << str.substr(l, len) << " " << l << " " << r << " " << cont << nL;
                // ans += cont;
                ans.pb({i, {l, r + k - 1}});
            } 
            r = l = r + i;
        }
    }
    return ans;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    string str;
    cin >> str;
    int n = str.length();
    vector<pair<int, pi>> forward = solve(str, false);
    reverse(all(str));
    vector<pair<int, pi>> backward = solve(str, true);
    rep(i, 0, backward.size()){
        backward[i].s.f = n - 1 - backward[i].s.f;
        backward[i].s.s = n - 1 - backward[i].s.s;
        swap(backward[i].s.f, backward[i].s.s);
    }
    sort(all(backward));
    reverse(all(str));
    int fi, bi = 0;
    ll ans = 0;
    rep(j, 1, n + 1){
        vector<pair<int, pi>> comb;
        while(fi < forward.size() && forward[fi].f == j){
            comb.emplace_back(forward[fi++]);
        }
        while(bi < backward.size() && backward[bi].f == j){
            comb.emplace_back(backward[bi++]);
        }
        sort(all(comb));
        if(comb.size() == 0) continue;
        vector<pair<int, pi>> comb1;
        comb1.pb(comb[0]);
        rep(i, 1, comb.size()){
            if(comb[i].s.f > comb1.back().s.s){
                comb1.pb(comb[i]);
            }
            else{
                comb1.back().s.s = max(comb1.back().s.s, comb[i].s.s);
            }
        }
        rep(i, 0, comb1.size()){
            int cont = (comb1[i].s.s - comb1[i].s.f + 1) - 2 * comb1[i].f + 1;
            ans += cont;
            cout << str.substr(comb1[i].s.f, j) << " " << str.substr(comb1[i].s.f, (comb1[i].s.s - comb1[i].s.f + 1)) << " " << cont << nL;
        }
    }
    cout << ans << nL;
    
    return 0;
}