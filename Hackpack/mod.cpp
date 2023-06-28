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

const ll MOD = 1000000007, LIM = 200000;
ll* inv = new ll[LIM] - 1; 
int main(){
    inv[1] = 1;
    rep(i,2,LIM) inv[i] = MOD - (MOD / i) * inv[MOD % i] % MOD;
}


// m must be positive
template<typename T>
static T mod(T a, T m)
{
    a %= m;
    if (a < 0)
        a += m;
    return a;
}

template<typename T>
static T mod(T a)
{
    a %= MOD;
    if (a < 0)
        a += MOD;
    return a;
}

// a must be relatively prime to m
template<typename T>
static T inverse(T a, T m)
{
    a = mod(a, m);
    if (a <= 1)
        return a;
    return mod((1 - inverse(m%a, a) * m) / a, m);
}

ll modpow(ll b, ll e) {
	ll ans = 1;
	for (; e; b = mod(b * b), e /= 2)
		if (e & 1) ans = mod(ans * b);
	return ans;
}
