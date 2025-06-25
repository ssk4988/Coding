#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;
using vii = vector<pii>;
using vl = vector<ll>;

#define all(x) begin(x), end(x)
#define sz(x) (int)x.size()
#define rep(i, a, b) for(int i = a; i < (b); i++)
// int created = 0;

int treesize = 0;
struct Node;
const int M = (4e5+10) * 23;
// vector<Node> tree = {};
struct Node {
    int bit, sum=0;
    int child[2];
    Node() {}
    Node(int bit) : bit(bit){
        // created++;
        child[0] = child[1] = -1;
    }
};
Node tree[M];
void push(int u) {
    if(tree[u].child[0] != -1 || tree[u].bit < 0) return;
    // cerr << sz(child) << endl;
    // cerr << sz(tree) << endl;
    rep(b, 0, 2) {
        // cerr << "is " << child[b] << " " << b << endl;
        tree[u].child[b] = treesize;
        tree[treesize++] = Node(tree[u].bit-1);
        // child[b] = new Node(bit-1);
    }
}
void add(int u, int x) {
    if(tree[u].bit == -1) {
        tree[u].sum++;
        return;
    }
    push(u);
    int v = tree[u].child[(x >> tree[u].bit)&1];
    add(v, x);
    tree[u].sum++;
}
// given y,z count num x such that x^y > z
int count(int u, int y, int cur_xy, int z, int cur_z) {
    if(cur_xy != cur_z) {
        return cur_xy > cur_z ? tree[u].sum : 0;
    }
    if(tree[u].bit == -1) return 0;
    push(u);
    int ans = 0;
    rep(i, 0, 2) {
        ans += count(tree[u].child[i], y, cur_xy ^ ((i ^ ((y >> tree[u].bit)&1)) << tree[u].bit), z, cur_z ^ (z & (1 << tree[u].bit)));
    }
    return ans;
}

template<class T>
struct RMQ {
	vector<vector<T>> jmp;
	RMQ(const vector<T>& V) : jmp(1, V) {
		for (int pw = 1, k = 1; pw * 2 <= sz(V); pw *= 2, ++k) {
			jmp.emplace_back(sz(V) - pw * 2 + 1);
			rep(j,0,sz(jmp[k]))
				jmp[k][j] = max(jmp[k - 1][j], jmp[k - 1][j + pw]);
		}
	}
	T query(int a, int b) {
		assert(a < b); // or return inf if a == b
		int dep = 31 - __builtin_clz(b - a);
		return max(jmp[dep][a], jmp[dep][b - (1 << dep)]);
	}
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);

    int n; cin >> n;
    vi a(n);
    vii b(n);
    rep(i, 0, n) {
        cin >> a[i];
        b[i].first = a[i];
        b[i].second = i;
    }
    RMQ<pii> rmq(b);
    ll ans = 0;
    auto dnc = [&](int l, int r, auto &&dnc) -> void {
        // cerr << l << "," << r << endl;
        if(r-l < 2) {
            if(r-l == 1) {
                tree[0] = Node(21);
                treesize = 1;
                add(0, a[l]);
            }
            return;
        }
        auto [mx, m] = rmq.query(l, r);
        bool heavyright = m-l < r-(m+1);
        if(heavyright) {
            dnc(l, m, dnc);
            tree[0] = Node(21);
            treesize = 1;
            dnc(m+1, r, dnc);
            ans += count(0, a[m], 0, mx, 0);
            add(0, a[m]);
            rep(i, l, m) {
                ans += count(0, a[i], 0, mx, 0);
            }
            rep(i, l, m) add(0, a[i]);
        } else {
            dnc(m+1, r, dnc);
            tree[0] = Node(21);
            treesize = 1;
            dnc(l, m, dnc);
            ans += count(0, a[m], 0, mx, 0);
            add(0, a[m]);
            rep(i, m+1, r) {
                ans += count(0, a[i], 0, mx, 0);
            }
            rep(i, m+1, r) add(0, a[i]);
        }
    };
    dnc(0, n, dnc);
    cout << ans << "\n";
    // cerr << "created: " << created << endl;

    return 0;
}
