// D. Xenia and Bit Operations
#ifdef LOCAL_DEBUG
#include <cpp-dump.hpp>
namespace cp = cpp_dump;
CPP_DUMP_SET_OPTION_GLOBAL(es_style, cp::types::es_style_t::no_es);
CPP_DUMP_SET_OPTION_GLOBAL(log_label_func, [](auto, auto, auto) { return ""; });
#else
#define cpp_dump(...)
#endif

#include <bits/stdc++.h>
using namespace std;

#define int long long

typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vpii;
typedef vector<vi> vvi;

#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define rep1(i, n) for (int i = 1; i <= (int)(n); i++)
#define rrep(i, n) for (int i = (int)(n) - 1; i >= 0; i--)
#define fore(i, a, b) for (int i = (a); i < (int)(b); i++)
#define each(x, v) for (auto &x : v)

#define pb push_back
#define eb emplace_back
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)(x).size()
#define F first
#define S second
#define nl "\n"

#define chmin(a, b) a = min(a, b)
#define chmax(a, b) a = max(a, b)

#define yn(b) cout << ((b) ? "YES" : "NO") << nl
#define printv(v)                                                              \
  for (auto &_x : v)                                                           \
    cout << _x << " ";                                                         \
  cout << nl
#define readv(v, n)                                                            \
  v.resize(n);                                                                 \
  rep(i, n) cin >> v[i]
#define sumv(v) accumulate(all(v), 0LL)
#define minv(v) *min_element(all(v))
#define maxv(v) *max_element(all(v))
#define rsort(v) sort((v).rbegin(), (v).rend())
#define tc                                                                     \
  int _t;                                                                      \
  cin >> _t;                                                                   \
  while (_t--)

template <typename T> inline int idx(const vector<T> &v, int i) {
  return i < 0 ? (int)v.size() + i : i;
}

#ifdef LOCAL_DEBUG
#define dbg(x) cerr << #x << " = " << (x) << nl
#else
#define dbg(x)
#endif

const int INF = 2e18;
const int MOD = 1e9 + 7;

struct Stree {
  vi nums;
  int n;
  vi st;
  void pin() { cpp_dump(n, nums, st); }
  int merge(int l, int r, int depth) {
    int leafdist = n - depth;
    if ((leafdist % 2) == 0)
      return l ^ r;
    else
      return l | r;
  }
  void build(int v, int depth, int tl, int tr) {
    if (tl == tr) {
      st[v] = nums[tl];
      return;
    }
    int mid = tl + ((tr - tl) / 2);
    build(v * 2, depth + 1, tl, mid);
    build(v * 2 + 1, depth + 1, mid + 1, tr);
    st[v] = merge(st[v * 2], st[v * 2 + 1], depth);
  }
  void update(int v, int tl, int tr, int depth, int pos, int val) {
    if (tl == tr) {
      st[v] = val;
      return;
    }
    int mid = tl + ((tr - tl) / 2);
    if (mid >= pos) {
      update(v * 2, tl, mid, depth + 1, pos, val);
    } else {
      update(v * 2 + 1, mid + 1, tr, depth + 1, pos, val);
    }
    st[v] = merge(st[v * 2], st[v * 2 + 1], depth);
  }

  int query(int v, int tl, int tr, int depth, int l, int r) {
    if (l > r) {
      return 0;
    }
    if (l == tl && r == tr) {
      return st[v];
    }
    int mid = tl + ((tr - tl) / 2);
    return merge(query(v * 2, tl, min(r, mid), depth + 1, l, r),
                 query(v * 2 + 1, max(l, mid + 1), r, depth + 1, l, r), depth);
  }
};

void solve() {
  int n, m;
  cin >> n >> m;
  Stree dsa;
  readv(dsa.nums, pow(2, n));
  dsa.st.resize((pow(2, n) * 4));
  dsa.n = n;
  dsa.build(1, 0, 0, pow(2, n) - 1);
  rep(i, m) {
    int p, b;
    cin >> p >> b;
    dsa.update(1, 0, pow(2, n) - 1, 0, p - 1, b);
    cout << dsa.query(1, 0, pow(2, n) - 1, 0, 0, pow(2, n) - 1) << nl;
    dsa.pin();
  }
}

int32_t main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  // tc{ solve(); }
  solve();
}
