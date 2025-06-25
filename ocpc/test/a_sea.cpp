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

struct Eertree {
	vi slink = {0, 0}, len = {-1, 0}, ends{-1, -1};
    vector<map<int, int>> down;
	int cur = 0, t = 0;
    vi at;
    vvi child, jmp;
	Eertree(vi &str) : down(2) {
		for (int i = 0; i < sz(str); i++) {
			int c = str[i]; int ci = c;
			while (t <= 0 || str[t-1] != c) 
				t = i - len[cur = slink[cur]];
			if (!down[cur].count(ci)) {
				down[cur][ci] = sz(slink);
                down.push_back({});
				len.push_back(len[cur] + 2);
                ends.push_back(i);
				if (len.back() > 1) {
					do t = i - len[cur = slink[cur]];
					while(t <= 0 || str[t-1] != c);
					slink.push_back(down[cur][ci]);
				} else slink.push_back(1);
				cur = sz(slink) - 1;
			} else cur = down[cur][ci];
			t = i - len[cur] + 1;
            at.push_back(cur);
		}
        jmp = vector(20, slink);
        for(int i = 0; i+1 < 20; i++) {
            rep(j, 0, sz(jmp[i])) {
                jmp[i+1][j] = jmp[i][jmp[i][j]];
            }
        }
        child.resize(sz(slink));
        rep(i, 1, sz(slink)) {
            child[slink[i]].push_back(i);
        }
	}
};

namespace unitMongeMult {
using iter = typename vector<int>::iterator;
void unit_monge_dmul(const int n, iter stack, const iter a, const iter b) {
    if (n == 1) {
        stack[0] = 0;
        return;
    }

    const iter c_row = stack;
    stack += n;
    const iter c_col = stack;
    stack += n;

    const auto map = [ = ](const int len, const auto f, const auto g) {
        const iter a_h = stack + 0 * len;
        const iter a_m = stack + 1 * len;
        const iter b_h = stack + 2 * len;
        const iter b_m = stack + 3 * len;
        const auto split = [ = ](const iter v, iter v_h, iter v_m) {
            for (int i = 0; i < n; i++) {
                if (f(v[i])) {
                    *v_h = g(v[i]);
                    ++v_h;
                    *v_m = i;
                    ++v_m;
                }
            }
        };
        split(a, a_h, a_m);
        split(b, b_h, b_m);
        const iter c = stack + 4 * len;
        unit_monge_dmul(len, c, a_h, b_h);

        for (int i = 0; i < len; i++) {
            const int row = a_m[i];
            const int col = b_m[c[i]];
            c_row[row] = col;
            c_col[col] = row;
        }
    };
    const int mid = n / 2;
    map(
    mid, [mid](const int x) {
        return x < mid;
    }, [](const int x) {
        return x;
    });
    map(
    n - mid, [mid](const int x) {
        return x >= mid;
    }, [mid](const int x) {
        return x - mid;
    });

    class d_itr {
    public:
        int delta;
        int col;
        d_itr() : delta(0), col(0) {}
    };
    int row = n;
    const auto right = [&](d_itr & it) {
        if (b[it.col] < mid) {
            if (c_col[it.col] >= row) {
                it.delta += 1;
            }
        } else {
            if (c_col[it.col] < row) {
                it.delta += 1;
            }
        }

        it.col += 1;
    };
    const auto up = [&](d_itr & it) {
        if (a[row] < mid) {
            if (c_row[row] >= it.col) {
                it.delta -= 1;
            }
        } else {
            if (c_row[row] < it.col) {
                it.delta -= 1;
            }
        }
    };
    d_itr neg, pos;

    while (row != 0) {
        while (pos.col != n) {
            d_itr temp = pos;
            right(temp);

            if (temp.delta == 0) {
                pos = temp;
            } else {
                break;
            }
        }

        row -= 1;
        up(neg);
        up(pos);

        while (neg.delta != 0) {
            right(neg);
        }

        if (neg.col > pos.col) {
            c_row[row] = pos.col;
        }
    }
}
vector<int> unit_monge_dmul(vector<int> a, vector<int> b) {
    const int n = a.size();
    vector<int> b_inv(n);

    for (int i = 0; i < n; i++)
        b_inv[b[i]] = i;

    std::swap(b, b_inv);

    vector<int> c([](int n) {
        int ret = 0;

        while (n > 1) {
            ret += 2 * n;
            n = (n + 1) / 2;
            ret += 4 * n;
        }

        ret += 1;
        return ret;
    }
    (n));
    unit_monge_dmul(n, c.begin(), a.begin(), b.begin());
    c.resize(n);

    return c;
}
} // namespace unitMongeMult

// Generate Seaweed Matrix of A and I(n).

vector<int> make_seaweed(vector<int> &a) {
    if (sz(a) == 1) {
        return vector<int> {0, 1};
    }

    int n = sz(a);
    int m = n / 2;
    vector<int> l, r, il, ir;

    for (int i = 0; i < n; i++) {
        if (a[i] < m) {
            l.push_back(a[i]);
            il.push_back(i);
        } else {
            r.push_back(a[i] - m);
            ir.push_back(i);
        }
    }

    auto rec1 = make_seaweed(l);
    auto rec2 = make_seaweed(r);

    for (auto &z : rec1) {
        if (z < sz(l))
            z = il[z];
        else
            z = n + z - sz(l);
    }

    for (auto &z : rec2) {
        if (z < sz(r))
            z = ir[z];
        else
            z = n + (z - sz(r));
    };

    vector<int> p1(2 * n), p2(2 * n);

    {
        for (int i = 0; i < sz(r); i++)
            p1[i] = i;

        for (int i = sz(r); i < n; i++)
            p1[i] = sz(r) + rec1[i - sz(r)];

        for (int i = n; i < 2 * n; i++)
            p1[i] = i - n + sz(r);
    }

    {
        for (int i = 0; i < sz(r); i++)
            p2[i] = rec2[i];

        for (int i = sz(r); i < sz(r) + n; i++)
            p2[i] = i - sz(r);

        for (int i = sz(r) + n; i < 2 * n; i++)
            p2[i] = i;
    }

    int i0 = 0, i1 = 0;

    for (int i = 0; i < n; i++) {
        if (a[i] < m)
            p1[i + n] = rec1[i0 + sz(l)] + sz(r), i0++;
        else
            p2[i + sz(r)] = rec2[i1 + sz(r)], i1++;
    }

    return unitMongeMult::unit_monge_dmul(p1, p2);
}

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

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vi a(n);
    vii b(n);
    rep(i, 0, n) {
        cin >> a[i];
        b[i] = {a[i], i};
    }
    Eertree e(a);
    sort(all(b));
    rep(i, 0, n) {
        a[b[i].s] = i;
    }
    // rep(i, 0, n) cerr << a[i] << " ";
    // cerr << endl;
    vi seaweed = make_seaweed(a);
    seaweed.erase(begin(seaweed), begin(seaweed)+n);
    // rep(i, 0, sz(seaweed)) cerr << seaweed[i] << " ";
    // cerr << endl;
    // cerr << sz(seaweed) << " " << sz(a) << endl;
    vi ans(q);
    FT ft(2*n+5);
    vvi bucket(n+1);
    vii qs(q);

    rep(qid, 0, q) {
        int l, r; cin >> l >> r; l--, r--;
        int u = e.at[r];
        for(int p = 20-1; p >= 0; p--) {
            if(e.len[e.jmp[p][u]] >= r-l+1) u = e.jmp[p][u];
        }
        if(e.len[u] != r-l+1) {
            ans[qid] = -1;
            continue;
        }
        // ans[qid] = (r-l+1)/2;
        qs[qid] = {l, (l+r+1)/2};
        // cerr << "process " << qid << " " << qs[qid].f << " " << qs[qid].s << endl;
        bucket[qs[qid].f].push_back(qid);
        bucket[qs[qid].s].push_back(qid);
    }
    rep(i, 0, n+1) {
        for(int qid : bucket[i]) {
            auto [l, r] = qs[qid];
            ans[qid] -= (ft.query(r)-ft.query(l)) * (l == i ? 1 : -1);
            // cerr << qid << " " << ans[qid] << endl;
        }
        if(i < n) {
            ft.update(seaweed[i], 1);
        }
    }
    rep(qid, 0, q) {
        cout << ans[qid] << "\n";
    }


    return 0;
}
