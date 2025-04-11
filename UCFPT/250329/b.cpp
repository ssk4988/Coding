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

pii parse(int v) { return {v >> 4, v&15}; }

pair<bool, int> test(vi buf, int x, int input) {
    buf.back() = input;
    int ip = 0;
    int cnt = 0;
    while(!(ip >= (1 << 12)-2)) {
        if(ip == 128) {
            // cerr << "on " << input << " used " << cnt << " moves to get to 128 io=" << buf.back() << " should be " << (x^input) << endl;
            assert(buf.back() == x ^ input);
        }
        auto [ai, ab] = parse(buf[ip]);
        auto [bi, bb] = parse(buf[ip+1]);
        if(max(ai, bi) >= (1 << 12) || cnt > 1000) {
            assert(false);
            return {false, cnt};
        }
        int bit = (buf[ai] >> ab)&1;
        if(bit) buf[bi] |= 1 << bb;
        else buf[bi] &= ~(1 << bb);
        ip = buf[ip+2];
        cnt++;
    }
    return {(input == x) == (buf.back()&1), cnt};
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int x; cin >> x;
    vi buf(1 << 12);
    int zero = sz(buf)-3, one = sz(buf)-2, io = sz(buf)-1;
    buf[zero] = 0;
    buf[one] = 1;
    int k = 8;
    int cur = 0;
    auto cp = [&](int addr, int bit) -> int { return (addr << 4) + bit; };
    rep(b, 0, 16) {
        int bit = (x >> b) & 1;
        buf[cur] = cp(io, b);
        buf[cur+1] = cp(cur+2, k);
        buf[cur+2] = cur+4;
        int cur0 = cur+4, cur1 = cur+4+(1<<k);
        buf[cur0] = cp(bit ? one : zero, 0);
        buf[cur1] = cp(bit ? zero : one, 0);
        buf[cur0+1] = buf[cur1+1] = cp(io, b);
        buf[cur0+2] = buf[cur1+2] = cur+8;
        cur += 8;
    }
    cerr << cur << endl;
    rep(b, 0, 16) {
        buf[cur] = cp(io, b);
        buf[cur+1] = cp(cur+2, k);
        buf[cur+2] = cur+4;
        int cur1 = cur+4+(1<<k);
        buf[cur1] = cp(zero, 0);
        buf[cur1+1] = cp(io, 0);
        buf[cur1+2] = io;
        cur += 4;
    }
    buf[cur] = cp(one, 0);
    buf[cur+1] = cp(io, 0);
    buf[cur+2] = io;
    assert(cur < (1 << k));
    cerr << cur << endl;
    
    // rep(b, 0, 1 << 16) {
    //     auto [works, cnt] = test(buf, x, b);
    //     if(!works){
    //         cout << "failed on input " << b << " using " << cnt << " moves" << endl;
    //         return 0;
    //     }
    // }

    rep(i, 0, sz(buf)-1){
        printf("%04x ", buf[i]);
    }
    printf("\n");
    
    return 0;
}
