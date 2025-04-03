#include <bits/stdc++.h>
using namespace std;

class SegmentTree {
private:
  vector<int> st;
  int n;

  void build(vector<int> &arr, int l, int r, int node) {
    if (l == r) {
      st[node] = arr[l];
      return;
    }

    int mid = (l + r) / 2;

    build(arr, l, mid, 2 * node);
    build(arr, mid + 1, r, 2 * node + 1);

    st[node] = st[2 * node] + st[2 * node + 1];
  }

  int query(int l, int r, int ql, int qr, int node) {
    if (ql > r || qr < l)
      return 0;

    if (ql <= l && r <= qr)
      return st[node];

    int mid = (l + r) / 2;

    return query(l, mid, ql, qr, 2 * node) +
           query(mid + 1, r, ql, qr, 2 * node + 1);
  }

  void update(int l, int r, int index, int value, int node) {
    if (l == r) {
      st[node] = value;
      return;
    }

    int mid = (l + r) / 2;

    if (index <= mid)
      update(l, mid, index, value, 2 * node);
    else
      update(mid + 1, r, index, value, 2 * node + 1);

    st[node] = st[2 * node] + st[2 * node + 1];
  }

public:
  SegmentTree(vector<int> &arr) {
    n = arr.size();
    st.resize(4 * n);
    build(arr, 0, n - 1, 1);
  }

  int query(int l, int r) { return query(0, n - 1, l, r, 1); }

  void update(int index, int value) { update(0, n - 1, index, value, 1); }
};

int main() {
  vector<int> arr = {1, 3, 5, 7, 9, 11};
  SegmentTree st(arr);

  cout << "Suma de 1 a 3: " << st.query(1, 3) << endl;
  st.update(1, 10);
  cout << "Suma de 1 a 3 después de actualizar: " << st.query(1, 3) << endl;

  return 0;
}
