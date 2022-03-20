#include "bits/stdc++.h"
using namespace std;
const int MAXN = 2e5 + 10;
const int MOD = 1e9 + 7;
#define int long long
mt19937_64 rng((int)std::chrono::steady_clock::now().time_since_epoch().count());
int rnd(int x, int y) {
  int u = uniform_int_distribution<int>(x, y)(rng); return u;
}

void solve(int tc) {
  // if i get ka chang i will be very sad
  int n, m, q;
  cin >> n >> m >> q;
  multiset<pair<int, pair<int, int> > > rows[n], cols[m]; // du liu
  for(int i=0; i<n; i++) rows[i].insert({m, {0, 0}});
  for(int i=0; i<m; i++) cols[i].insert({n, {0, 0}});
  for(int i=0; i<q; i++) {
    int t;
    cin >> t;
    if(t == 1) {
      int r, c, k, a;
      cin >> r >> c >> k >> a;
      rows[r].insert({c, {k, a}});
      cols[c].insert({r, {k, a}});
    }
    else {
      char v;
      cin >> v;
      int w, x, y;
      cin >> w >> x >> y;
      if(v == 'R') {
        auto it = rows[w].lower_bound({x, {0, 0}});
        unordered_map<int, int> freq;
        int best = -1, id = -1;
        vector<pair<int, pair<int, int> > >tor;
        while((*it).first <= y) {
          tor.push_back(*it);
          cols[(*it).first].erase({w, (*it).second});
          freq[(*it).second.second] += (*it).second.first;
          if(freq[(*it).second.second] > best) {
            best = freq[(*it).second.second];
            id = (*it).second.second;
          }
          else if(freq[(*it).second.second] == best) {
            id = min(id, (*it).second.second);
          }
          it++;
        }
        for(pair<int, pair<int, int> > z: tor) {
          rows[w].erase(z);
        }
        cout << id << '\n';
      }
      else {
        auto it = cols[w].lower_bound({x, {0, 0}});
        unordered_map<int, int> freq;
        int best = -1, id = -1;
        vector<pair<int, pair<int, int> > > tor;
        while((*it).first <= y) {
          tor.push_back(*it);
          rows[(*it).first].erase({w, (*it).second});
          freq[(*it).second.second] += (*it).second.first;
          if(freq[(*it).second.second] > best) {
            best = freq[(*it).second.second];
            id = (*it).second.second;
          }
          else if(freq[(*it).second.second] == best) {
            id = min(id, (*it).second.second);
          }
          it++;
        }
        for(pair<int, pair<int, int> > z: tor) {
          cols[w].erase(z);
        }
        cout << id << '\n';
      }
    }
  }
}
int32_t main(){
  ios::sync_with_stdio(0); cin.tie(0);
  int t = 1; //cin >> t;
  for(int i=1; i<=t; i++) solve(i);
} 
//祝大家 人品爆棚
