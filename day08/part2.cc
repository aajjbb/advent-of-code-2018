#include <bits/stdc++.h>

using namespace std;

const int MAX_TREE_SIZE = 100;

vector<int> tree[MAX_TREE_SIZE];
vector<int> tree_metadata[MAX_TREE_SIZE];

int build_tree(int node_id) {
  int child, meta;
  int value = 0;
  vector<int> child_values;

  cin >> child >> meta;

  for (int i = 0; i < child; i++) {
    int cv = build_tree(node_id + i + 1);
    child_values.push_back(cv);
  }

  for (int i = 0; i < meta; i++) {
    int mt_value;
    cin >> mt_value;

    tree_metadata[node_id].push_back(mt_value);

    if (child == 0) {
      value += mt_value;
    } else {
      if (mt_value > 0 && mt_value <= child) {
        value += child_values[mt_value - 1];
      }
    }
  }

  return value;
}

int main() {
  int root_value = build_tree(1);

  cout << root_value << "\n";

  return 0;
}
