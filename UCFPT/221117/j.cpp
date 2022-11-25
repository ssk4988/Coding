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
#define maxN 1005

int parent[maxN];
int siz[maxN];
int numcomps = 0;

int find(int a){
    if(parent[a] == a)    {
        return a;
    }
    return parent[a] = find(parent[a]);
}

bool join(int a, int b){
    a = find(a);
    b = find(b);
    if(a == b) return false;
    if(siz[a] < siz[b]){
        swap(a, b);
    }
    parent[b] = a;
    numcomps--;
    siz[a] += siz[b];
    return true;
}

int get_siz(int a){
    return siz[find(a)];
}

int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n, m, k;
    cin >> n >> m >>k;
    rep(i, 0, n){
        parent[i] = i;
        siz[i] = 1;
    }
    int lwb = 0;
    vector<pair<int, pi>> v(m);
    rep(i, 0, m){
        char c; cin >> c;
        int a, b; cin >> a >> b;
        a--;b--;
        v[i] = {c=='B', {a, b}};
    }
    sort(all(v));
    numcomps = n;
    rep(i, 0, m){
        if(v[i].f) break;
        join(v[i].s.f, v[i].s.s);
    }
    lwb = numcomps - 1;
    int upb = 0;
    rep(i, 0, n){
        parent[i] = i;
        siz[i] = 1;
    }
    for(int i = m - 1; i >= 0; i--){
        if(v[i].f && join(v[i].s.f, v[i].s.s)){
            upb++;
        }
    }
    cout << (upb >= k && k >= lwb ? 1 : 0) << nL;
    //cout << lwb << " " << upb << nL;

    
    return 0;
}