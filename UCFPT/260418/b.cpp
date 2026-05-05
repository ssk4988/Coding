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

// NOTE: CHANGE LATER
const int K = 300;

/*
1 2 3 4 5 6
2 + 1 + 4 + 2 + 2 + 1 + 6 + 2 + 2

1 2 3 4 5 6 7
2 + 1 + 5 + 2 + 2 + 1 + 7 + 2 + 3 + 1 + 2
*/
struct Info {
    int cnt = 0;
    vi two;
    array<ll, 2> sum{0, 0};
    ll score() {
        if(cnt == 0) return 0;
        if(cnt <= 2) return two[cnt-1];
        return sum[(cnt&1)^1] + (cnt - 2) / 2 * two[0] + two[1] * (cnt - 2);
    }
};

Info make(int x) {
    return Info{1, vi{x}, array<ll, 2>{x, 0}};
}

Info operator+(Info a, Info b) {
    vi two(a.two);
    for(auto x : b.two) if(sz(two) < 2) two.push_back(x);
    return {a.cnt + b.cnt, two, array<ll, 2>{a.sum[0] + b.sum[a.cnt&1], a.sum[1] + b.sum[(a.cnt&1)^1]}};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, q; cin >> n >> q;
    vi a(n);
    rep(i, 0, n) cin >> a[i];
    vi c(a);
    sort(all(c));
    c.erase(unique(all(c)), end(c));
    vi b(n);
    rep(i, 0, n) b[i] = lower_bound(all(c), a[i]) - begin(c);
    vii ord;
    rep(i, 0, n) ord.push_back({b[i], i});
    sort(all(ord));
    vi invord(n);
    rep(i, 0, n) invord[ord[i].second] = i;
    // rep(i, 0, n) {
    //     cerr << i << " " << a[i] << " " << b[i] << " " << ord[i] << " " << invord[i] << endl;
    // }
    vector<Info> infos((n + K - 1) / K * K), blockinfo((n + K-1) / K);
    vi ls(q), rs(q), as(q), bs(q), ks(q);
    rep(i, 0, q) {
        cin >> ls[i] >> rs[i] >> as[i] >> bs[i] >> ks[i];
        ls[i]--;
        as[i] = lower_bound(all(c), as[i]) - begin(c);
        bs[i]++;
        bs[i] = lower_bound(all(c), bs[i]) - begin(c);
    }
    vi qord(q);
    iota(all(qord), 0);
    sort(all(qord), [&](int i, int j) { return pii{ls[i] / K, rs[i]} < pii{ls[j] / K, rs[j]}; });
    int L = 0, R = 0;
    auto upd = [&](int i, Info x) -> void {
        // cerr << "upd " << i << " with " << x.score() << endl;
        infos[i] = x;
        int j = i / K * K;
        blockinfo[i/K] = Info();
        while(j / K == i / K) {
            blockinfo[i / K] = blockinfo[i / K] + infos[j];
            // cerr << "pref " << j << endl;
            // cerr << "block " << blockinfo[i/K].score() << endl;
            j++;
        }
    };
    vl ans(q, -1);
    for(auto qid : qord) {
        // cerr << "process " << qid << " l = " << ls[qid] << " r = " << rs[qid] << endl;
        while(R < rs[qid]) {
            upd(invord[R], make(a[R]));
            R++;
        }
        while(L > ls[qid]) {
            L--;
            upd(invord[L], make(a[L]));
        }
        while(R > rs[qid]) {
            R--;
            upd(invord[R], Info());
        }
        while(L < ls[qid]) {
            upd(invord[L], Info());
            L++;
        }
        int ql = lower_bound(all(ord), pii{as[qid], -1}) - begin(ord);
        int qr = lower_bound(all(ord), pii{bs[qid], -1}) - begin(ord);
        // cerr << "ql " << ql << " qr " << qr << endl;
        Info res;
        while(ql / K != qr / K && ql % K != 0 && res.cnt < ks[qid]) {
            res = res + infos[ql];
            ql++;
        }
        while(ql / K != qr / K && res.cnt + blockinfo[ql / K].cnt <= ks[qid]) {
            res = res + blockinfo[ql / K];
            ql += K;
        }
        while(ql < qr && res.cnt < ks[qid]) {
            res = res + infos[ql];
            ql++;
        }
        assert(res.cnt <= ks[qid]);
        // cerr << "res " << res.cnt << " ";
        // for(auto x : res.two) cerr << x << ",";
        // for(auto x : res.sum) cerr << x << ",";
        // cerr << res.score() << endl;
        ans[qid] = res.score();
    }
    rep(qid, 0, q) {
        cout << ans[qid] << "\n";
    }
    
    return 0;
}
