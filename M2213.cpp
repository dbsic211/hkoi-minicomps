#include "bits/stdc++.h"
using namespace std;
mt19937_64 rng((int)std::chrono::steady_clock::now().time_since_epoch().count());
const int MAXN = 4e5 + 10;
const int MOD = 1e9 + 7;
#define int long long
int rnd(int x, int y) {
  int u = uniform_int_distribution<int>(x, y)(rng); return u;
}
vector<pair<int, int> > adj[MAXN];
unordered_map<int, int> id;
void solve(int tc) {
  int n, m;
  cin >> n >> m;
  vector<int> v;
  int a[2*n+1];
  for(int i=1; i<=2*n; i++) cin >> a[i];
  for(int i=1; i<=2*n; i++) {
    v.push_back(a[i]);
  }
  int now = 2*n + 1;
  int prv = -1;
  sort(v.begin(), v.end());
  vector<int> s;
  for(int i=0; i<v.size(); i++) {
    if(i == 0 || v[i] !=v[i-1]) s.push_back(v[i]);
  }
  for(int x: s) {
    id[x] = now;
    if(now != 2*n + 1) {
      adj[now].push_back({now - 1, x - prv});
      adj[now - 1].push_back({now, x - prv});
    }
    prv = x;
    now++;
  }
  const int POTATO = 1e15;
  for(int i=1; i<=2*n; i++) {
    adj[i].push_back({id[a[i]], POTATO});
    adj[id[a[i]]].push_back({i, POTATO});
  }
  for(int i=1; i<=m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }
  for(int i=1; i<=m; i++) {
    int u, v, w;
    cin >> u >> v >> w;
    u += n, v += n;
    adj[u].push_back({v, w});
    adj[v].push_back({u, w});
  }
  int dist[4*n + 1];
  int vis[4*n + 1];
  for(int i=1; i<=4*n; i++) {
    dist[i] = 1e18;
    vis[i] = 0;
  }
  dist[1] = 0;
  priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > >pq;
  pq.push({dist[1], 1});
  while(pq.size()) {
    pair<int, int> t = pq.top();pq.pop();
    if(!vis[t.second]) {
      vis[t.second] = 1;
      for(auto x: adj[t.second]) {
        if(!vis[x.first] && dist[t.second] != 1e18 && dist[x.first] > dist[t.second] + x.second) {
          dist[x.first] = dist[t.second] + x.second;
          pq.push({dist[x.first], x.first});
        }
      }
    }
  }
  cout << dist[n + 1] - 2 * POTATO << '\n';
}

int32_t main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int t = 1; //cin >> t;
  for(int i=1; i<=t; i++) solve(i);
}  
//祝各位 人品爆棚 
