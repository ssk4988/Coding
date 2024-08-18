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

const int MAX_N = 2010;

pi getorig(pi augment){
    return {(augment.f + augment.s) / 2, augment.s - (augment.f + augment.s) / 2};
}

pi augment(pi orig){
    return {orig.f - orig.s, orig.f + orig.s};
}

struct UF {
	vi e, mx, mn;
	UF(int n) : e(n, -1), mx(n, -1e9), mn(n, 1e9) {}
	bool sameSet(int a, int b) { return find(a) == find(b); }
	int size(int x) { return -e[find(x)]; }
	int find(int x) { return e[x] < 0 ? x : e[x] = find(e[x]); }
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (e[a] > e[b]) swap(a, b);
		e[a] += e[b]; e[b] = a;
        mn[a] = min(mn[a], mn[b]);
        mx[a] = max(mx[a], mx[b]);
		return true;
	}
};

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k; cin >> n >> m >> k;
    vector<UF> rows(MAX_N * 2, UF(MAX_N));
    vector<UF> cols(MAX_N * 2, UF(MAX_N));
    rep(_, 0, k){
        int i, j; cin >> i >> j; i--, j--;
        i += MAX_N; // j -= MAX_N;
        auto [r, c] = augment({i, j});
        pi best = {1e9, 1e9};
        // cout << i << " " << j << " " << r << " " << c << endl;
        rep(d, 0, MAX_N){
            int minr = r - d, minc = c - d;
            int maxr = r + d, maxc = c + d;
            // cout << "tyring d " <<  d << endl;
            // cout << "rows\n";
            for(int r1 : {minr, maxr}){
                vi ct;
                if((r1 + c) % 2){
                    ct = {c-1, c+1};
                }
                else ct = {c};
                vi cs;
                for(int c1 : ct){
                    int u = rows[r1].find(c1/2);
                    if(rows[r1].mn[u] != 1e9){
                        cs.pb((rows[r1].mn[u] - 1) * 2 + c1 % 2);
                    }
                    if(rows[r1].mx[u] != -1e9){
                        cs.pb((rows[r1].mx[u] + 1) * 2 + c1 % 2);
                    }
                    if (rows[r1].mx[u] == -1e9){
                        cs.pb(c1);
                    }
                }
                for(int c1 : cs){
                    // cout << "for row " << r1 << " processed " << c1 << "\n";
                    auto [i1, j1] = getorig({r1, c1});
                    int oi1 = i1 - MAX_N, oj1 = j1;
                    if(oi1 >= 0 && oi1 < n && oj1 >= 0 && oj1 < m){}
                    else continue;
                    if(minr <= r1 && r1 <= maxr && minc <= c1 && c1 <= maxc){}
                    else continue;
                    // cout << "try " << i1 << " " << j1 << endl;
                    if(abs(i - i1) + abs(j - j1) < abs(i - best.f) + abs(j - best.s) || (abs(i - i1) + abs(j - j1) == abs(i - best.f) + abs(j - best.s) && pi{i1, j1} < best)){
                        // cout << "replace with " << i1 << " " << j1 << endl;
                        best = pi{i1, j1};
                    }
                }
            }
            // cout << "cols\n";
            for(int c1 : {minc, maxc}){
                vi rt;
                if((r + c1) % 2){
                    rt = {r-1, r+1};
                }else rt = {r};
                vi rs;
                for(int r1 : rt){
                    int u = cols[c1].find(r1/2);
                    if(cols[c1].mn[u] != 1e9){
                        rs.pb((cols[c1].mn[u] - 1) + r1 % 2);
                    }
                    if(cols[c1].mx[u] != -1e9){
                        rs.pb((cols[c1].mx[u] + 1) + r1 % 2);
                    }
                    if (cols[c1].mx[u] == -1e9){
                        rs.pb(r1);
                    }
                }
                for(int r1 : rs){
                    // cout << "for row " << r1 << " processed " << c1 << "\n";
                    auto [i1, j1] = getorig({r1, c1});
                    int oi1 = i1 - MAX_N, oj1 = j1;
                    if(oi1 >= 0 && oi1 < n && oj1 >= 0 && oj1 < m){}
                    else continue;
                    if(minr <= r1 && r1 <= maxr && minc <= c1 && c1 <= maxc){}
                    else continue;
                    // cout << "try " << i1 << " " << j1 << endl;
                    if(abs(i - i1) + abs(j - j1) < abs(i - best.f) + abs(j - best.s) || (abs(i - i1) + abs(j - j1) == abs(i - best.f) + abs(j - best.s) && pi{i1, j1} < best)){
                        // cout << "replace with " << i1 << " " << j1 << endl;
                        best = pi{i1, j1};
                    }
                }
            }
            if(best.f != 1e9){
                break;
            }
        }
        // rep(r, 0, n){
        // }
        cout << (best.f+1-MAX_N) << " " << (best.s+1) << endl;
        tie(r, c) = augment(best);
        // cout << " rem " << r << " " << c << endl;
        rows[r].mn[c/2] = rows[r].mx[c/2] = c/2;
        if(rows[r].mx[rows[r].find(c/2-1)] != -1e9) rows[r].join(c/2, c/2-1);
        if(rows[r].mx[rows[r].find(c/2+1)] != -1e9) rows[r].join(c/2, c/2+1);
        cols[c].mn[r/2] = cols[c].mx[r/2] = r/2;
        if(cols[c].mx[cols[c].find(r/2-1)] != -1e9) cols[c].join(r/2, r/2-1);
        if(cols[c].mx[cols[c].find(r/2+1)] != -1e9) cols[c].join(r/2, r/2+1);
    }


    return 0;
}