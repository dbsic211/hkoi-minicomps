#include "bits/stdc++.h"
using namespace std;
const int MAXN = 2e5 + 10;
const int MOD = 1e9 + 7;
#define int long long
mt19937_64 rng((int)std::chrono::steady_clock::now().time_since_epoch().count());
int rnd(int x, int y) {
  int u = uniform_int_distribution<int>(x, y)(rng); return u;
}

vector<pair<int, int> >adj[MAXN];
int a[MAXN];
int sum[MAXN];
int cur = 0, ans = 1e18;
vector<int> id;
void dfs(int node, int prv, int io) {
  sum[node] = a[node];
  cur += io * a[node];
  for(auto x: adj[node]) {
    if(x.first != prv) {
      dfs(x.first, node, io + x.second);
      sum[node] += sum[x.first];
    }
  }
}

void reroot(int old_rt, int new_rt, int weight, int wow) {
  if(wow == 0) {
    int subtr = sum[new_rt];
    int rem = sum[1] - subtr;
    cur += weight * (rem - subtr);
  }
  else {
    int subtr = sum[old_rt];
    int rem = sum[1] - subtr;
    cur -= weight * (rem - subtr);
  }
}

void dpf(int node, int prv) {
  if(cur < ans) {
    ans = cur;
    id.clear();
    id.push_back(node);
  }
  else if(cur == ans) {
    id.push_back(node);
  }
  for(auto x: adj[node]) {
    if(x.first != prv) {
      reroot(node, x.first, x.second, 0);

      dpf(x.first, node);

      reroot(x.first, node, x.second, 1);
    }
  }
}

void solve(int tc) {
  int n;
  cin >> n;
  for(int i=1; i<n; i++) {
    int u, v, w; cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }
  for(int i=1; i<=n; i++) {
    cin >> a[i];
  }
  dfs(1, -1, 0);
  dpf(1, -1);
  cout << ans << '\n';
  sort(id.begin(), id.end());
  for(int X: id) cout <<X << ' ';
  cout << '\n';
}
int32_t main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int t = 1; //cin >> t;
  for(int i=1; i<=t; i++) solve(i);
} 
//祝大家 人品爆棚
