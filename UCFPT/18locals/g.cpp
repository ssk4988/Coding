#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pi = pair<int, int>;
using vl = vector<ll>;

#define sz(x) (int) x.size()
#define all(x) begin(x), end(x)
#define rep(i, a, b) for(int i = a; i < (b); i++)
#define pb push_back
#define f first
#define s second

template<class T>
struct Point{
    typedef Point P;
    T x, y;
    explicit Point(T x = 0, T y=0) : x(x), y(y){}
    P operator+(P p) const { return P(x + p.x, y + p.y); }
    P operator-(P p) const { return P(x - p.x, y - p.y); }
    T dot(P p) const { return x * p.x + y * p.y; }
    T cross(P p) const { return x * p.y - y * p.x; }
    T cross(P a, P b) const { return (a - *this).cross(b - *this); }
    T dist2() const { return x * x + y * y; }
};

using P = Point<ll>;

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    int n; cin >> n;
    vector<P> a(n), b(n);
    rep(i, 0, n){
        cin >> a[i].x >> a[i].y;
    }
    rep(i, 0, n){
        cin >> b[i].x >> b[i].y;
    }
    vector<vi> adj(n);
    vi dist(n, INT_MAX);
    dist[0] = 0;
    auto block = [](P a, P b, P c)->bool{
        // c blocks ab
        ll cv = a.cross(b, c);
        if(cv != 0) return false;
        ll dp = (b - a).dot(c - a);
        if(dp < 0) return false;
        ll d1 = (c - a).dist2(), d2 = (b - a).dist2();
        return d1 < d2;
    };
    rep(i, 0, n){
        rep(j, 0, n){
            if(i == j) continue;
            bool blocked = false;
            rep(k, 0, n){
                if(k == i || k == j) continue;
                if(block(a[i], a[j], a[k])) blocked = true;
            }
            rep(k, 0, n){
                if(block(a[i], a[j], b[k])) blocked = true;
            }
            if(!blocked) adj[i].pb(j);
        }
    }
    priority_queue<pi, vector<pi>, greater<pi>> pq;
    pq.push({dist[0], 0});
    vi visited(n);
    while(!pq.empty()){
        auto [d, x] = pq.top();
        pq.pop();
        if(visited[x]) continue;
        visited[x] = true;
        for(auto y : adj[x]){
            if(!visited[y] && dist[y] > dist[x] + 1){
                dist[y] = dist[x] + 1;
                pq.push({dist[y], y});
            }
        }
    }
    if(dist[n - 1] == INT_MAX) dist[n - 1] = -1;
    cout << dist[n - 1] << "\n";
}
