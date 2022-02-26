//NOTE: This solution is overcomplicated

#include "bits/stdc++.h"
using namespace std;
mt19937_64 rng((int)std::chrono::steady_clock::now().time_since_epoch().count());
const int MAXN = 2e5 + 10;
const int MOD = 1e9 + 7;
#define int long long
int rnd(int x, int y) {
  int u = uniform_int_distribution<int>(x, y)(rng); return u;
}
struct node {
  pair<int, int> mi = {0, 0};
  pair<int, int> ma = {0, 0};
  int upd = 0;
} st[4*MAXN];

void u(int l, int r, int constl, int constr, int idx, int val) {
  if(l <= constl && constr <= r) {
    st[idx].mi.first += val;
    st[idx].ma.first += val;
    st[idx].upd += val;
    if(constl == constr) st[idx].mi.second = st[idx].ma.second = constl;
    return;
  }
  int mid = (constl + constr) >> 1;
  if(st[idx].upd != 0) {
    st[2*idx+1].mi.first += st[idx].upd;
    st[2*idx+1].ma.first += st[idx].upd;
    st[2*idx+2].mi.first += st[idx].upd;
    st[2*idx+2].ma.first += st[idx].upd;
    st[2*idx+1].upd += st[idx].upd;
    st[2*idx+2].upd += st[idx].upd;
    st[idx].upd = 0;
    st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
    st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
  }
  if(mid < l || r < constl) u(l, r, mid+1, constr, 2*idx+2, val);
  else if(constr < l || r < mid+1) u(l, r, constl, mid, 2*idx+1, val);
  else {
    u(l, r, constl, mid, 2*idx+1, val);
    u(l, r, mid+1, constr, 2*idx+2, val);
  }
  st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
  st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
}

pair<int, int> qu1(int l, int r, int constl, int constr, int idx) { // range Max
  if(l <= constl && constr <= r) return st[idx].ma;
  int mid = (constl + constr) >> 1;
  if(st[idx].upd != 0) {
    st[2*idx+1].mi.first += st[idx].upd;
    st[2*idx+1].ma.first += st[idx].upd;
    st[2*idx+2].mi.first += st[idx].upd;
    st[2*idx+2].ma.first += st[idx].upd;
    st[2*idx+1].upd += st[idx].upd;
    st[2*idx+2].upd += st[idx].upd;
    st[idx].upd = 0;
    st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
    st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
  }
  if(mid < l || r < constl) return qu1(l, r, mid+1, constr, 2*idx+2);
  else if(constr < l || r < mid+1) return qu1(l, r, constl, mid, 2*idx+1);
  else {
    return max(qu1(l, r, constl, mid, 2*idx+1), qu1(l, r, mid+1, constr, 2*idx+2));
  }
}
pair<int, int> qu2(int l, int r, int constl, int constr, int idx) { // range Min
  if(l <= constl && constr <= r) return st[idx].mi;
  int mid = (constl + constr) >> 1;
  if(st[idx].upd != 0) {
    st[2*idx+1].mi.first += st[idx].upd;
    st[2*idx+1].ma.first += st[idx].upd;
    st[2*idx+2].mi.first += st[idx].upd;
    st[2*idx+2].ma.first += st[idx].upd;
    st[2*idx+1].upd += st[idx].upd;
    st[2*idx+2].upd += st[idx].upd;
    st[idx].upd = 0;
    st[idx].mi = min(st[2*idx+1].mi, st[2*idx+2].mi);
    st[idx].ma = max(st[2*idx+1].ma, st[2*idx+2].ma);
  }
  if(mid < l || r < constl) return qu2(l, r, mid+1, constr, 2*idx+2);
  else if(constr < l || r < mid+1) return qu2(l, r, constl, mid, 2*idx+1);
  else {
    return min(qu2(l, r, constl, mid, 2*idx+1), qu2(l, r, mid+1, constr, 2*idx+2));
  }
}

int cur_range = 0;
void fluctuate(int v) {
  if(cur_range == 0) {
    return;
  }
  u(1, cur_range, 0, MAXN - 1, 0, v);
  while(cur_range > 0) {
    pair<int, int> res = qu2(1, cur_range, 0, MAXN - 1, 0);
    if(res.first < 0) {
      // no more
      if(res.second == cur_range) {
        u(cur_range, cur_range, 0, MAXN - 1, 0, -res.first); // becomes 0
        cur_range--;
      }
      else {
        int ono = qu1(cur_range, cur_range, 0, MAXN - 1, 0).first;
        u(res.second, res.second, 0, MAXN - 1, 0, ono - res.first);
        u(cur_range, cur_range, 0, MAXN - 1, 0, -ono);
        cur_range--;
      }
    }
    else break;
  }
}

void insert(int v) {
  cur_range++;
  u(cur_range, cur_range, 0, MAXN - 1, 0, v);
}
void sell() {
  if(cur_range == 0) {
    cout << "-1\n"; return;
  }
  pair<int, int> res = qu1(1, cur_range, 0, MAXN - 1, 0);
  if(res.first >= 0) {
    cout << res.first << "\n";
    if(res.second == cur_range) {
      u(cur_range, cur_range, 0, MAXN - 1, 0, -res.first); // becomes 0
      cur_range--;
    }
    else {
      int ono = qu1(cur_range, cur_range, 0, MAXN - 1, 0).first;
      u(res.second, res.second, 0, MAXN - 1, 0, ono - res.first);
      u(cur_range, cur_range, 0, MAXN - 1, 0, -ono);
      cur_range--;
    }
    return;
  }
  else {
    cout << "-1\n"; return;
  }
}

void solve(int tc) {
  int q;
  cin >> q;
  while(q--) {
    int op;
    cin >> op;
    if(op == 1) {
      int v;
      cin >> v;
      insert(v);
    }
    else if(op == 2) {
      sell();
    }
    else {
      int x;
      cin >> x;
      fluctuate(x);
    }
  }
  int sum = 0;
  for(int i=1; i<=cur_range; i++) sum += qu1(i, i, 0, MAXN - 1, 0).first;
  cout << sum << "\n";
}

int32_t main(){
  time_t t0 = clock();
  ios::sync_with_stdio(0); cin.tie(0);
  int t = 1; //cin >> t;
  for(int i=1; i<=t; i++) solve(i);
  t0 = clock() - t;
  //cerr << "Time used: " << fixed << setprecision(3) << (double)(t0 * 1.0 / CLOCKS_PER_SEC) << " seconds\n";
}  
//祝各位 人品爆棚 
