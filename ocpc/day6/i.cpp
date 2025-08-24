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

random_device(rd);
mt19937 rng(rd());

ll randint(ll a, ll b) {
    return uniform_int_distribution<ll>(a, b)(rng);
}

pair<vl, vl> gen(int n) {
    vl a(n), b(n);
    rep(i, 0, n) {
        a[i] = randint(1, 100);
        b[i] = a[i] + randint(1, 100);
    }
    return {a, b};
}

ll solve(vl a, vl b) {
    int n = sz(a);
    ll s = 0, t = 0;
    vl diffs;
    rep(i, 0, n) {
        s += a[i], t += b[i];
        diffs.push_back(b[i]-a[i]);
    }
    vl slack{s+1};
    sort(all(diffs));
    reverse(all(diffs));
    rep(i, 0, n) {
        slack.push_back(slack.back() + diffs[i]);
    }
    // for(auto v : slack) cerr << v << " ";
    // cerr << endl;
    // tx >= s
    const ll k = 1e7;
    ll ans = 0;
    rep(i, 1, k) {
        int it = upper_bound(all(slack), ((s-1)/i+1)*i) - begin(slack);
        if(it == sz(slack)) continue;
        // cerr << i << "=" << it << endl;
        ans += it;
    }
    // cerr << s << " " << t << endl;
    // x >= k
    rep(i, 1, n+1) {
        ll lb = slack[i-1];
        ll ub = slack[i];
        // cerr << "lb=" << lb << " ub=" << ub << endl;
        // iterate over v and count x in [k, t] such that vx in [lb, ub) and (v-1)x < lb
        // smallest x such that (v-1)x >= s
        // (v+1)
        // x = ceil(s / (v-1))
        for(ll v = 1; v * k < ub; v++) {
            ll r = (ub-1)/v+1;
            ll l = (lb-1)/v+1;
            if(v > 1) {
                r = min(r, (s-1)/(v-1)+1);
            }
            l = min(l, r);
            r = clamp(r, k, t+1);
            l = clamp(l, k, t+1);
            ans += (r-l)*i;
            // cerr << i << " v" << v << " r" << r << " l" << l << " r-l*i" << (r-l)*i << endl;
        }
    }
    return ans;
}

ll bf(vl a, vl b) {
    int n = sz(a);
    ll s = 0, t = 0;
    vl diffs;
    rep(i, 0, n) {
        s += a[i], t += b[i];
        diffs.push_back(b[i]-a[i]);
    }
    vl slack{s+1};
    sort(all(diffs));
    reverse(all(diffs));
    rep(i, 0, n) {
        slack.push_back(slack.back() + diffs[i]);
    }
    ll ans = 0;
    rep(i, 1, t+1) {
        int it = upper_bound(all(slack), ((s-1)/i+1)*i) - begin(slack);
        if(it == sz(slack)) continue;
        cerr << i << " " << it << endl;
        ans += it;
    }
    return ans;
}


int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    // int cnt = 0;
    // while(true) {
    //     // if(cnt % 100 == 0) 
    //     cerr << cnt << endl;
    //     cnt++;
    //     auto [a, b] = gen(5);
    //     ll d = bf(a, b);
    //     ll c = solve(a, b);
    //     if(c != d) {
    //         rep(i, 0, sz(a)) {
    //             cerr << a[i] << " ";
    //         }
    //         cerr << endl;
    //         rep(i, 0, sz(b)) {
    //             cerr << b[i] << " ";
    //         }
    //         cerr << endl;
    //         cerr << c << " " << d << endl;
    //         break;
    //     }
    // }

    int n; cin >> n;
    vl a(n), b(n);
    rep(i, 0, n) {
        cin >> a[i] >> b[i];
    }

    
    cout << solve(a, b) << "\n";
    
    return 0;
}


/*
6,6: 1,2,3,6
7,8: 7,4,8
9,9: 9


*/
