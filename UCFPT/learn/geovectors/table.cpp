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

template <class T> int sgn(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
	typedef Point P;
	T x, y;
	explicit Point(T x=0, T y=0) : x(x), y(y) {}
	bool operator<(P p) const { return tie(x,y) < tie(p.x,p.y); }
	bool operator==(P p) const { return tie(x,y)==tie(p.x,p.y); }
	P operator+(P p) const { return P(x+p.x, y+p.y); }
	P operator-(P p) const { return P(x-p.x, y-p.y); }
	P operator*(T d) const { return P(x*d, y*d); }
	P operator/(T d) const { return P(x/d, y/d); }
	T dot(P p) const { return x*p.x + y*p.y; }
	T cross(P p) const { return x*p.y - y*p.x; }
	T cross(P a, P b) const { return (a-*this).cross(b-*this); }
	T dist2() const { return x*x + y*y; }
	ld dist() const { return sqrt((ld)dist2()); }
	// angle to x-axis in interval [-pi, pi]
	ld angle() const { return atan2(y, x); }
	P unit() const { return *this/dist(); } // makes dist()=1
	P perp() const { return P(-y, x); } // rotates +90 degrees
	P normal() const { return perp().unit(); }
	// returns point rotated 'a' radians ccw around the origin
	P rotate(ld a) const {
		return P(x*cos(a)-y*sin(a),x*sin(a)+y*cos(a)); }
	friend ostream& operator<<(ostream& os, P p) {
		return os << "(" << p.x << "," << p.y << ")"; }
};

using P = Point<ld>;
ld eps = 1e-3, eps2 = 1e-6;
int main()
{
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int nc; cin >> nc;
    rep(cn, 0, nc){
        int n, k; cin >> n >> k;
        vector<P> v(n);
        rep(i, 0, n){
            cin >> v[i].x >> v[i].y;
        }
        ll ans = 0;
        vector<vi> used(n, vi(n));
        auto dfs = [&](int c1, int c2, ld cross, ld d, vi &st, int start, auto &&dfs)->bool{
            if(sz(st) == k + 1){
                if(c2 == start && v[start] < v[c1]){
                    // for(auto &p : st) cout << v[p] << " ";
                    // cout << nL;
                    ans++;
                    used[st[0]][st[sz(st) - 2]] = true;
                    used[st[0]][st[1]] = true;
                    return true;
                }
                // else cout << "bruH\n";
                return false;
            }
            rep(i, 0, n){
                ld d1 = (v[i] - v[c2]).dist2();
                if(fabs(d1 - d) > eps)continue;
                ld angle = asin((v[i] - v[c2]).unit().cross((v[c1] - v[c2]).unit()));
                ld dif2 = v[c2].cross(v[c1], v[i]);
                if(fabs(v[c2].cross(v[c1], v[i]) - cross) > eps) continue;
                // if(fabs(cross - angle) > eps2) continue;
                st.pb(i);
                if(dfs(c2, i, cross, d, st, start, dfs)){
                    st.pop_back(); return true;
                }
                st.pop_back();
            }
            return false;
        };
        int deg = (k - 2) * 180 / k;
        ld angle = deg / 180.0L * acosl(-1);
        // vector<vvi>
        rep(i, 0, n){
            rep(j, 0, n){
                if(used[i][j]) continue;
                if(v[i] < v[j]) {
                    vector<int> st = {i, j};
                    ld d = (v[j] - v[i]).dist2();
                    dfs(i, j, sin(angle) * d, d, st, i, dfs);
                }
            }
        }
        cout << ans << nL;
    }
    
    return 0;
}