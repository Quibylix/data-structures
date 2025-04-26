#include <bits/stdc++.h>
using namespace std;

struct SegmentTree {
  int n;
  vector<int> data, lazy;

  SegmentTree(vector<int> &values) {
    n = values.size();
    data.assign(4 * n, 0);
    lazy.assign(4 * n, -1); // -1 means "no pending assignment"
    _build(1, 0, n - 1, values);
  }

  void _build(int node, int l, int r, vector<int> &values) {
    if (l == r) {
      data[node] = values[l];
      return;
    }
    int mid = (l + r) / 2;
    _build(2 * node, l, mid, values);
    _build(2 * node + 1, mid + 1, r, values);
    data[node] = data[2 * node] + data[2 * node + 1];
  }

  void push(int node, int l, int r) {
    if (lazy[node] != -1) {
      data[node] = lazy[node] * (r - l + 1);
      if (l != r) {
        lazy[node * 2] = lazy[node];
        lazy[node * 2 + 1] = lazy[node];
      }
      lazy[node] = -1;
    }
  }

  void update(int ql, int qr, int val) { _update(1, 0, n - 1, ql, qr, val); }

  void _update(int node, int l, int r, int ql, int qr, int val) {
    push(node, l, r);

    if (qr < l || ql > r)
      return; // no overlap

    if (ql <= l && r <= qr) {
      lazy[node] = val;
      push(node, l, r);
      return;
    }

    int mid = (l + r) / 2;
    _update(2 * node, l, mid, ql, qr, val);
    _update(2 * node + 1, mid + 1, r, ql, qr, val);
    data[node] = data[2 * node] + data[2 * node + 1];
  }

  int query(int ql, int qr) { return _query(1, 0, n - 1, ql, qr); }

  int _query(int node, int l, int r, int ql, int qr) {
    push(node, l, r);

    if (qr < l || ql > r)
      return 0; // no overlap

    if (ql <= l && r <= qr)
      return data[node]; // total overlap

    int mid = (l + r) / 2;
    return _query(2 * node, l, mid, ql, qr) +
           _query(2 * node + 1, mid + 1, r, ql, qr);
  }
};

int main() {
  vector<int> values = {1, 2, 3, 4, 7};
  SegmentTree st(values);

  st.update(0, 1, 2);             // set range [0, 1] to 2
  cout << st.query(0, 4) << endl; // total sum

  for (int i = 0; i < values.size(); i++) {
    cout << st.query(i, i) << endl; // each value individually
  }

  return 0;
}
