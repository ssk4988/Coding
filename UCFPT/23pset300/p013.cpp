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
	string str;
	SuffixArray(const string& _s) : str(_s + '\0') {
		int N = sz(str);
		vector<pli> b(N);
		a.resize(N);
		rep(i,0,N) {
			b[i].first = str[i];
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
			while (str[i + h] == str[p0 + h]) h++;
			res[inv[i]] = h;
			if(h > 0) h--;
		}
		return res;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<string> strs(n);
    string comb = "";
    vvi idxs(n);
    int cn = 0;
    rep(i, 0, n){
        cin >> strs[i];
        cn += strs[i].length();
        if(i){
            comb += "|";
        }
        comb += strs[i];
    }
    SuffixArray SA(comb);
    vi lg2;
    lg2.pb(0);
    lg2.pb(0);
    rep(i, 2, sz(comb) + 5)
        lg2.pb(1 + lg2[i / 2]);
    vi sa = SA.a;
    vpi conv(sz(sa));
    int strnum = 0, idx = 0;
    // comb = SA.str
    rep(i, 0, sz(sa)){
        if(SA.str[i] == '|' || SA.str[i] == '\0'){
            conv[i] = {-1, -1};
            strnum++;
            idx = 0;
        }
        else{
            conv[i] = {strnum, idx++};
        }
    }
    vi lc2 = SA.lcp();
    vi lc;
    rep(i, 1, sz(lc2)){
        if(conv[sa[i]].f == -1 || conv[sa[i - 1]].f == -1){lc.pb(0);}
        else{
            lc.pb(min(lc2[i], min(sz(strs[conv[sa[i]].f]) - conv[sa[i]].s,sz(strs[conv[sa[i-1]].f]) - conv[sa[i-1]].s)));
        }
    }
    lc.pb(0);
    rep(i, 1, sz(sa)){
        if(conv[sa[i]].f == -1) continue;
        idxs[conv[sa[i]].f].pb(i);
    }
    vvi jmp(20, vi(sz(lc)));
    jmp[0] = lc;
    rep(i, 1, 20){
        rep(j, 0, sz(lc) - (1 << i)){
            jmp[i][j] = min(jmp[i - 1][j], jmp[i - 1][j + (1 << (i - 1))]);
        }
    }
    auto getlcp = [&](int start, int end)->int{
        int lg = lg2[end - start];
        return min(jmp[lg][start], jmp[lg][end - (1 << lg)]);
    };
    // vi lastseen(n, -1);
    // rep(i, 0, )
    rep(i, 0, n){
        vi bestlcp(sz(idxs[i]));
        int pre = -1;
        rep(j, 0, sz(idxs[i])){
            if(idxs[i][j] > 1 && (j == 0 || idxs[i][j] > idxs[i][j - 1] + 1)){
                pre = idxs[i][j] - 1;
            }
            if(pre != -1){
                bestlcp[j] = max(bestlcp[j], getlcp(pre, idxs[i][j]));
            }
        }
        reverse(all(idxs[i]));
        pre = cn + 5;
        rep(j, 0, sz(idxs[i])){
            if(idxs[i][j] < cn && (j == 0 || idxs[i][j] < idxs[i][j - 1] - 1)){
                pre = idxs[i][j] + 1;
            }
            if(pre != cn + 5){
                bestlcp[sz(idxs[i]) - 1 - j] = max(bestlcp[sz(idxs[i]) - 1 - j], getlcp(idxs[i][j], pre));
            }
        }
        reverse(all(idxs[i]));
        rep(j, 1, sz(idxs[i])){
            int p = getlcp(idxs[i][j - 1], idxs[i][j]);
            bestlcp[j] = max(bestlcp[j], p);
        }
        ll ans = ll(sz(strs[i])) * (sz(strs[i]) + 1) / 2;
        rep(i, 0, sz(bestlcp)){
            ans -= bestlcp[i];
        }
        cout << ans << "\n";
    }

    
    return 0;
}
