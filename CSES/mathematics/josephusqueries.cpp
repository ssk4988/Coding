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

ll solve2(ll n, ll k){
    ll p = 2;
    ll i1 = 1, i2 = 2;
    ll parity = 1;
    // cout << "prediction: ";
    while(n > 0){
        ll val;
        if(parity == 1){
            // cout << i2 << " ";
            val = i2;
            i2 = -1;
        }
        else{
            val = i1;
            // cout << i1 << " " ;
            i1 = i2; i2 = -1;
        }
        i2 = i1 + p;
        ll tmp = parity;
        parity = parity ^ (n % 2);
        ll rem = (n + 1 - tmp) / 2;
        if(k <= rem){
            return val + (k - 1) * p;
        }
        n -= rem;
        k -= rem;
        p<<=1;
    }
    // cout << nL;
    return -1;
}

vi solve(int n){
    set<int> left;
    rep(i, 1, n + 1){
        left.insert(i);
    }
    vi seq;
    vi seq2;
    int parity = 0;
    while(left.size()){
        vi rem;
        int cnt = 0;
        for(int i : left){
            if(cnt >= 2) break;
            cnt++;
            cout << i << ",";
        }
        for(int i : left){
            parity = 1 - parity;
            if(parity == 0){
                rem.pb(i);
            }
        }
        if(rem.size()) seq2.pb(rem.front());
        else seq2.pb(-1);
        for(int i : rem){
            seq.pb(i);
            left.erase(i);
        }
        cout << " ";
    }
    cout << nL;
    return seq2;

}

string binstr(int n){
    string res;
    int leftover = 0;
    while(n > 0){
        int tmp = leftover;
        leftover = (n - leftover) % 2;
        res.pb('0' + leftover);
        n -= (n + 1 - tmp) / 2;
    }
    // for(int i = 0; (1 << i) <= n; i++){
    //     if(n & (1 << i)) res.pb('1');
    //     else res.pb('0');
    // }
    return res;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int q; cin >> q;
    rep(i, 0, q){
        ll n, k; cin >> n >> k;
        cout << solve2(n, k) << nL;
    }

    return 0;
}