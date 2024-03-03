#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef long double ld;

typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
typedef pair<ld, ld> pd;

typedef vector<int> vi;
typedef vector<ll> vl;
typedef vector<ld> vd;
typedef vector<pi> vpi;
typedef vector<pl> vpl;
typedef vector<pd> vpd;



#define f first
#define s second
#define mp make_pair
#define pb push_back
#define lb lower_bound
#define ub upper_bound
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()




struct st { int len, pos, term; st *link; unordered_map<int, st*> next; bool forward = false;
  bool dfsd = false;
  ll pforward = 0;
};
st *suffixAutomaton(vi &str) {
	st *last = new st(), *root = last;
	for(auto c : str) {
		st *p = last, *cur = last = new st{last->len + 1, last->len};
		while(p && !p->next.count(c))
			p->next[c] = cur, p = p->link;
		if (!p) cur->link = root;
		else {
			st *q = p->next[c];
			if (p->len + 1 == q->len) cur->link = q;
			else {
				st *clone = new st{p->len+1, q->pos, 0, q->link, q->next};
				for (; p && p->next[c] == q; p = p->link)
					p->next[c] = clone;
				q->link = cur->link = clone;
			}
		}
	}
	while(last) last->term = 1, last = last->link;
  auto gof = [&](st *cur, auto &&gof) -> void {
    if(cur->forward) return;
    cur->forward = true;
    for(auto [key, nex] : cur->next){
      gof(nex, gof);
      cur->pforward += nex->pforward;
    }
    cur->pforward += cur->term;
  };
  gof(root, gof);
  return root;
}

using vvi = vector<vi>;
void solve() {
  int n; cin >> n;
  basic_string<int> a;
  vi a1;
  for(int i = 0; i < n; i++) {
    int v; cin >> v; v++;
    a.push_back(v);
    a1.push_back(v);
    // cin >> a[i];
  }
  st* root = suffixAutomaton(a1);
  vi freq(n+1);
  vector<st*> order;
  auto dfs = [&](st *cur, auto &&dfs) -> void {
      if(cur->dfsd) return;
      cur->dfsd = true;
      for(auto [key, nex] : cur->next){
        dfs(nex, dfs);
      }
      order.pb(cur);
      if(cur != root){
        int times = cur->len - (cur->link->len);
        freq[cur->pforward] += times;
      }
  };
  dfs(root, dfs);
  for(st *cur : order){
    free(cur);
  }
  ll ans = 0;
  bool good = true;
  deque<pi> q;
  auto add = [&](int key, int val) -> void {
    if(key <= n){
        freq[key] += val;
    }
    else {
        q.push_back({key, val});
    }
  };
  rep(i, 1, n+1){
    while(good){
      int k1 = i;
      int f1 = freq[k1];
      if(f1 == 0) break;
    //   cout << k1 << " " << f1 << "\n";
      if(f1 == 1){
        int nexocc = i+1;
        while(nexocc <= n && freq[nexocc] == 0) nexocc++;
        if(nexocc > n) {
          good = false;
          break;
        }
        freq[nexocc]--;
        ans += nexocc + k1;
        // cout << "combining " << k1 << " and " << nexocc << "\n";
        add(nexocc + k1, 1);
        // freq[nexocc + k1] += 1;
        freq[k1] = 0;
      }
      else{
        // self match
        ll times = f1 / 2;
        ans += k1 * times * 2;
        add(k1 * 2, times);
        // freq[k1 * 2] += times;
        freq[k1] = f1 % 2;
      }
    }
  }
  for(int i = n; i >= 1; i--) {
    if(freq[i]){
        q.push_front({i, freq[i]});
    }
  }
  while(true){
    auto [k1, f1] = q.front(); q.pop_front();
    // cout << k1 << " " << f1 << endl;
    if(f1 == 1){
      if(sz(q)){
        auto [k2, f2] = q.front();
        q.pop_front();
        f2--;
        ans += k2 + k1;
        q.push_back({k2 + k1, 1});
        if(f2){
          q.push_front({k2, f2});
        }
      }
      else break;
    }
    else{
      // self match
      ll times = f1 / 2;
      ans += k1 * times * 2;
      q.push_back({k1 * 2, times});
      if(f1 % 2){
        q.push_front({k1, f1 % 2});
      }
    }
  }
  ll denom = ll(n) * (n+1) / 2;
  ll g = __gcd(denom, ans);
  denom /= g, ans /= g;
  if(denom == 1){
    cout << ans << "\n";
  }
  else cout << ans << "/" << denom << "\n";
}

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int tc; cin >> tc;

  for(int tt = 1; tt <= tc; tt++) {
    solve();
  }

  return 0;
}