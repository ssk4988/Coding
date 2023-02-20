#include <bits/stdc++.h>
using namespace std;

#define all(x) begin(x),end(x)
#define nl '\n'
#define sz(x) (int)(x).size()
#define rep(i, a, b) for(int i = a; i < b; i++)

typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<pii> vii;
typedef vector<ll> vl;

ll mod(ll k, ll m){
    return (k % m + m) % m;
}


vl euclid(ll a, ll b){
    if(b == 0) return {a, 1, 0};
    vl ans = euclid(b, a % b);
    ll tmp = ans[1] - ans[2] * (a / b);
    ans[1] = ans[2]; ans[2] = tmp;
    return ans;
}

ll modinv(ll a, ll b){
    return ((euclid(a, b)[1] % b) + b) % b;
}
ll gcd(ll a, ll b){
    return b == 0 ? a : gcd(b, a % b);
}

ll ceildiv(ll a, ll b){
    // a / b
    return (a + b + (b >= 0 ? -1 : 1)) / b;
}

ll lowerdiv(ll a, ll b){
    // a / b
    return b >= 0 ? (a - 1) / b : (a + 1) / b;
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    ll n, m; cin >> n >> m;
    ll ccoef = m;

    vl a(n);
    ll sum= 0;
    rep(i, 0, n){
        cin >> a[i];
        sum = mod(a[i] + sum, m);
    }
    ll n2 = n % 2 == 0 ? n / 2 : n;
    ll g = __gcd(n2, m);
    ll inc = 0;
    if(mod(-sum, g) != 0){
        inc = g - mod(-sum, g);
    }
    ll left = inc - sum;
    // ll m2 = m;
    // left /= g;
    // m2 /= g;
    // n2 /= g;
    // vl stuff = euclid(m2, n2);

    left += m * ((n2 - left) / m - 2);
    pair<ll,ll> ans = {-1, -1};
    rep(c, 0, n2 * 4){
        if((left + m * c) % n2 != 0) continue;
        ll v = (left + m * c) / n2;
        if(n % 2 == 0){
            if(v >= n + 1){
                ans = {(v - (n + 1)) / 2, 1};
                break;
            }
        }
        else{
            if(v >= 0){
                ans = {v, 0};
                break;
            }
        }
    }
    cout << inc << nl << ans.first << " " << ans.second << nl;
    // ll scoef = n;
    // ll dcoef = n * (n + 1) / 2;
    // ll g = gcd(abs(scoef), abs(dcoef));
    // ll cval = -1;
    // ll inc = -1;
    // ll amt = 0;
    // if(mod(m, g) == 0){
    //     ll nsum = mod(-sum, m);
    //     ll curmod = mod(nsum, g);
    //     inc = mod(g - curmod, g);
    //     cval = 0;
    //     amt = m / g;
    // }
    // else{
    //     cval = mod(mod(sum, g) * modinv(m, g), g);
    //     inc = 0;
    //     amt = g * m;
    // }
    // // sum = mod(-sum + inc, m);
    // ll leftside = m * cval - sum + inc;


    // // dcoef -= ccoef;
    // // ll 
    // // sum += inc;
    // // assert(mod(sum, g) == 0);
    // // assert(mod(scoef, g) == 0);
    // // assert(mod(dcoef, g) == 0);
    // leftside /= g;
    // scoef /= g;
    // dcoef /= g;
    // // check case where scoef or dcoef are 0
    // vl stuff = euclid(scoef, dcoef);
    // // vl stuff1 = euclid(2, 7);
    // bool diffsign = scoef * dcoef < 0;
    // ll schange = dcoef;
    // ll dchange = -scoef;
    // ll& sconst = stuff[1];
    // ll& dconst = stuff[2];
    // bool foundans = false;
    // pair<ll, ll> ans = {-1, -1};
    // // schange *= scale;
    // // dchange *= scale;
    // // check schange is 0? can only happen if scoef or dcoef are 0
    // // ll zeros = ceildiv(sconst, schange);
    // // ll zerod = ceildiv(dconst, dchange);
    // // ll ms = lowerdiv(m - sconst, schange);
    // // ll md = lowerdiv(m - dconst, dchange);
    // //ax + b
    // auto lowb = [&](ll a, ll b, ll lowv, ll highv) -> ll{
    //     bool boundl = a >= 0;
    //     ll startval = boundl ? (lowv-b) / a : (highv - b) / a;
    //     startval -= 5;
    //     while(true){
    //         if(boundl){
    //             if(startval * a + b >= lowv) break;
    //         }
    //         else{
    //             if(startval * a + b < highv) break;
    //         }
    //         startval++;
    //     }
    //     return startval;
    // };
    // auto highb = [&](ll a, ll b, ll lowv, ll highv) -> ll{
    //     bool boundh = a >= 0;
    //     ll startval = boundh ? (highv-b) / a : (lowv - b) / a;
    //     startval += 5;
    //     while(true){
    //         if(boundh){
    //             if(startval * a + b < highv) break;
    //         }
    //         else{
    //             if(startval * a + b >= lowv) break;
    //         }
    //         startval--;
    //     }
    //     return startval;
    // };
    // auto f = [](ll a, ll b, ll x) -> ll{
    //     return a * x + b;
    // };
    // auto sc = [&](ll left) -> void{
    //     ll scale = left / stuff[0];
    //     sconst *= scale;
    //     dconst *= scale;
    //     ll mins = schange == 0 ? 0 : lowb(schange, sconst, 0, m);
    //     ll mind = dchange == 0 ? 0 : lowb(dchange, dconst, 0, m);
    //     ll maxs = schange == 0 ? 0 : highb(schange, sconst, 0, m);
    //     ll maxd = dchange == 0 ? 0 : highb(dchange, dconst, 0, m);
    //     ll val = max(mins, mind);
    //     if(val <= maxs && val <= maxd){
    //         foundans = true;
    //         ans = {f(schange, sconst, val), f(dchange, dconst, val)};
    //     }
    //     if(scale != 0) sconst /= scale;
    //     if(scale != 0) dconst /= scale;
    // };
    // for(ll l = leftside; !foundans; l += m / g){
    //     sc(l);
    // }
    
    
    // cout << inc << nl;
    
    // // assert(schange == 0 || scoef == 0 || dcoef == 0 || val <= maxs);
    // // assert(schange == 0 || scoef == 0 || dcoef == 0 || val <= maxd);
    // cout << ans.first << " " << ans.second << nl; 

    return 0;
}
